#include <QApplication>

#include "maincalcwindow.h"

int main(int argc, char *argv[]) {
  s21::MainCalc mainModel;
  s21::PlotCalc plotModel;
  s21::CreditCalc creditModel;
  s21::DeposCalc deposModel;
  s21::CreditCalcController creditController(&creditModel);
  s21::DeposCalcController deposController(&deposModel);
  s21::MainCalcController mainController(&mainModel);
  s21::PlotCalcController plotController(&plotModel);
  s21::AllControllers allControllers(creditController, deposController,
                                     mainController, plotController);
  QApplication a(argc, argv);
  MainCalcWindow w(false, &allControllers);
  w.show();
  return a.exec();
}
