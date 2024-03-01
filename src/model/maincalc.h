#ifndef CPP3_SMARTCALC_V2_0_2_SRC_MODEL_MAINCALC_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_MODEL_MAINCALC_H_

#include <queue>
#include <set>
#include <string>

namespace s21 {

struct FlagsForErrorExpr {
  bool isNumber{};
  bool isE{};
  bool isOperator{};
  bool isFunction{};
  bool isBracketClose{};
  bool isDot{};
  bool isPlus{};
  bool isX{};
  void ResetFlags();
};

class MainCalc {
 public:
  void MainCalcResult(const std::string *expression, const std::string *xValue);
  std::queue<std::string> ToReversePolishNotation(std::string expression,
                                                  std::string xValue);
  bool GetError();
  double GetResult();
  void Reset();

 private:
  double result{};
  bool error{};
  void ExpressionError(std::string *expression, std::string *xValue);
  FlagsForErrorExpr flags;
  std::set<char> operatorName = {'+', '-', '*', '/', '%', '^', 'm', '~'};
  std::set<std::string> functionName = {
      {"negate("}, {"atan("}, {"acos("}, {"asin("}, {"sqrt("}, {"tan("},
      {"log("},    {"abs("},  {"cos("},  {"sin("},  {"ln("}};
  void FixExpression(std::string *expression, std::string::iterator *it);
  int OperatorPriority(char ch);
  bool IsNumber(std::string::iterator it);
  void NumberCheckError(std::string::iterator it);
  bool IsOperator(char ch);
  void OperatorCheckError(std::string *expression, std::string::iterator it);
  bool IsFunction(std::string::iterator it);
  void FunctionCheckError(std::string::iterator *it);
  void XCheckError(std::string *expression, std::string *xValue,
                   std::string::iterator *it);
  double GetOperationResult(std::string str, double value1, double value2);
  std::string GetNumber(std::string::iterator it);
  std::string GetFunction(std::string::iterator it);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_MODEL_MAINCALC_H_