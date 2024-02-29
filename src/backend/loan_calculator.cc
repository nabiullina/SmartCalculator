#include "loan_calculator.h"

namespace s21 {

/**
 * Sets loan amount.
 * @param amount loan amount
 */
void LoanCalculator::setAmount(double amount) {
  if (amount > 0) {
    this->amount = amount;
  } else {
    throw std::invalid_argument("Amount should be a positive value.");
  }
}

/**
 * Sets loan rate.
 * @param rate loan rate
 */
void LoanCalculator::setRate(double rate) {
  if (rate >= 0) {
    this->rate = rate;
  } else {
    throw std::invalid_argument("Rate should not be a negative value.");
  }
}

/**
 * Sets loan period in (months)
 * @param months number of months
 */
void LoanCalculator::setMonths(int months) {
  if (months > 0) {
    this->months = months;
  } else {
    throw std::invalid_argument("Months should be positive value.");
  }
}

/**
 * Calculates annuity payment.
 */
void LoanCalculator::CalculateAnnuityPayment() {
  full_payment_amount = 0;
  double monthlyRatePart = rate / 12 / 100;
  annuity_payment =
      amount * (monthlyRatePart * pow(1 + monthlyRatePart, months) /
                (pow(1 + monthlyRatePart, months) - 1));
  annuity_payment = round(annuity_payment * 100) / 100;
  full_payment_amount = annuity_payment * months;
}

/**
 * Calculates differentiated payment.
 */
void LoanCalculator::CalculateDifferentiatedPayment() {
  full_payment_amount = 0;
  while (!differentiated_payments.empty()) differentiated_payments.pop_back();

  double monthlyRatePart = rate / 12.0 / 100;
  double payment = 0;
  double amountLeft = amount;
  for (int i = 1; i <= months; i++) {
    payment = amount / months + amountLeft * monthlyRatePart;
    payment = round(payment * 100) / 100;

    full_payment_amount += payment;
    amountLeft = amount - i * amount / months;
    differentiated_payments.push_back(payment);
  }
}

/**
 * Gets annuity payment.
 * @return annuity payment
 */
double LoanCalculator::getAnnuityPayment() { return annuity_payment; }

/**
 * Gets total payment sum.
 * @return total payment sum
 */
double LoanCalculator::getTotalPaymentSum() { return full_payment_amount; }

/**
 * Gets list of differentiated payments.
 * @return list of differentiated payments
 */
std::list<double> LoanCalculator::getDifferentiatedPayment() {
  return differentiated_payments;
}

/**
 * Gets overpayment amount.
 * @return overpayment amount
 */
double LoanCalculator::getOverpayment() { return full_payment_amount - amount; }

}  // namespace s21