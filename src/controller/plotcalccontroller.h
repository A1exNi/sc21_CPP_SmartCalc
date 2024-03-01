#ifndef CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_PLOTCALCCONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_PLOTCALCCONTROLLER_H_

#include <string>

#include "../model/plotcalc.h"

namespace s21 {

class PlotCalcController {
 public:
  explicit PlotCalcController(PlotCalc *m) : model(m) {}
  std::vector<double> PlotCalcResult(std::string expression, double xMin,
                                     double xMax, size_t numberPoints);
  bool GetError();

 private:
  PlotCalc *model;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_PLOTCALCCONTROLLER_H_
