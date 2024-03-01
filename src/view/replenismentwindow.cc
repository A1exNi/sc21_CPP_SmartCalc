#include "replenismentwindow.h"

#include "ui_replenismentwindow.h"

ReplenismentWindow::ReplenismentWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::ReplenismentWindow) {
  ui->setupUi(this);
  ui->dateEdit->setDate(QDate::currentDate());
}

ReplenismentWindow::~ReplenismentWindow() { delete ui; }

std::pair<QDateTime, QString> ReplenismentWindow::GetData() {
  QString amount;
  if (ui->radioButtonWithdrawal->isChecked()) {
    amount = "-" + ui->lineEdit->text();
  } else {
    amount = ui->lineEdit->text();
  }
  return {ui->dateEdit->dateTime(), amount};
}
