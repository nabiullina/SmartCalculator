#ifndef CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_LOAN_CALCULATOR_H
#define CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_LOAN_CALCULATOR_H

#include <cmath>
#include <iostream>
#include <list>

namespace s21 {

class LoanCalculator {
 public:
  // SETTERS
  void setAmount(double amount);
  void setRate(double rate);
  void setMonths(int months);

  // GETTERS
  double getAnnuityPayment();
  std::list<double> getDifferentiatedPayment();
  double getOverpayment();
  double getTotalPaymentSum();

  // METHODS
  void CalculateAnnuityPayment();
  void CalculateDifferentiatedPayment();

 private:
  // FIELDS
  double amount;
  double rate;
  int months;
  double annuity_payment;
  std::list<double> differentiated_payments;
  double full_payment_amount;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_LOAN_CALCULATOR_H
