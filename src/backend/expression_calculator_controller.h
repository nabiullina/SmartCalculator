#ifndef CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_EXPRESSION_CALCULATOR_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_EXPRESSION_CALCULATOR_CONTROLLER_H
#include <utility>

#include "expression_calculator.h"

namespace s21 {
class ExpressionCalculatorController {
 public:
  /**
   * Controller constructor initializing expression calculator model.
   * @param m calculator model
   */
  explicit ExpressionCalculatorController(ExpressionCalculator *m) : model(m){};

  /**
   * Invokes model's calculation method.
   * @return calculation result
   */
  long double Calculate() { return model->Calculate(); }

  /**
   * Invokes model's expression setting method.
   * @param expression expression
   */
  void setExpression(std::string expression) {
    model->setExpression(std::move(expression));
  }

  /**
   * Invokes model's x value setting method.
   * @param x value
   */
  void setXValue(long double x) { model->setXValue(x); }

 private:
  /**
   * Expression calculator model.
   */
  ExpressionCalculator *model;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_EXPRESSION_CALCULATOR_CONTROLLER_H
