#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_PLOTCALC_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_PLOTCALC_H_

#include <string>
#include <vector>

namespace s21 {

class PlotCalc {
 public:
  std::vector<double> PlotCalcResult(const std::string *expression, double xMin,
                                     double xMax, size_t numberPoints);
  void Reset();
  bool GetError();

 private:
  bool error{};
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_PLOTCALC_H_