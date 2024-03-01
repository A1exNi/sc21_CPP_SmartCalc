#include "plotcalccontroller.h"

namespace s21 {

std::vector<double> PlotCalcController::PlotCalcResult(std::string expression,
                                                       double xMin, double xMax,
                                                       size_t numberPoints) {
  return model->PlotCalcResult(&expression, xMin, xMax, numberPoints);
}

bool PlotCalcController::GetError() { return model->GetError(); }

}  // namespace s21
