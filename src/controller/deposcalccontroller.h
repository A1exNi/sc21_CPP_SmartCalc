#ifndef CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_DEPOSCALCCONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_DEPOSCALCCONTROLLER_H_

#include <string>

#include "../model/deposcalc.h"
#include "../view/datadeposcreditview.h"

namespace s21 {

class DeposCalcController {
 public:
  explicit DeposCalcController(DeposCalc *m) : model(m) {}
  void DeposCalcResult(OutputDataDeposView inputDataView);
  void CheckAmountError(const std::string *amountStr);
  int GetError();
  double GetInterest();
  double GetTax();
  double GetDepAmount();

 private:
  DeposCalc *model;
  InputDataDeposCalc ToCalcData(OutputDataDeposView inputDataView);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_DEPOSCALCCONTROLLER_H_
