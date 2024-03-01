#include "deposcalcwindow.h"

#include <QDate>
#include <iomanip>

#include "creditcalcwindow.h"
#include "maincalcwindow.h"
#include "replenismentwindow.h"
#include "ui_deposcalcwindow.h"

DeposCalcWindow::DeposCalcWindow(s21::AllControllers *ac)
    : ui(new Ui::DeposCalcWindow), allControllers(ac) {
  ui->setupUi(this);
}

DeposCalcWindow::~DeposCalcWindow() { delete ui; }

void DeposCalcWindow::on_creditCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  CreditCalcWindow *window = new CreditCalcWindow(allControllers);
  window->resize(width, height);
  window->show();
}

void DeposCalcWindow::on_plotCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  MainCalcWindow *window = new MainCalcWindow(true, allControllers);
  window->resize(width, height);
  window->show();
}

void DeposCalcWindow::on_mainCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  MainCalcWindow *window = new MainCalcWindow(false, allControllers);
  window->resize(width, height);
  window->show();
}

void DeposCalcWindow::on_pushButtonCalc_clicked() {
  bool timeIsOk;
  int time = ui->lineEditTime->text().toInt(&timeIsOk);
  if (timeIsOk) {
    if (ui->comboBoxTime->currentText() == "Years" && (time < 1 || time > 50))
      timeIsOk = false;
    if (ui->comboBoxTime->currentText() == "Months" && (time < 1 || time > 600))
      timeIsOk = false;
    if (ui->comboBoxTime->currentText() == "Days" && (time < 1 || time > 18250))
      timeIsOk = false;
  }
  if (timeIsOk) {
    s21::OutputDataDeposView outputData = GetDataForOutput();
    allControllers->deposController.DeposCalcResult(outputData);
  }
  SetResult(timeIsOk);
}

s21::OutputDataDeposView DeposCalcWindow::GetDataForOutput() {
  s21::OutputDataDeposView outputData;
  outputData.amountStr = ui->lineEditAmount->text().toStdString();
  outputData.taxRateStr = ui->lineEditTaxRate->text().toStdString();
  outputData.interestRateStr = ui->lineEditInterestRate->text().toStdString();
  outputData.freqPayStr = ui->comboBoxFreqPay->currentText().toStdString();
  outputData.tmStartDate = GetStartDate();
  outputData.tmEndDate = GetEndDate();
  outputData.isCapitalization = ui->checkBoxCapital->checkState();
  outputData.withdrawalReplData = GetWithdrawalRepl();
  return outputData;
}

tm DeposCalcWindow::GetStartDate() {
  QDate startDate = QDate::currentDate();
  tm tmStartDate{};
  tmStartDate.tm_year = startDate.year() - 1900;
  tmStartDate.tm_mon = startDate.month() - 1;
  tmStartDate.tm_mday = startDate.day();
  return tmStartDate;
}

tm DeposCalcWindow::GetEndDate() {
  QDate endDate = QDate::currentDate();
  if (ui->comboBoxTime->currentText() == "Months") {
    endDate = endDate.addMonths(ui->lineEditTime->text().toInt());
  } else if (ui->comboBoxTime->currentText() == "Years") {
    endDate = endDate.addYears(ui->lineEditTime->text().toInt());
  } else if (ui->comboBoxTime->currentText() == "Days") {
    endDate = endDate.addDays(ui->lineEditTime->text().toInt());
  }
  tm tmEndDate{};
  tmEndDate.tm_year = endDate.year() - 1900;
  tmEndDate.tm_mon = endDate.month() - 1;
  tmEndDate.tm_mday = endDate.day();
  return tmEndDate;
}

std::multimap<time_t, std::string> DeposCalcWindow::GetWithdrawalRepl() {
  std::multimap<time_t, std::string> withdrawalReplData;
  for (int i = 0; i < ui->ListWidget->count(); ++i) {
    QListWidgetItem *item = ui->ListWidget->item(i);
    QStringList str = item->text().split("\t");
    QDateTime date = QDateTime::fromString(str.front(), "dd.MM.yy");
    withdrawalReplData.insert(
        {date.toSecsSinceEpoch() + 70, str.back().toStdString()});
  }
  return withdrawalReplData;
}

void DeposCalcWindow::SetResult(bool timeIsOk) {
  ui->ListWidgetCalc->clear();
  if (allControllers->deposController.GetError() == s21::NO && timeIsOk) {
    ui->ListWidgetCalc->addItem(
        "Accrued interest:\t" +
        QString::number(allControllers->deposController.GetInterest(), 'g',
                        10));
    ui->ListWidgetCalc->addItem(
        "Tax:\t\t" +
        QString::number(allControllers->deposController.GetTax(), 'g', 10));
    ui->ListWidgetCalc->addItem(
        "Deposit amount:\t" +
        QString::number(allControllers->deposController.GetDepAmount(), 'g',
                        10));
  } else if (allControllers->deposController.GetError() == s21::AMOUNT) {
    ui->ListWidgetCalc->addItem(
        "*AMOUNT OF CREDIT can be in the format \"999.99\". The minimum "
        "allowed value is 1.");
  } else if (!timeIsOk) {
    ui->ListWidgetCalc->addItem(
        "*CREDIT TIME must be an integer in the range from 1 to 50 for "
        "\"yeara\" and from 1 to 600 for \"month\"");
  } else if (allControllers->deposController.GetError() == s21::RATE) {
    ui->ListWidgetCalc->addItem("*INTEREST RATE must be between 0.01 and 999.");
  } else {
    ui->ListWidgetCalc->addItem("*ERROR.");
  }
}

void DeposCalcWindow::on_pushButtonRepl_clicked() {
  ReplenismentWindow dialog(this);
  std::pair<QDateTime, QString> data;
  ui->ListWidgetCalc->clear();
  if (dialog.exec() == QDialog::Accepted) {
    data = dialog.GetData();
    std::string amount = data.second.toStdString();
    if (amount[0] == '-') {
      std::string str = &amount[1];
      allControllers->deposController.CheckAmountError(&str);
    } else {
      allControllers->deposController.CheckAmountError(&amount);
    }
    if (allControllers->deposController.GetError() == s21::NO) {
      ui->ListWidget->addItem(data.first.toString("dd.MM.yy") + "\t" +
                              data.second);
    } else {
      ui->ListWidgetCalc->addItem(
          "*AMOUNT can be in the format \"999.99\". The minimum allowed value "
          "is 1.");
    }
  }
}

void DeposCalcWindow::on_ListWidget_itemDoubleClicked(QListWidgetItem *item) {
  delete item;
}