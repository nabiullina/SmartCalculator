#include "calc_tests.h"
#include "gtest/gtest.h"

class LoanCalcTest : public testing::Test {
 public:
  s21::LoanCalculator *calculator{};
  s21::LoanCalculatorController *controller{};

  void SetUp() override {
    calculator = new s21::LoanCalculator();
    controller = new s21::LoanCalculatorController(calculator);
  }

  void TearDown() override {
    delete controller;
    delete calculator;
  }
};

TEST_F(LoanCalcTest, ValidationTest_0) {
  EXPECT_ANY_THROW(controller->setMonths(0));
}

TEST_F(LoanCalcTest, ValidationTest_1) {
  EXPECT_ANY_THROW(controller->setMonths(-10));
}

TEST_F(LoanCalcTest, ValidationTest_2) {
  EXPECT_ANY_THROW(controller->setRate(-100));
}

TEST_F(LoanCalcTest, ValidationTest_3) {
  EXPECT_ANY_THROW(controller->setAmount(-100));
}

TEST_F(LoanCalcTest, AnnuityTest_1) {
  controller->setAmount(100000);
  controller->setRate(10);
  controller->setMonths(12);
  controller->CalculateAnnuityPayment();
  ASSERT_FLOAT_EQ(controller->getAnnuityPayment(), 8791.59);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 105499.08);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 5499.08);
}

TEST_F(LoanCalcTest, AnnuityTest_2) {
  controller->setAmount(50000);
  controller->setRate(12);
  controller->setMonths(24);
  controller->CalculateAnnuityPayment();
  ASSERT_FLOAT_EQ(controller->getAnnuityPayment(), 2353.67);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 56488.08);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 6488.08);
}

TEST_F(LoanCalcTest, AnnuityTest_3) {
  controller->setAmount(75000);
  controller->setRate(8);
  controller->setMonths(36);
  controller->CalculateAnnuityPayment();
  ASSERT_FLOAT_EQ(controller->getAnnuityPayment(), 2350.23);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 84608.28);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 9608.28);
}

TEST_F(LoanCalcTest, AnnuityTest_4) {
  controller->setAmount(120000);
  controller->setRate(15);
  controller->setMonths(18);
  controller->CalculateAnnuityPayment();
  ASSERT_FLOAT_EQ(controller->getAnnuityPayment(), 7486.17);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 134751.06);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 14751.06);
}

TEST_F(LoanCalcTest, AnnuityTest_5) {
  controller->setAmount(250000);
  controller->setRate(6);
  controller->setMonths(60);
  controller->CalculateAnnuityPayment();
  ASSERT_FLOAT_EQ(controller->getAnnuityPayment(), 4833.20);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 289992.00);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 39992.00);
}

TEST_F(LoanCalcTest, AnnuityTest_6) {
  controller->setAmount(80000);
  controller->setRate(20);
  controller->setMonths(24);
  controller->CalculateAnnuityPayment();
  ASSERT_FLOAT_EQ(controller->getAnnuityPayment(), 4071.66);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 97719.84);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 17719.84);
}

//
//
TEST_F(LoanCalcTest, DifferentiatedTest_1) {
  controller->setAmount(100000);
  controller->setRate(10);
  controller->setMonths(12);
  controller->CalculateDifferentiatedPayment();
  auto payments = controller->getDifferentiatedPayment();
  ASSERT_FLOAT_EQ(payments.back(), 8402.78);
  ASSERT_FLOAT_EQ(payments.front(), 9166.67);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 105416.67);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 5416.67);
}

TEST_F(LoanCalcTest, DifferentiatedTest_2) {
  controller->setAmount(50000);
  controller->setRate(12);
  controller->setMonths(24);
  controller->CalculateDifferentiatedPayment();
  auto payments = controller->getDifferentiatedPayment();
  ASSERT_FLOAT_EQ(payments.front(), 2583.33);
  ASSERT_FLOAT_EQ(payments.back(), 2104.17);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 56250.00);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 6250.00);
}

TEST_F(LoanCalcTest, DifferentiatedTest_3) {
  controller->setAmount(75000);
  controller->setRate(8);
  controller->setMonths(36);
  controller->CalculateDifferentiatedPayment();
  auto payments = controller->getDifferentiatedPayment();

  ASSERT_FLOAT_EQ(payments.front(), 2583.33);
  ASSERT_FLOAT_EQ(payments.back(), 2097.22);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 84250.00);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 9250.00);
}

TEST_F(LoanCalcTest, DifferentiatedTest_4) {
  controller->setAmount(120000);
  controller->setRate(15);
  controller->setMonths(18);
  controller->CalculateDifferentiatedPayment();

  auto payments = controller->getDifferentiatedPayment();
  ASSERT_FLOAT_EQ(payments.front(), 8166.67);
  ASSERT_FLOAT_EQ(payments.back(), 6750.00);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 134250.00);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 14250.00);
}

TEST_F(LoanCalcTest, DifferentiatedTest_5) {
  controller->setAmount(250000);
  controller->setRate(6);
  controller->setMonths(60);
  controller->CalculateDifferentiatedPayment();

  auto payments = controller->getDifferentiatedPayment();
  ASSERT_FLOAT_EQ(payments.front(), 5416.67);
  ASSERT_FLOAT_EQ(payments.back(), 4187.50);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 288125.00);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 38125.00);
}

TEST_F(LoanCalcTest, DifferentiatedTest_6) {
  controller->setAmount(80000);
  controller->setRate(20);
  controller->setMonths(24);
  controller->CalculateDifferentiatedPayment();

  auto payments = controller->getDifferentiatedPayment();
  ASSERT_FLOAT_EQ(payments.front(), 4666.67);
  ASSERT_FLOAT_EQ(payments.back(), 3388.89);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 96666.67);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 16666.67);
}

TEST_F(LoanCalcTest, DifferentiatedTest_Multiple) {
  controller->setAmount(80000);
  controller->setRate(20);
  controller->setMonths(24);
  controller->CalculateDifferentiatedPayment();

  auto payments = controller->getDifferentiatedPayment();
  ASSERT_FLOAT_EQ(payments.front(), 4666.67);
  ASSERT_FLOAT_EQ(payments.back(), 3388.89);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 96666.67);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 16666.67);

  controller->setAmount(250000);
  controller->setRate(6);
  controller->setMonths(60);
  controller->CalculateDifferentiatedPayment();

  payments = controller->getDifferentiatedPayment();
  ASSERT_FLOAT_EQ(payments.front(), 5416.67);
  ASSERT_FLOAT_EQ(payments.back(), 4187.50);
  ASSERT_FLOAT_EQ(controller->getTotalPaymentSum(), 288125.00);
  ASSERT_FLOAT_EQ(controller->getOverpayment(), 38125.00);
}
