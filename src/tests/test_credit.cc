#include <gtest/gtest.h>

#include <vector>

#include "../model/creditcalc.h"

TEST(CreditCalc, credit_calc) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "5";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'y';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  std::vector<double> my = calc.GetMonPay();
  std::vector<double> orig = {1887.12};
  auto myIt = my.begin();
  auto orIt = orig.begin();
  while (myIt != my.end() || orIt != orig.end()) {
    ASSERT_DOUBLE_EQ(*myIt, *orIt);
    ++myIt;
    ++orIt;
  }
  ASSERT_DOUBLE_EQ(calc.GetOverPay(), 13227.20);
  ASSERT_DOUBLE_EQ(calc.GetTotalPay(), 113227.20);
}

TEST(CreditCalc, credit_calc2) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "5";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = false;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  std::vector<double> my = calc.GetMonPay();
  std::vector<double> orig = {20416.67, 20333.33, 20250.0, 20166.67, 20083.33};
  auto myIt = my.begin();
  auto orIt = orig.begin();
  while (myIt != my.end() || orIt != orig.end()) {
    ASSERT_DOUBLE_EQ(*myIt, *orIt);
    ++myIt;
    ++orIt;
  }
  ASSERT_DOUBLE_EQ(calc.GetOverPay(), 1250.00);
  ASSERT_DOUBLE_EQ(calc.GetTotalPay(), 101250.00);
}

TEST(CreditCalc, credit_calc3) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "10000000.00";
  inputData.timeStr = "50";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  std::vector<double> my = calc.GetMonPay();
  std::vector<double> orig = {221971.07};
  auto myIt = my.begin();
  auto orIt = orig.begin();
  while (myIt != my.end() || orIt != orig.end()) {
    ASSERT_DOUBLE_EQ(*myIt, *orIt);
    ++myIt;
    ++orIt;
  }
  ASSERT_DOUBLE_EQ(calc.GetOverPay(), 1098553.50);
  ASSERT_DOUBLE_EQ(calc.GetTotalPay(), 11098553.50);
}

TEST(CreditCalc, credit_calc_error) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.004";
  inputData.timeStr = "5";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'y';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::AMOUNT);
}

TEST(CreditCalc, credit_calc_error2) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.a";
  inputData.timeStr = "5";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'y';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::AMOUNT);
}

TEST(CreditCalc, credit_calc_error3) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "adsf";
  inputData.timeStr = "5";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'y';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::AMOUNT);
}

TEST(CreditCalc, credit_calc_error4) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "51";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'y';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::TIME);
}

TEST(CreditCalc, credit_calc_error5) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "601";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::TIME);
}

TEST(CreditCalc, credit_calc_error6) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "0";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'y';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::TIME);
}

TEST(CreditCalc, credit_calc_error7) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "0";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::TIME);
}

TEST(CreditCalc, credit_calc_error8) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "a";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'y';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::TIME);
}

TEST(CreditCalc, credit_calc_error9) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "1000";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::TIME);
}

TEST(CreditCalc, credit_calc_error10) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "100";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'y';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::TIME);
}

TEST(CreditCalc, credit_calc_error11) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "100";
  inputData.rateStr = "5.112";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::RATE);
}

TEST(CreditCalc, credit_calc_error12) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "100";
  inputData.rateStr = "a";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::RATE);
}

TEST(CreditCalc, credit_calc_error13) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "100";
  inputData.rateStr = "5.a";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::RATE);
  calc.Reset();
  ASSERT_EQ(calc.GetError(), s21::NO);
}

TEST(AmountError, amount_error) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr =
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999";
  inputData.timeStr = "100";
  inputData.rateStr = "5";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::AMOUNT);
  calc.Reset();
  ASSERT_EQ(calc.GetError(), s21::NO);
}

TEST(RateError, rate_error) {
  s21::InputDataCreditCalc inputData;
  inputData.amountStr = "100000.00";
  inputData.timeStr = "100";
  inputData.rateStr =
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999";
  inputData.yearsMonthsDays = 'm';
  inputData.annuity = true;
  s21::CreditCalc calc;
  calc.CreditCalcResult(inputData);
  ASSERT_EQ(calc.GetError(), s21::RATE);
  calc.Reset();
  ASSERT_EQ(calc.GetError(), s21::NO);
}