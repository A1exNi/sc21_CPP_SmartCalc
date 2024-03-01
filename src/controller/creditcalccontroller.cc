#include "creditcalccontroller.h"

namespace s21 {

void CreditCalcController::CreditCalcResult(
    OutputDataCreditView inputDataView) {
  InputDataCreditCalc inputDataCalc = ToCalcData(inputDataView);
  model->CreditCalcResult(inputDataCalc);
}

InputDataCreditCalc CreditCalcController::ToCalcData(
    OutputDataCreditView inputDataView) {
  InputDataCreditCalc inputDataCalc;
  inputDataCalc.amountStr = inputDataView.amountStr;
  inputDataCalc.timeStr = inputDataView.timeStr;
  inputDataCalc.rateStr = inputDataView.rateStr;
  inputDataCalc.yearsMonthsDays = inputDataView.yearsMonthsDays;
  inputDataCalc.annuity = inputDataView.annuity;
  return inputDataCalc;
}

int CreditCalcController::GetError() { return model->GetError(); }
double CreditCalcController::GetOverPay() { return model->GetOverPay(); }
double CreditCalcController::GetTotalPay() { return model->GetTotalPay(); }
std::vector<double> CreditCalcController::GetMonPay() {
  return model->GetMonPay();
}

}  // namespace s21
