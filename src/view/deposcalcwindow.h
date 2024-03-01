#ifndef CPP3_SMARTCALC_V2_0_2_SRC_VIEW_DEPOSCALCWINDOW_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_VIEW_DEPOSCALCWINDOW_H_

#include <QListWidgetItem>
#include <QWidget>

#include "../controller/allcontrollers.h"
#include "datadeposcreditview.h"

namespace Ui {
class DeposCalcWindow;
}

class DeposCalcWindow : public QWidget {
  Q_OBJECT

 public:
  explicit DeposCalcWindow(s21::AllControllers *ac);
  ~DeposCalcWindow();

 private slots:
  void on_creditCalcButton_clicked();
  void on_plotCalcButton_clicked();
  void on_mainCalcButton_clicked();
  void on_pushButtonCalc_clicked();
  void on_pushButtonRepl_clicked();
  void on_ListWidget_itemDoubleClicked(QListWidgetItem *item);

 private:
  Ui::DeposCalcWindow *ui;
  s21::AllControllers *allControllers;
  s21::OutputDataDeposView GetDataForOutput();
  tm GetStartDate();
  tm GetEndDate();
  std::multimap<time_t, std::string> GetWithdrawalRepl();
  void SetResult(bool timeIsOk);
};

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_VIEW_DEPOSCALCWINDOW_H_