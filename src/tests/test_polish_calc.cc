#include <gtest/gtest.h>

#include <cmath>

#include "../model/maincalc.h"
#include "../model/plotcalc.h"

TEST(PolishCalc, polish_add) {
  std::string expr = "224 + 2.3";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), 224 + 2.3);
}

TEST(PolishCalc, polish_sub) {
  std::string expr = "224 - 2.3";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), 224 - 2.3);
}

TEST(PolishCalc, polish_mult) {
  std::string expr = "224 * 2.3";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), 224 * 2.3);
}

TEST(PolishCalc, polish_div) {
  std::string expr = "224 / 2.3";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), 224 / 2.3);
}

TEST(PolishCalc, polish_fmod) {
  std::string expr = "224 % 2.3";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), fmod(224, 2.3));
}

TEST(PolishCalc, polish_pow) {
  std::string expr = "224 ^ 2.3";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), pow(224, 2.3));
}

TEST(PolishCalc, polish_cos) {
  std::string expr = "cos(224)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), cos(224));
}

TEST(PolishCalc, polish_sin) {
  std::string expr = "sin(224)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), sin(224));
}

TEST(PolishCalc, polish_tan) {
  std::string expr = "tan(224)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), tan(224));
}

TEST(PolishCalc, polish_acos) {
  std::string expr = "acos(0.5)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), acos(0.5));
}

TEST(PolishCalc, polish_asin) {
  std::string expr = "asin(0.5)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), asin(0.5));
}

TEST(PolishCalc, polish_atan) {
  std::string expr = "atan(224)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), atan(224));
}

TEST(PolishCalc, polish_sqrt) {
  std::string expr = "sqrt(224)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), sqrt(224));
}

TEST(PolishCalc, polish_ln) {
  std::string expr = "ln(224)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), log(224));
}

TEST(PolishCalc, polish_log) {
  std::string expr = "log(224)";
  s21::MainCalc calc;
  std::string xValue = "0";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), log10(224));
}

TEST(PolishCalc, polish_negate) {
  std::string expr = "x * (-1.0)";
  s21::MainCalc calc;
  std::string xValue = "224";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(calc.GetResult(), 224 * (-1.0));
}

TEST(PolishCalc, polish_calc) {
  std::string expr =
      "x + negate(2e+5) + x + atan(-1/2) - acos(+1e-3) * asin(2E-6) / \
                    (tan(1E+2) + log(10) * (abs(x) - cos(1/2))) % sin(1) mod ln(10) ^ sqrt(9)";
  s21::MainCalc calc;
  std::string xValue = "-5";
  calc.MainCalcResult(&expr, &xValue);
  ASSERT_DOUBLE_EQ(
      calc.GetResult(),
      -5.0 + -2e+5 + -5.0 + atan(-1.0 / 2.0) -
          fmod(
              fmod(acos(+1e-3) * asin(2E-6) /
                       (tan(1E+2) + log10(10.0) * (abs(-5.0) - cos(1.0 / 2.0))),
                   sin(1)),
              pow(log(10), sqrt(9))));
}

TEST(PlotCalc, plot_calc) {
  s21::PlotCalc calc;
  std::string expr = "x + 3";
  double xMin = -10;
  double xMax = 10;
  size_t numberPoints = 20;
  std::vector<double> answer =
      calc.PlotCalcResult(&expr, xMin, xMax, numberPoints);
  std::vector<double> orig = {-7, -6, -5, -4, -3, -2, -1, 0,  1,  2,
                              3,  4,  5,  6,  7,  8,  9,  10, 11, 12};
  auto answer_it = answer.begin();
  auto orig_it = orig.begin();
  while (answer_it != answer.end() || orig_it != orig.end()) {
    ASSERT_DOUBLE_EQ(*answer_it, *orig_it);
    ++answer_it;
    ++orig_it;
  }
}

TEST(PlotCalc, plot_error) {
  s21::PlotCalc calc;
  std::string expr = "x+";
  double xMin = -10;
  double xMax = 10;
  size_t numberPoints = 20;
  calc.PlotCalcResult(&expr, xMin, xMax, numberPoints);
  ASSERT_EQ(calc.GetError(), true);
}