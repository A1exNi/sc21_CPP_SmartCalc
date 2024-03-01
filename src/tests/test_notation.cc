#include <gtest/gtest.h>

#include <list>
#include <queue>

#include "../model/maincalc.h"
// добавить проверку с inf -inf
TEST(PolishNot, notation_1) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"224", "2e+3", "2e-003", "3E+0",
                              "*",   "+",    "sin",    "+"};
  std::string expr = "224 + sin(2e+3 + 2e-003 * 3E+0)";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_2) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"22.4", "34.1", "+"};
  std::string expr = "22.4 + 34,1";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_3) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"2"};
  std::string expr = "+2";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_4) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"2", "~"};
  std::string expr = "-2";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_5) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"1", "2", "~", "sin", "+"};
  std::string expr = "1 + sin(-2)";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_6) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"1", "2", "3", "*", "4", "*", "+"};
  std::string expr = "1 + 2 * 3 * 4";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_7) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{
      "2", "negate", "1",  "~",   "2",    "/",  "atan", "+", "4", "acos",
      "2", "asin",   "*",  "1",   "tan",  "10", "log",  "5", "~", "abs",
      "1", "2",      "/",  "cos", "-",    "*",  "+",    "/", "1", "sin",
      "%", "10",     "ln", "9",   "sqrt", "^",  "%",    "-"};
  std::string expr =
      "negate(2) + atan(-1/2) - acos(+4) * asin(2) / \
                    (tan(1) + log(10) * (abs(-5) - cos(1/2))) % sin(1) mod ln(10) ^ sqrt(9)";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_8) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"5", "2", "3", "^", "^"};
  std::string expr = "5^2^3";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_9) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"0.5", "tan", "sin", "cos"};
  std::string expr = "cos(sin(tan(0.5)))";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_10) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"1.23"};
  std::string expr = "1.23";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}
// -*-*
// 2^(3+1)/2 = 8
// 2^((3+1)/2) = 4
TEST(PolishNot, notation_11) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"3", "~", "2", "24",  "4", "+",
                              "^", "3", "/", "sin", "~", "-"};
  std::string expr = "-3--sin(2^(24+4)/3)";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_12) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"2", "2", "+", "sin", "~"};
  std::string expr = "-sin(2+2)";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_13) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"1", "~", "0.4", "cos", "*"};
  std::string expr = "(-1)*cos(0.4)";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_14) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"2", "1", "~", "^"};
  std::string expr = "2^-1";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_15) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"1", "2", "~", "3", "^", "+"};
  std::string expr = "1+-2^3";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_16) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"12", "10", "6e+4", "^", "*"};
  std::string expr = "12*10^6e+4";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}

TEST(PolishNot, notation_17) {
  s21::MainCalc model;
  std::queue<std::string> my_q;
  std::list<std::string> or_l{"1", "sin", "2", "^", "1", "cos", "2", "^", "+"};
  std::string expr = "(sin(1))^2+(cos(1))^2";
  my_q = model.ToReversePolishNotation(expr, "0");
  ASSERT_EQ(my_q.size(), or_l.size());
  while (!my_q.empty() && !or_l.empty()) {
    std::string my_str = my_q.front();
    my_q.pop();
    std::string or_str = or_l.front();
    or_l.pop_front();
    ASSERT_EQ(my_str, or_str);
  }
}