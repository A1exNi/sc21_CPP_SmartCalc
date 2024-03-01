
#include "deposcalc.h"

#include <cmath>
#include <iostream>

namespace s21 {

void DeposCalc::CheckAmountError(std::string amountStr) {
  error.CheckAmountError(amountStr);
}

void DeposCalc::DeposCalcResult(InputDataDeposCalc inputData) {
  setlocale(LC_NUMERIC, "C");
  Reset();
  error.CheckAmountError(inputData.amountStr);
  error.CheckRateError(inputData.taxRateStr);
  error.CheckRateError(inputData.interestRateStr);
  if (error.error == NO) {
    depAmount = stod(inputData.amountStr);
    double taxRate = stod(inputData.taxRateStr);
    double interestRate = stod(inputData.interestRateStr);
    double resForTax = 0;
    double accruedInterest = 0;
    time_t nextTimePay = mktime(&inputData.tmStartDate);
    time_t currentDate = mktime(&inputData.tmStartDate);
    IncreaseNextTimePay(&nextTimePay, inputData.freqPayStr);
    while (currentDate != mktime(&inputData.tmEndDate)) {
      currentDate = currentDate + 24 * 60 * 60;
      tm *bufLocalTime = localtime(&currentDate);
      int numberDayAtYear = 365;
      if (IsLeap(bufLocalTime->tm_year)) numberDayAtYear = 366;
      double interestForDay =
          depAmount * (interestRate / 100.0) / numberDayAtYear;
      interest += interestForDay;
      if (*inputData.freqPayStr == "every day") {
        interest -= interestForDay;
        interest += round(interestForDay * 100.0) / 100.0;
        resForTax += round(interestForDay * 100.0) / 100.0;
        if (inputData.isCapitalization)
          depAmount += round(interestForDay * 100.0) / 100.0;
        TaxCalc(bufLocalTime, &currentDate, &inputData.tmEndDate, taxRate,
                &resForTax);
      } else if (*inputData.freqPayStr == "at the end") {
        if (currentDate == mktime(&inputData.tmEndDate)) {
          interest = round(interest * 100.0) / 100.0;
          tax = (interest - 150000.0) * (taxRate / 100.0);
          if (inputData.isCapitalization) depAmount += interest;
        }
      } else {
        accruedInterest += interestForDay;
        if (currentDate == nextTimePay ||
            currentDate == mktime(&inputData.tmEndDate)) {
          accruedInterest = round(accruedInterest * 100.0) / 100.0;
          interest = round(interest * 100.0) / 100.0;
          resForTax += accruedInterest;
          if (inputData.isCapitalization)
            depAmount += round(accruedInterest * 100.0) / 100.0;
          accruedInterest = 0;
          IncreaseNextTimePay(&nextTimePay, inputData.freqPayStr);
        }
        TaxCalc(bufLocalTime, &currentDate, &inputData.tmEndDate, taxRate,
                &resForTax);
      }
      CorrectAmount(inputData.withdrawalReplData, currentDate);
    }
  }
}

void DeposCalc::IncreaseNextTimePay(time_t *nextTimePay,
                                    const std::string *freqPay) {
  tm *nextTimePayTM = localtime(nextTimePay);
  if (*freqPay == "every week") {
    *nextTimePay += 7 * 24 * 60 * 60;
    nextTimePayTM = localtime(nextTimePay);
  } else if (*freqPay == "once a month") {
    AddMonths(nextTimePayTM, 1);
  } else if (*freqPay == "once a quarter") {
    AddMonths(nextTimePayTM, 3);
  } else if (*freqPay == "once in half-year") {
    AddMonths(nextTimePayTM, 6);
  } else if (*freqPay == "once a year") {
    AddMonths(nextTimePayTM, 12);
  }
  *nextTimePay = mktime(nextTimePayTM);
}

void DeposCalc::AddMonths(tm *nextTimePayTM, int numberMonth) {
  int monthDay = nextTimePayTM->tm_mday;
  int nextMon = (nextTimePayTM->tm_mon + numberMonth) % 12;
  int numberDayAtNextMonth = NumberDayAtMonth(nextMon);
  if (nextTimePayTM->tm_mon > 11 - numberMonth) ++nextTimePayTM->tm_year;
  if (nextMon == 1 && IsLeap(nextTimePayTM->tm_year)) ++numberDayAtNextMonth;
  nextTimePayTM->tm_mon = nextMon;
  if (monthDay > numberDayAtNextMonth) {
    nextTimePayTM->tm_mday = monthDay - numberDayAtNextMonth;
    ++nextTimePayTM->tm_mon;
  }
}

int DeposCalc::NumberDayAtMonth(int mon) {
  int answer = 0;
  if (mon == 3 || mon == 5 || mon == 8 || mon == 10)
    answer = 30;
  else if (mon == 1)
    answer = 28;
  else
    answer = 31;
  return answer;
}

bool DeposCalc::IsLeap(int year) {
  return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

void DeposCalc::TaxCalc(tm *bufLocalTime, const time_t *currentDate,
                        tm *tmEndDate, double taxRate, double *resForTax) {
  if ((bufLocalTime->tm_mon == 11 && bufLocalTime->tm_mday == 31) ||
      *currentDate == mktime(tmEndDate)) {
    double buf = (*resForTax - 150000.0) * (taxRate / 100.0);
    buf = round(buf * 100.0) / 100.0;
    if (buf > 0) tax += buf;
    *resForTax = 0;
  }
}

int DeposCalc::BankRound(double num) { return int(num / 2.0 + 0.5) * 2; }

void DeposCalc::CorrectAmount(
    const std::multimap<time_t, std::string> *withdrawalReplData,
    time_t currentDate) {
  auto val = withdrawalReplData->find(currentDate);
  if (val != withdrawalReplData->end()) {
    double repl = stod(val->second);
    depAmount += repl;
  }
}

void DeposCalc::Reset() {
  interest = 0;
  tax = 0;
  depAmount = 0;
}

double DeposCalc::GetInterest() { return interest; }
double DeposCalc::GetTax() { return tax; }
double DeposCalc::GetDepAmount() { return depAmount; }
int DeposCalc::GetError() { return error.error; }

}  // namespace s21
