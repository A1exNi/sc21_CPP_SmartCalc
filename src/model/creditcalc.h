#ifndef CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CREDITCALC_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CREDITCALC_H_

#include <string>
#include <vector>

#include "creditdeposerror.h"

namespace s21 {

struct InputDataCreditCalc {
  std::string amountStr;
  std::string timeStr;
  std::string rateStr;
  char yearsMonthsDays;
  bool annuity;
};

class CreditCalc {
 public:
  void CreditCalcResult(InputDataCreditCalc inputData);
  std::vector<double> GetMonPay();
  int GetError();
  double GetOverPay();
  double GetTotalPay();
  void Reset();

 private:
  CreditDeposError error;
  std::vector<double> monPay;
  double overPay{};
  double totalPay{};
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CREDITCALC_H_
