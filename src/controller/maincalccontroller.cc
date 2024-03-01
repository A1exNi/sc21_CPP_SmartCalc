#include "maincalccontroller.h"

#include <iostream>

namespace s21 {

double MainCalcController::MainCalcResult(const std::string *expression,
                                          const std::string *xValue) {
  model->MainCalcResult(expression, xValue);
  return model->GetResult();
}

int MainCalcController::GetError() { return model->GetError(); }

}  // namespace s21
