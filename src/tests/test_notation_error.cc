#include <gtest/gtest.h>

#include <list>
#include <queue>

#include "../model/maincalc.h"

TEST(PolishNotError, notation_error_1) {
  std::string expr = "224 + sinu(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_2) {
  std::string expr = "22.4 + 0 34,1";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_3) {
  std::string expr = "+2\n";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_4) {
  std::string expr = "-2 *";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_5) {
  std::string expr = "1 + sincos(-2)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_6) {
  std::string expr = "sin(1)cos(1)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_7) {
  std::string expr = "1 + (2+3)2";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_8) {
  std::string expr = "1(2+3) + 2";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_9) {
  std::string expr = "1 * (2 + 3))";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_10) {
  std::string expr = "1 * ((2 + 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_11) {
  std::string expr = "neg";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_12) {
  std::string expr = "224 + negatez(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_13) {
  std::string expr = "224 + atanf(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_14) {
  std::string expr = "224 + asinn(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_15) {
  std::string expr = "224 + sqrtg(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_16) {
  std::string expr = "tan1(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_17) {
  std::string expr = "log8(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_18) {
  std::string expr = "absi(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_19) {
  std::string expr = "cosuu";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_20) {
  std::string expr = "ln";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_20_2) {
  std::string expr = "3 m";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_21) {
  std::string expr = "* -2";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_22) {
  std::string expr = "224 + acosn(1 + 2 * 3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_23) {
  std::string expr = "-3--sin(2^(24_4)/3)";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_24) {
  std::string expr = "6 module 7";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_25) {
  std::string expr = "6 zmod 7";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_26) {
  std::string expr = "22..4 + 34,1";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_27) {
  std::string expr = "22.4.4 + 34,1";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_28) {
  std::string expr = "22.4 + 34,,1";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_29) {
  std::string expr = "22.4 + 34,1,";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_30) {
  std::string expr = "2e++3";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_31) {
  std::string expr = "2e*+3";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_32) {
  std::string expr = "2e";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_33) {
  std::string expr = "2ee+3";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_34) {
  std::string expr = "2e-+3";
  s21::MainCalc model;
  model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(model.GetError(), true);
}

TEST(PolishNotError, notation_error_35) {
  std::string xValue = "0";
  std::string expr =
      "999999999999999999999999999999999999999999999999999999999999999999999999999 \
                      999999999999999999999999999999999999999999999999999999999999999999999999999 \
                      999999999999999999999999999999999999999999999999999999999999999999999999999 \
                      999999999999999999999999999999999999999999999999999999999999999999999999999 \
                      999999999999999999999999999999999999+3";
  s21::MainCalc model;
  model.MainCalcResult(&expr, &xValue);
  ASSERT_EQ(model.GetError(), true);
}

// TEST(PolishNotError, notation_error_36) {
//   std::string xValue = "0";
//   std::string expr = "9a+3";
//   s21::MainCalc model;
//   model.MainCalc(&expr, &xValue);
//   ASSERT_EQ(model.GetError(), true);
// }