#ifndef CPP3_SMARTCALC_V2_0_2_SRC_VIEW_MAINCALCWINDOW_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_VIEW_MAINCALCWINDOW_H_

#include <QWidget>

#include "../controller/allcontrollers.h"

namespace Ui {
class MainCalcWindow;
}

class MainCalcWindow : public QWidget {
  Q_OBJECT

 public:
  explicit MainCalcWindow(bool p, s21::AllControllers *ac);
  ~MainCalcWindow();

 private slots:
  void ClickButton();
  void on_creditCalcButton_clicked();
  void on_plotCalcButton_clicked();
  void on_mainCalcButton_clicked();
  void on_deposCalcButton_clicked();

 private:
  Ui::MainCalcWindow *ui;
  s21::AllControllers *allControllers;
  int countBracket;
  bool needSetX;
  bool plotting;
  void SetNumber(QString *textLine, const QString *buttonText,
                 const QChar *frontChLine);
  void ClearLine();
  void SetNegate(const QChar *frontChLine, QString *textLine);
  void SetOperator(const QString *textLine, const QString *textLabel,
                   const QString *buttonText, const QChar *backChLabel);
  void SetResult(QString *textLine, QString *textLabel,
                 const QChar *frontChLine);
  void SetFunction(const QString *textLine, const QString *textLabel,
                   const QString *buttonText, const QChar *backChLabel,
                   const QChar *frontChLine);
};

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_VIEW_MAINCALCWINDOW_H_
