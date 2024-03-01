#ifndef CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_MAINCALCCONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_MAINCALCCONTROLLER_H_

#include <string>

#include "../model/maincalc.h"

namespace s21 {

class MainCalcController {
 public:
  explicit MainCalcController(MainCalc *m) : model(m) {}
  double MainCalcResult(const std::string *expression,
                        const std::string *xValue);
  int GetError();

 private:
  MainCalc *model;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_MAINCALCCONTROLLER_H_
