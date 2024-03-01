#include "deposcalccontroller.h"

#include <iostream>

namespace s21 {

void DeposCalcController::DeposCalcResult(OutputDataDeposView inputDataView) {
  InputDataDeposCalc inputDataCalc = ToCalcData(inputDataView);
  model->DeposCalcResult(inputDataCalc);
}

InputDataDeposCalc DeposCalcController::ToCalcData(
    OutputDataDeposView inputDataView) {
  InputDataDeposCalc inputDataCalc;
  inputDataCalc.amountStr = inputDataView.amountStr;
  inputDataCalc.taxRateStr = inputDataView.taxRateStr;
  inputDataCalc.interestRateStr = inputDataView.interestRateStr;
  inputDataCalc.freqPayStr = &inputDataView.freqPayStr;
  inputDataCalc.tmStartDate = inputDataView.tmStartDate;
  inputDataCalc.tmEndDate = inputDataView.tmEndDate;
  inputDataCalc.isCapitalization = inputDataView.isCapitalization;
  inputDataCalc.withdrawalReplData = &inputDataView.withdrawalReplData;
  return inputDataCalc;
}

void DeposCalcController::CheckAmountError(const std::string *amountStr) {
  model->CheckAmountError(*amountStr);
}

int DeposCalcController::GetError() { return model->GetError(); }
double DeposCalcController::GetInterest() { return model->GetInterest(); }
double DeposCalcController::GetTax() { return model->GetTax(); }
double DeposCalcController::GetDepAmount() { return model->GetDepAmount(); }

}  // namespace s21
