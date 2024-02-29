#ifndef CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_LOAN_CALCULATOR_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_LOAN_CALCULATOR_CONTROLLER_H
#include "loan_calculator.h"

namespace s21 {
class LoanCalculatorController {
 public:
  /**
   * Controller constructor initializing loan calculator model.
   * @param m loan calculator model
   */
  explicit LoanCalculatorController(LoanCalculator *m) : model(m) {}

  /**
   * Invokes model's amount setting method.
   * @param amount loan amount
   */
  void setAmount(double amount) { model->setAmount(amount); }

  /**
   * Invokes model's rate setting method.
   * @param rate rate
   */
  void setRate(double rate) { model->setRate(rate); }

  /**
   * Invokes model's period setting method.
   * @param months number of period
   */
  void setMonths(int months) { model->setMonths(months); }

  /**
   * Invokes model's annuity payment getting method.
   * @return annuity payment
   */
  double getAnnuityPayment() { return model->getAnnuityPayment(); }

  /**
   * Invokes model's differentiated payments getting method.
   * @return list of differentiated payments
   */
  std::list<double> getDifferentiatedPayment() {
    return model->getDifferentiatedPayment();
  }

  /**
   * Invokes model's overpayment getting method.
   * @return overpayment amount
   */
  double getOverpayment() { return model->getOverpayment(); }

  /**
   * Invokes model's total payment getting method.
   * @return total payment amount
   */
  double getTotalPaymentSum() { return model->getTotalPaymentSum(); }

  /**
   * Invokes model's annuity calculation method.
   */
  void CalculateAnnuityPayment() { model->CalculateAnnuityPayment(); }

  /**
   * Invokes model's differentiated calculation method.
   */
  void CalculateDifferentiatedPayment() {
    model->CalculateDifferentiatedPayment();
  }

 private:
  /**
   * Loan calculator model.
   */
  LoanCalculator *model;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_LOAN_CALCULATOR_CONTROLLER_H
