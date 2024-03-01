#ifndef CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_ALLCONTROLLERS_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_ALLCONTROLLERS_H_

#include "creditcalccontroller.h"
#include "deposcalccontroller.h"
#include "maincalccontroller.h"
#include "plotcalccontroller.h"

namespace s21 {

struct AllControllers {
  AllControllers(CreditCalcController cc, DeposCalcController dc,
                 MainCalcController mc, PlotCalcController pc)
      : creditController(cc),
        deposController(dc),
        mainController(mc),
        plotController(pc){};
  CreditCalcController creditController;
  DeposCalcController deposController;
  MainCalcController mainController;
  PlotCalcController plotController;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_ALLCONTROLLERS_H_