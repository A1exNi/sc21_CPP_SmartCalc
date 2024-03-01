#include "plotcalc.h"

#include "maincalc.h"

namespace s21 {

std::vector<double> PlotCalc::PlotCalcResult(const std::string *expression,
                                             double xMin, double xMax,
                                             size_t numberPoints) {
  Reset();
  std::vector<double> result(numberPoints);
  MainCalc mainCalc;
  for (size_t i = 0; i < numberPoints && !error; ++i) {
    std::string xValue =
        std::to_string(xMin + i * (xMax - xMin) / numberPoints);
    mainCalc.MainCalcResult(expression, &xValue);
    error = mainCalc.GetError();
    if (!error) result[i] = mainCalc.GetResult();
  }
  return result;
}

void PlotCalc::Reset() { error = false; }
bool PlotCalc::GetError() { return error; }

}  // namespace s21
