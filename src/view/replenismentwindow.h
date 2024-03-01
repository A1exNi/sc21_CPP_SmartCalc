#ifndef CPP3_SMARTCALC_V2_0_2_SRC_VIEW_REPLENISMENTWINDOW_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_VIEW_REPLENISMENTWINDOW_H_

#include <QDialog>

namespace Ui {
class ReplenismentWindow;
}

class ReplenismentWindow : public QDialog {
  Q_OBJECT

 public:
  explicit ReplenismentWindow(QWidget *parent = nullptr);
  ~ReplenismentWindow();
  std::pair<QDateTime, QString> GetData();

 private:
  Ui::ReplenismentWindow *ui;
};

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_VIEW_REPLENISMENTWINDOW_H_
