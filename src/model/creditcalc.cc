
#include "creditcalc.h"

#include <cmath>
#include <iostream>

namespace s21 {

void CreditCalc::CreditCalcResult(InputDataCreditCalc inputData) {
  setlocale(LC_NUMERIC, "C");
  Reset();
  error.CheckAmountError(inputData.amountStr);
  error.CheckTimeError(inputData.timeStr, inputData.yearsMonthsDays);
  error.CheckRateError(inputData.rateStr);
  if (error.error == NO) {
    double amount = std::stod(inputData.amountStr);
    int time = std::stoi(inputData.timeStr);
    double rate = std::stod(inputData.rateStr);
    if (inputData.yearsMonthsDays == 'y') time *= 12;
    double p = rate / 12.0 / 100.0;
    if (inputData.annuity) {
      monPay.push_back(amount * (p + p / (pow((1.0 + p), time) - 1.0)));
      monPay.back() = round(monPay.back() * 100.0) / 100.0;
      totalPay = monPay.back() * time;
    } else {
      double b = amount / time;
      for (int i = 0; i < time; ++i) {
        double j = (amount - i * b) * p;
        monPay.push_back(b + j);
        monPay.back() = round(monPay.back() * 100.0) / 100.0;
        totalPay += monPay.back();
      }
    }
    overPay = totalPay - amount;
  }
}

void CreditCalc::Reset() {
  error.Reset();
  monPay.clear();
  overPay = 0;
  totalPay = 0;
}

int CreditCalc::GetError() { return error.error; }
std::vector<double> CreditCalc::GetMonPay() { return monPay; }
double CreditCalc::GetOverPay() { return overPay; }
double CreditCalc::GetTotalPay() { return totalPay; }

}  // namespace s21
