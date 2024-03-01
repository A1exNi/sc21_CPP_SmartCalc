
#include "maincalc.h"

#include <cmath>
#include <iostream>
#include <stack>
namespace s21 {
void FlagsForErrorExpr::ResetFlags() {
  isNumber = false;
  isE = false;
  isOperator = false;
  isFunction = false;
  isBracketClose = false;
  isDot = false;
  isPlus = false;
  isX = false;
}

void MainCalc::MainCalcResult(const std::string *expression,
                              const std::string *xValue) {
  setlocale(LC_NUMERIC, "C");
  Reset();
  std::queue<std::string> polishNot =
      ToReversePolishNotation(*expression, *xValue);
  std::stack<double> buf;
  double value1 = 0;
  while (!polishNot.empty() && !error) {
    std::string str = polishNot.front();
    polishNot.pop();
    while (IsNumber(str.begin()) && !error) {
      try {
        buf.push(std::stod(str));
        str = polishNot.front();
        polishNot.pop();
      } catch (...) {
        error = true;
      }
    }
    if (!error) {
      double value2 = buf.top();
      buf.pop();
      if (IsOperator(str[0]) && str[0] != '~') {
        value1 = buf.top();
        buf.pop();
      }
      buf.push(GetOperationResult(str, value1, value2));
    }
  }
  if (!error) result = buf.top();
}

double MainCalc::GetOperationResult(std::string str, double value1,
                                    double value2) {
  double answer = 0;
  if (str[0] == '+') answer = value1 + value2;
  if (str[0] == '-') answer = value1 - value2;
  if (str[0] == '*') answer = value1 * value2;
  if (str[0] == '/') answer = value1 / value2;
  if (str[0] == '%') answer = fmod(value1, value2);
  if (str[0] == '^') answer = pow(value1, value2);
  if (str[0] == '~' || str[0] == 'n') answer = value2 * -1.0;
  if (str[0] == 'c') answer = cos(value2);
  if (str[0] == 't') answer = tan(value2);
  if (str[0] == 's') {
    if (str[1] == 'i') answer = sin(value2);
    if (str[1] == 'q') answer = sqrt(value2);
  }
  if (str[0] == 'l') {
    if (str[1] == 'o') answer = log10(value2);
    if (str[1] == 'n') answer = log(value2);
  }
  if (str[0] == 'a') {
    if (str[1] == 't') answer = atan(value2);
    if (str[1] == 'c') answer = acos(value2);
    if (str[1] == 's') answer = asin(value2);
    if (str[1] == 'b') answer = abs(value2);
  }
  return answer;
}

std::queue<std::string> MainCalc::ToReversePolishNotation(
    std::string expression, std::string xValue) {
  std::queue<std::string> polishNot;
  ExpressionError(&expression, &xValue);
  if (!error) {
    std::stack<std::string> bufStack;
    auto it = expression.begin();
    while (it != expression.end() && !error) {
      if (IsNumber(it)) {
        std::string number = GetNumber(it);
        polishNot.push(number);
        it += number.length();
      } else if (*it == 'x') {
        polishNot.push(xValue);
        ++it;
      } else if (*it == '(') {
        bufStack.push("(");
        ++it;
      } else if (IsFunction(it)) {
        std::string function = GetFunction(it);
        bufStack.push(function);
        it += function.length();
      } else if (IsOperator(*it)) {
        while (!bufStack.empty() &&
               (OperatorPriority(bufStack.top()[0]) <= OperatorPriority(*it)) &&
               !(bufStack.top()[0] == '^' && *it == '^') &&
               !(bufStack.top()[0] == '~' && *it == '~')) {
          polishNot.push(bufStack.top());
          bufStack.pop();
        }
        std::string str(1, *it);
        bufStack.push(str);
        ++it;
      } else if (*it == ')') {
        while (!bufStack.empty() && bufStack.top()[0] != '(') {
          polishNot.push(bufStack.top());
          bufStack.pop();
        }
        if (!bufStack.empty()) bufStack.pop();
        ++it;
      }
    }
    while (!bufStack.empty()) {
      polishNot.push(bufStack.top());
      bufStack.pop();
    }
  }
  return polishNot;
}

void MainCalc::ExpressionError(std::string *expression, std::string *xValue) {
  int countBracket = 0;
  auto it = expression->begin();
  while (it != expression->end() && !error) {
    FixExpression(expression, &it);
    if (IsNumber(it)) {
      NumberCheckError(it);
    } else if (IsOperator(*it)) {
      OperatorCheckError(expression, it);
    } else if (IsFunction(it)) {
      FunctionCheckError(&it);
    } else if (*it == '(') {
      if (flags.isNumber || flags.isX) error = true;
      ++countBracket;
    } else if (*it == ')') {
      --countBracket;
      flags.isBracketClose = true;
    } else if (*it == 'x') {
      XCheckError(expression, xValue, &it);
    } else {
      error = true;
    }
    ++it;
  }
  if (xValue->front() == '-') xValue->erase(0, 1);
  if (countBracket != 0 || flags.isOperator) error = true;
}

void MainCalc::FixExpression(std::string *expression,
                             std::string::iterator *it) {
  while (**it == ' ') *it = expression->erase(*it);
  if (**it == 'm') {
    std::string str = expression->substr((*it - expression->begin()), 3);
    if (str != "mod") {
      error = true;
    } else {
      *it = expression->erase(*it, *it + 3);
      expression->insert(*it, '%');
    }
  }
  if (**it == ',') **it = '.';
  if (**it == '-') {
    if (*it == expression->begin() && expression->length() > 1)
      **it = '~';
    else if (*it != expression->begin())
      if (!IsNumber(*it - 1) && *(*it - 1) != ')') **it = '~';
  }
  if (**it == '+') {
    if (*it == expression->begin() && expression->length() > 1)
      *it = expression->erase(*it);
    else if (*it != expression->begin())
      if (!IsNumber(*it - 1) && *(*it - 1) != ')' && *(*it - 1) != 'x')
        *it = expression->erase(*it);
  }
}

bool MainCalc::IsNumber(std::string::iterator it) {
  bool answer = false;
  if ((*it >= '0' && *it <= '9') || *it == '.' || *it == ',') answer = true;
  if (*it == 'e' || *it == 'E') {
    --it;
    if (IsNumber(it) && *it != 'e' && *it != 'E') {
      it += 2;
      if (*it == '+' || *it == '-') answer = true;
    }
  } else if (*it == '+' || *it == '-') {
    --it;
    if (*it == 'e' || *it == 'E') answer = true;
  }
  return answer;
}

void MainCalc::NumberCheckError(std::string::iterator it) {
  if (flags.isBracketClose || flags.isX) error = true;
  if (*it == ',' || *it == '.') {
    if (flags.isDot || flags.isE) error = true;
    flags.isDot = true;
  }
  if ((*it == '-' || *it == '+') && (*(it + 1) == '-' || *(it + 1) == '+'))
    error = true;
  if (!flags.isNumber && *it == '0' && *(it + 1) != '.' && *(it + 1) != ',')
    error = true;
  if (!flags.isNumber && !flags.isE) flags.ResetFlags();
  flags.isNumber = true;
  if (*it == 'e' || *it == 'E') flags.isE = true;
}

bool MainCalc::IsOperator(char ch) {
  return (operatorName.find(ch) != operatorName.end());
}

void MainCalc::OperatorCheckError(std::string *expression,
                                  std::string::iterator it) {
  if (*it != '~') {
    if (flags.isOperator) error = true;
    if (expression->begin() == it) error = true;
  }
  flags.ResetFlags();
  flags.isOperator = true;
}

bool MainCalc::IsFunction(std::string::iterator it) {
  bool answer = false;
  if (*it == 'n' || *it == 'l' || *it == 't' || *it == 'a' || *it == 'c' ||
      *it == 's')
    answer = true;
  return answer;
}

void MainCalc::FunctionCheckError(std::string::iterator *it) {
  std::string function = GetFunction(*it);
  if (*(*it + function.length()) == '(') function += "(";
  if (functionName.find(function) == functionName.end()) error = true;
  if (!error) {
    *it += function.length() - 2;
    if (flags.isBracketClose || flags.isX) error = true;
  }
  flags.ResetFlags();
  flags.isFunction = true;
}

void MainCalc::XCheckError(std::string *expression, std::string *xValue,
                           std::string::iterator *it) {
  if (xValue->front() == '-') {
    *it = expression->insert(*it, '~');
    ++(*it);
    flags.isOperator = true;
  }
  error = true;
  if (flags.isOperator) error = false;
  if (*it != expression->begin()) {
    if (*(*it - 1) == '(') error = false;
  } else {
    error = false;
  }
  flags.ResetFlags();
  flags.isX = true;
}

int MainCalc::OperatorPriority(char ch) {
  int answer = 0;
  if (ch == '~') answer = 0;
  if (ch == '^') answer = 1;
  if (ch == '*' || ch == '/' || ch == '%' || ch == 'm') answer = 2;
  if (ch == '+' || ch == '-') answer = 3;
  if (ch == '(') answer = 4;
  return answer;
}

std::string MainCalc::GetNumber(std::string::iterator it) {
  auto itEndNumber = it;
  while (IsNumber(itEndNumber)) ++itEndNumber;
  std::string number;
  std::copy(it, itEndNumber, std::back_inserter(number));
  return number;
}

std::string MainCalc::GetFunction(std::string::iterator it) {
  auto itEndNumber = it;
  while (*itEndNumber != '(' && *itEndNumber != '\0') ++itEndNumber;
  std::string function;
  std::copy(it, itEndNumber, std::back_inserter(function));
  return function;
}

void MainCalc::Reset() {
  result = 0;
  error = false;
  flags.ResetFlags();
}
double MainCalc::GetResult() { return result; }

bool MainCalc::GetError() { return error; }

}  // namespace s21
