#ifndef CPP3_SMARTCALC_V2_0_2_SRC_MODEL_DEPOSCALC_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_MODEL_DEPOSCALC_H_

#include <map>
#include <string>

#include "creditdeposerror.h"

namespace s21 {

struct InputDataDeposCalc {
  std::string amountStr;
  std::string taxRateStr;
  std::string interestRateStr;
  const std::string *freqPayStr;
  tm tmStartDate;
  tm tmEndDate;
  bool isCapitalization;
  const std::multimap<time_t, std::string> *withdrawalReplData;
};

class DeposCalc {
 public:
  void DeposCalcResult(InputDataDeposCalc inputData);
  double GetInterest();
  double GetTax();
  double GetDepAmount();
  void Reset();
  int GetError();
  void CheckAmountError(std::string amountStr);

 private:
  CreditDeposError error;
  double interest{};
  double tax{};
  double depAmount{};
  void CorrectAmount(
      const std::multimap<time_t, std::string> *withdrawalReplData,
      time_t currentDate);
  int BankRound(double num);
  void TaxCalc(tm *bufLocalTime, const time_t *currentDate, tm *tmEndDate,
               double taxRate, double *resForTax);
  bool IsLeap(int year);
  int NumberDayAtMonth(int mon);
  void AddMonths(tm *nextTimePayTM, int numberMonth);
  void IncreaseNextTimePay(time_t *nextTimePay, const std::string *freqPay);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_MODEL_DEPOSCALC_H_
