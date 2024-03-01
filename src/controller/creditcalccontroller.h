#ifndef CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_CREDITCALCCONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_CREDITCALCCONTROLLER_H_

#include "../model/creditcalc.h"
#include "../view/datadeposcreditview.h"

namespace s21 {

class CreditCalcController {
 public:
  explicit CreditCalcController(CreditCalc *m) : model(m) {}
  void CreditCalcResult(OutputDataCreditView inputDataView);
  int GetError();
  double GetOverPay();
  double GetTotalPay();
  std::vector<double> GetMonPay();

 private:
  CreditCalc *model;
  InputDataCreditCalc ToCalcData(OutputDataCreditView inputDataView);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_CREDITCALCCONTROLLER_H_
