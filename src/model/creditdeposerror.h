#ifndef CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CREDITDEPOSERROR_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CREDITDEPOSERROR_H_

#include <string>

namespace s21 {

enum Error { NO = 0, AMOUNT = 1, TIME = 2, RATE = 3 };

class CreditDeposError {
 public:
  void Reset();
  void CheckAmountError(std::string amountStr);
  void CheckTimeError(std::string timeStr, char yearsMonthsDays);
  void CheckRateError(std::string rateStr);
  int error{};
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CREDITDEPOSERROR_H_