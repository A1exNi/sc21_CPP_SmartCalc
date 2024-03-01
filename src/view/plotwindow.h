#ifndef CPP3_SMARTCALC_V2_0_2_SRC_VIEW_PLOTWINDOW_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_VIEW_PLOTWINDOW_H_

#include <QWidget>

#include "../controller/plotcalccontroller.h"

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QWidget {
  Q_OBJECT

 public:
  explicit PlotWindow(s21::PlotCalcController *c, QString e);
  ~PlotWindow();

 private slots:
  void on_pushButtonAccept_clicked();

 private:
  Ui::PlotWindow *ui;
  s21::PlotCalcController *controller;
  QString expression;
  int countBracket;
  double xMin, xMax, yMin, yMax;
  size_t numberPoints;
  void DrawGraph();
};

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_VIEW_PLOTWINDOW_H_
