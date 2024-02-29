#include "expression_calculator.h"

namespace s21 {
/**
 * Sets X value.
 * @param xValue value
 */
void ExpressionCalculator::setXValue(long double xValue) { this->x = xValue; }

/**
 * Sets expression to calculate.
 * @param inputExpression expression
 */
void ExpressionCalculator::setExpression(std::string inputExpression) {
  if (inputExpression.empty()) {
    throw std::invalid_argument("invalid input");
  }

  this->expression = std::move(inputExpression);
  this->it = this->expression.data();
  previous_symbol = ValueType::kOpenBrace;
  count_open_braces = 0;
  count_close_braces = 0;
}

/**
 * Calculates expression.
 * @return calculation result
 */
long double ExpressionCalculator::Calculate() {
  EmptyStackAndQueue();
  ConvertToPolish();
  return CalculateExpression();
}

/**
 * Empties stack and output queue.
 */
void ExpressionCalculator::EmptyStackAndQueue() {
  while (!stack.empty()) {
    stack.pop();
  }

  while (!polish_notation.empty()) {
    polish_notation.pop();
  }
}

/**
 * Converts expression to polish notation.
 */
void ExpressionCalculator::ConvertToPolish() {
  while (*it != '\0') {
    if (*it == ' ') {
      ++it;
    } else if (*it == 'x') {
      XCase();
    } else if (*it >= '0' && *it <= '9') {
      NumCase();
    } else if (*it == '(') {
      OpenBraceCase();
    } else if (*it == ')') {
      CloseBraceCase();
    } else if (ARITHMETIC_OPERATORS.find(*it) != std::string::npos) {
      OperatorsCase();
    } else {
      FuncCase();
    }
  }

  if ((previous_symbol != ValueType::kNum && previous_symbol != ValueType::kX &&
       previous_symbol != ValueType::kCloseBrace) ||
      count_open_braces != count_close_braces) {
    throw std::invalid_argument("invalid input");
  }

  while (!stack.empty()) {
    polish_notation.push(stack.top());
    stack.pop();
  }
}

/**
 * Pushes 'x' token to output queue.
 */
void ExpressionCalculator::XCase() {
  if (!(previous_symbol == ValueType::kOpenBrace ||
        previous_symbol == ValueType::kOperator)) {
    throw std::invalid_argument("invalid input");
  }

  previous_symbol = ValueType::kX;
  polish_notation.push({0, 0, ValueType::kX});
  ++it;
}

/**
 * Pushes 'number' token to output queue.
 */
void ExpressionCalculator::NumCase() {
  if (!(previous_symbol == ValueType::kNum ||
        previous_symbol == ValueType::kOperator ||
        previous_symbol == ValueType::kOpenBrace)) {
    throw std::invalid_argument("invalid input");
  }

  std::string number;
  while ((*it >= '0' && *it <= '9') || *it == '.' || *it == ',') {
    number += *it;
    ++it;
  }

  if (*it == 'e' || *it == 'E') {
    number += *it;
    ++it;
    if (*it == '+' || *it == '-') {
      number += *it;
      ++it;
    }
    while ((*it >= '0' && *it <= '9')) {
      number += *it;
      ++it;
    }
  } else if (number.back() == '.') {
    throw std::invalid_argument("invalid input");
  }
  long double num = std::stold(number);
  polish_notation.push({num, 0, ValueType::kNum});
  previous_symbol = ValueType::kNum;
}

/**
 * Pushes 'open brace' token to operators stack.
 */
void ExpressionCalculator::OpenBraceCase() {
  if (!(previous_symbol == ValueType::kOperator ||
        previous_symbol == ValueType::kFunction ||
        previous_symbol == ValueType::kOpenBrace)) {
    throw std::invalid_argument("invalid input");
  }

  previous_symbol = ValueType::kOpenBrace;
  ++count_open_braces;
  stack.push({0, 0, ValueType::kOpenBrace});
  ++it;
}

/**
 * Pushes tokens to output queue if current token is 'close brace'.
 */
void ExpressionCalculator::CloseBraceCase() {
  if (!(previous_symbol == ValueType::kNum ||
        previous_symbol == ValueType::kCloseBrace ||
        previous_symbol == ValueType::kX) ||
      count_close_braces >= count_open_braces) {
    throw std::invalid_argument("invalid input");
  }

  previous_symbol = ValueType::kCloseBrace;
  ++count_close_braces;

  while (stack.top().type != ValueType::kOpenBrace && !stack.empty()) {
    polish_notation.push(stack.top());
    stack.pop();
  }
  stack.pop();
  if (!stack.empty()) {
    if (stack.top().type >= ValueType::kCos &&
        stack.top().type <= ValueType::kLog) {
      polish_notation.push(stack.top());
      stack.pop();
    }
  }
  ++it;
}

/**
 * Pushes 'operator' tokens to stack or output queue following Dijkstra's
 * algorithm.
 */
void ExpressionCalculator::OperatorsCase() {
  if (!(previous_symbol == ValueType::kNum ||
        previous_symbol == ValueType::kCloseBrace ||
        previous_symbol == ValueType::kX ||
        (previous_symbol == ValueType::kOpenBrace &&
         (*it == '-' || *it == '+')))) {
    throw std::invalid_argument("invalud input");
  }

  if (*it == '-') {
    while (!stack.empty() && stack.top().importance >= 1) {
      polish_notation.push(stack.top());
      stack.pop();
    }
    if (previous_symbol == ValueType::kOpenBrace) {
      stack.push({0, 1, ValueType::kUnaryMinus});
    } else {
      stack.push({0, 1, ValueType::kMinus});
    }
  } else if (*it == '+') {
    while (!stack.empty() && stack.top().importance >= 1) {
      polish_notation.push(stack.top());
      stack.pop();
    }
    if (previous_symbol == ValueType::kOpenBrace) {
      stack.push({0, 1, ValueType::kUnaryPlus});
    } else {
      stack.push({0, 1, ValueType::kPlus});
    }
  } else if (*it == '*') {
    while (!stack.empty() && stack.top().importance >= 2) {
      polish_notation.push(stack.top());
      stack.pop();
    }
    stack.push({0, 2, ValueType::kMulti});
  } else if (*it == '/') {
    while (!stack.empty() && stack.top().importance >= 2) {
      polish_notation.push(stack.top());
      stack.pop();
    }
    stack.push({0, 2, ValueType::kDiv});
  } else if (*it == '^') {
    while (!stack.empty() && stack.top().importance >= 3) {
      polish_notation.push(stack.top());
      stack.pop();
    }
    stack.push({0, 3, ValueType::kPow});
  } else if (!strncmp(it, "mod", 3)) {
    stack.push({0, 2, ValueType::kMod});
    it += 2;
  }
  ++it;
  previous_symbol = ValueType::kOperator;
}

/**
 * Pushes 'function' tokens to stack following Dijkstra's algorithm.
 */
void ExpressionCalculator::FuncCase() {
  previous_symbol = ValueType::kFunction;
  if (!std::strncmp(it, "sin", 3)) {
    stack.push({0, 4, ValueType::kSin});
    it += 3;
  } else if (!strncmp(it, "cos", 3)) {
    stack.push({0, 4, ValueType::kCos});
    it += 3;
  } else if (!strncmp(it, "log", 3)) {
    stack.push({0, 4, ValueType::kLog});
    it += 3;
  } else if (!strncmp(it, "ln", 2)) {
    stack.push({0, 4, ValueType::kLn});
    it += 2;
  } else if (!strncmp(it, "sqrt", 4)) {
    stack.push({0, 4, ValueType::kSqrt});
    it += 4;
  } else if (!strncmp(it, "tan", 3)) {
    stack.push({0, 4, ValueType::kTan});
    it += 3;
  } else if (!strncmp(it, "atan", 4)) {
    stack.push({0, 4, ValueType::kAtan});
    it += 4;
  } else if (!strncmp(it, "asin", 4)) {
    stack.push({0, 4, ValueType::kAsin});
    it += 4;
  } else if (!strncmp(it, "acos", 4)) {
    stack.push({0, 4, ValueType::kAcos});
    it += 4;
  } else {
    throw std::invalid_argument("invalid input");
  }
}

/**
 * Calculates expression parsed to polish notation.
 * @return calculation result.
 */
long double ExpressionCalculator::CalculateExpression() {
  long double left_operand = 0, right_operand = 0;
  StackElement element{};

  while (!polish_notation.empty()) {
    element = polish_notation.front();
    if (element.type == ValueType::kNum) {
      stack.push(element);
    } else if (element.type == ValueType::kX) {
      stack.push({x, 0, ValueType::kNum});
    } else {
      if (element.type >= ValueType::kPlus && element.type <= ValueType::kMod) {
        right_operand = stack.top().data;
        stack.pop();
        left_operand = stack.top().data;
        stack.pop();
        CalcOperators(left_operand, right_operand, element.type);
      } else {
        left_operand = stack.top().data;
        stack.pop();
        CalcFuncs((double)left_operand, element.type);
      }
    }
    polish_notation.pop();
  }
  left_operand = !stack.empty() ? stack.top().data : 0;
  stack.pop();

  return left_operand;
}

/**
 * Calculates operators and pushes result to stack.
 * @param left_operand left operand
 * @param right_operand right operand
 * @param arithmetic_operator arithmetic operator
 */
void ExpressionCalculator::CalcOperators(long double left_operand,
                                         long double right_operand,
                                         ValueType arithmetic_operator) {
  long double result = 0;
  switch (arithmetic_operator) {
    case ValueType::kPlus:
      result = left_operand + right_operand;
      break;
    case ValueType::kMinus:
      result = left_operand - right_operand;
      break;
    case ValueType::kDiv:
      result = left_operand / right_operand;
      break;
    case ValueType::kMulti:
      result = left_operand * right_operand;
      break;
    case ValueType::kMod:
      result = fmod((double)left_operand, (double)right_operand);
      break;
    case ValueType::kPow:
      result = pow((double)left_operand, (double)right_operand);
      break;
    default:
      break;
  }
  stack.push({result, 0, ValueType::kNum});
}

/**
 * Calculates functions and pushes result to stack.
 * @param operand operand
 * @param function function
 */
void ExpressionCalculator::CalcFuncs(double operand, ValueType function) {
  long double result = 0;
  switch (function) {
    case ValueType::kSin:
      result = sin(operand);
      break;
    case ValueType::kCos:
      result = cos(operand);
      break;
    case ValueType::kTan:
      result = tan(operand);
      break;
    case ValueType::kAsin:
      result = asin(operand);
      break;
    case ValueType::kAcos:
      result = acos(operand);
      break;
    case ValueType::kSqrt:
      result = sqrt(operand);
      break;
    case ValueType::kLn:
      result = log(operand);
      break;
    case ValueType::kLog:
      result = log10(operand);
      break;
    case ValueType::kAtan:
      result = atan(operand);
      break;
    case ValueType::kUnaryMinus:
      result = -operand;
      break;
    case ValueType::kUnaryPlus:
      result = std::abs(operand);
      break;
    default:
      break;
  }
  stack.push({result, 0, ValueType::kNum});
}

}  // namespace s21
