#include "calc_tests.h"

class ExpCalcTest : public testing::Test {
 public:
  s21::ExpressionCalculator *calculator{};
  s21::ExpressionCalculatorController *controller{};

  void SetUp() override {
    calculator = new s21::ExpressionCalculator();
    controller = new s21::ExpressionCalculatorController(calculator);
  }

  void TearDown() override {
    delete controller;
    delete calculator;
  }
};

TEST_F(ExpCalcTest, ValidationTest_0) {
  controller->setExpression("coq-(+3)");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_1) {
  controller->setExpression("/3");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_2) {
  controller->setExpression("{}");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_3) {
  controller->setExpression("3)");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_4) {
  controller->setExpression("/3");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_5) {
  controller->setExpression("{}");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_6) {
  controller->setExpression("()");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_7) {
  controller->setExpression("asin2*x)");
  controller->setXValue(0.0003);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_8) {
  controller->setExpression("mod");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_9) {
  controller->setExpression("2.+1");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_10) {
  controller->setExpression("2.9*3+1.");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_11) {
  controller->setExpression("mod2");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_12) {
  EXPECT_ANY_THROW(controller->setExpression(""));
}

TEST_F(ExpCalcTest, ValidationTest_13) {
  controller->setExpression("2+((3-1)");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_14) {
  controller->setExpression("2x+(3-1)");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, ValidationTest_15) {
  controller->setExpression("2(x+(3-1)");
  controller->setXValue(0);
  EXPECT_ANY_THROW(controller->Calculate());
}

TEST_F(ExpCalcTest, Test_0) {
  controller->setExpression("2mod2");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 0);
}

TEST_F(ExpCalcTest, Test_1) {
  controller->setExpression("1e-2+1");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 1e-2 + 1);
}

TEST_F(ExpCalcTest, Test_2) {
  controller->setExpression("1e2+1e-09");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 1e2 + 1e-09);
}

TEST_F(ExpCalcTest, Test_3) {
  controller->setExpression("log(10*x)");
  controller->setXValue(2);
  ASSERT_FLOAT_EQ(controller->Calculate(), 1.30103);
}

TEST_F(ExpCalcTest, Test_4) {
  controller->setExpression("ln(10*x)");
  controller->setXValue(2);
  ASSERT_FLOAT_EQ(controller->Calculate(), 2.9957323);
}

TEST_F(ExpCalcTest, Test_5) {
  controller->setExpression("sqrt(2*x)");
  controller->setXValue(25);
  ASSERT_FLOAT_EQ(controller->Calculate(), 7.0710678);
}

TEST_F(ExpCalcTest, Test_6) {
  controller->setExpression(
      "cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(6)))))))))))");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 0.743467);
}

TEST_F(ExpCalcTest, Test_7) {
  controller->setExpression("3+4*2/(1-5)^2");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 3.5);
}

TEST_F(ExpCalcTest, Test_8) {
  controller->setExpression("1+2+3+4*5*6^7");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 5598726);
}

TEST_F(ExpCalcTest, Test_9) {
  controller->setExpression("123.456+2*3^4");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 285.456);
}

TEST_F(ExpCalcTest, Test_10) {
  controller->setExpression("(8+2*5)/(1+3*2-4)");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 6);
}

TEST_F(ExpCalcTest, Test_11) {
  controller->setExpression(
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 10);
}

TEST_F(ExpCalcTest, Test_12) {
  controller->setExpression("cos(1*2)-1");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), -1.41614683655);
}

TEST_F(ExpCalcTest, Test_13) {
  controller->setExpression(
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1");
  ;
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), -1.83907152908);
}

TEST_F(ExpCalcTest, Test_14) {
  controller->setExpression("sin(cos(5))");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 0.27987335076);
}

TEST_F(ExpCalcTest, Test_15) {
  controller->setExpression("2.33mod1");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 0.33);
}

TEST_F(ExpCalcTest, Test_16) {
  controller->setExpression("3+4*2/1-5+2^2");
  controller->setXValue(10);
  ASSERT_FLOAT_EQ(controller->Calculate(), 10);
}

TEST_F(ExpCalcTest, Test_17) {
  controller->setExpression("3+4*2/1-5+2^2");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 10);
}

TEST_F(ExpCalcTest, Test_18) {
  controller->setExpression("asin(2*x)");
  controller->setXValue(0.0003);
  ASSERT_FLOAT_EQ(controller->Calculate(), 0.0006);
}

TEST_F(ExpCalcTest, Test_19) {
  controller->setExpression("acos(2*x)");
  controller->setXValue(0.0019);
  ASSERT_FLOAT_EQ(controller->Calculate(), 1.5669963);
}

TEST_F(ExpCalcTest, Test_20) {
  controller->setExpression("atan(2*x)");
  controller->setXValue(0.0019);
  ASSERT_FLOAT_EQ(controller->Calculate(), 0.0037999817);
}

TEST_F(ExpCalcTest, Test_21) {
  controller->setExpression("tan(2*x)");
  controller->setXValue(0.004);
  ASSERT_FLOAT_EQ(controller->Calculate(), 0.00800017);
}

TEST_F(ExpCalcTest, Test_22) {
  controller->setExpression("1e-100");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 1e-100);
}

TEST_F(ExpCalcTest, Test_23) {
  controller->setExpression("1e-100^2");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 1e-100);
}

TEST_F(ExpCalcTest, Test_24) {
  long double x = 1.0;
  controller->setExpression("x");
  controller->setXValue(x);
  ASSERT_FLOAT_EQ(controller->Calculate(), 1);
}

TEST_F(ExpCalcTest, Test_25) {
  controller->setExpression("9.3");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 9.3);
}

TEST_F(ExpCalcTest, Test_26) {
  controller->setExpression("-3");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), -3);
}

TEST_F(ExpCalcTest, Test_27) {
  controller->setExpression("cos(x)");
  controller->setXValue(0);
  ASSERT_FLOAT_EQ(controller->Calculate(), 1);
}

TEST_F(ExpCalcTest, Test_28) {
  long double x = 1.0;
  controller->setExpression("cos(3*x)");
  controller->setXValue(x);
  ASSERT_FLOAT_EQ(controller->Calculate(), cos(3 * x));
}

TEST_F(ExpCalcTest, Test_29) {
  long double x = 0;
  controller->setExpression("1 + 1");
  controller->setXValue(x);
  ASSERT_FLOAT_EQ(controller->Calculate(), 2);
}

TEST_F(ExpCalcTest, Test_30) {
  long double x = 0;
  controller->setExpression("2^2^2");
  controller->setXValue(x);
  ASSERT_FLOAT_EQ(controller->Calculate(), pow(2, pow(2, 2)));
}

TEST_F(ExpCalcTest, Test_31) {
  long double x = 0;
  controller->setExpression("+2");
  controller->setXValue(x);
  ASSERT_FLOAT_EQ(controller->Calculate(), 2);
}