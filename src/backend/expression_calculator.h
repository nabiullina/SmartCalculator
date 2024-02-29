#ifndef CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_EXPRESSION_CALCULATOR_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_EXPRESSION_CALCULATOR_H_

#include <cmath>
#include <cstring>
#include <queue>
#include <regex>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>

namespace s21 {
enum class ValueType {
  kNum,
  kX,
  kOpenBrace,
  kCloseBrace,
  kPlus,
  kMinus,
  kMulti,
  kDiv,
  kPow,
  kMod,
  kUnaryPlus,
  kUnaryMinus,
  kCos,
  kSin,
  kTan,
  kAcos,
  kAsin,
  kAtan,
  kSqrt,
  kLn,
  kLog,
  kOperator,
  kFunction
};

struct StackElement {
  long double data;
  int importance;
  ValueType type;
};

const std::string ARITHMETIC_OPERATORS = "+-*/^m";

class ExpressionCalculator {
 public:
  // CONSTRUCTORS
  ExpressionCalculator() = default;

  // SETTERS
  void setExpression(std::string inputExpression);
  void setXValue(long double xValue);

  // METHODS
  long double Calculate();

 private:
  // FIELDS
  std::queue<StackElement> polish_notation;
  std::stack<StackElement> stack;
  std::string expression;
  char *it{};
  long double x = 0;
  ValueType previous_symbol = ValueType::kOpenBrace;
  int count_open_braces{};
  int count_close_braces{};

  // METHODS
  void CalcOperators(long double left_operand, long double right_operand,
                     ValueType type);
  void CalcFuncs(double operand, ValueType function);
  void EmptyStackAndQueue();
  void ConvertToPolish();
  long double CalculateExpression();
  void FuncCase();
  void NumCase();
  void OperatorsCase();
  void CloseBraceCase();
  void OpenBraceCase();
  void XCase();
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_EXPRESSION_CALCULATOR_H_
