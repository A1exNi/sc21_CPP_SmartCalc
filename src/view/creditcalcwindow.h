#ifndef CPP3_SMARTCALC_V2_0_2_SRC_VIEW_CREDITCALCWINDOW_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_VIEW_CREDITCALCWINDOW_H_

#include <QWidget>

#include "../controller/allcontrollers.h"

namespace Ui {
class CreditCalcWindow;
}

class CreditCalcWindow : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalcWindow(s21::AllControllers *ac);
  ~CreditCalcWindow();

 private slots:
  void on_mainCalcButton_clicked();
  void on_plotCalcButton_clicked();
  void on_deposCalcButton_clicked();
  void on_pushButton_clicked();

 private:
  Ui::CreditCalcWindow *ui;
  s21::AllControllers *allControllers;
  s21::OutputDataCreditView GetDataForOutput();
};

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_VIEW_CREDITCALCWINDOW_H_
