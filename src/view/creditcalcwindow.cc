#include "creditcalcwindow.h"

#include "deposcalcwindow.h"
#include "maincalcwindow.h"
#include "ui_creditcalcwindow.h"

CreditCalcWindow::CreditCalcWindow(s21::AllControllers *ac)
    : ui(new Ui::CreditCalcWindow), allControllers(ac) {
  ui->setupUi(this);
}

CreditCalcWindow::~CreditCalcWindow() { delete ui; }

void CreditCalcWindow::on_mainCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  MainCalcWindow *window = new MainCalcWindow(false, allControllers);
  window->resize(width, height);
  window->show();
}

void CreditCalcWindow::on_plotCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  MainCalcWindow *window = new MainCalcWindow(true, allControllers);
  window->resize(width, height);
  window->show();
}

void CreditCalcWindow::on_deposCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  DeposCalcWindow *window = new DeposCalcWindow(allControllers);
  window->resize(width, height);
  window->show();
}

void CreditCalcWindow::on_pushButton_clicked() {
  s21::OutputDataCreditView outputData = GetDataForOutput();
  allControllers->creditController.CreditCalcResult(outputData);
  ui->ListWidget->clear();
  if (allControllers->creditController.GetError() == s21::NO) {
    ui->ListWidget->addItem(
        "Overpayment:\t " +
        QString::number(allControllers->creditController.GetOverPay(), 'g',
                        10));
    ui->ListWidget->addItem(
        "Total payment:\t" +
        QString::number(allControllers->creditController.GetTotalPay(), 'g',
                        10));
    ui->ListWidget->addItem("Monthly payment:\t");
    std::vector<double> monPay = allControllers->creditController.GetMonPay();
    for (auto &&value : monPay) {
      ui->ListWidget->addItem("\t\t" + QString::number(value, 'g', 10));
    }
  } else if (allControllers->creditController.GetError() == s21::AMOUNT) {
    ui->ListWidget->addItem(
        "*AMOUNT OF CREDIT can be in the format \"999.99\". The minimum "
        "allowed value is 1.");
  } else if (allControllers->creditController.GetError() == s21::TIME) {
    ui->ListWidget->addItem(
        "*CREDIT TIME must be an integer in the range from 1 to 50 for "
        "\"yeara\" and from 1 to 600 for \"month\"");
  } else if (allControllers->creditController.GetError() == s21::RATE) {
    ui->ListWidget->addItem("*INTEREST RATE must be between 0.01 and 999.");
  } else {
    ui->ListWidget->addItem("*ERROR.");
  }
}

s21::OutputDataCreditView CreditCalcWindow::GetDataForOutput() {
  s21::OutputDataCreditView outputData;
  outputData.amountStr = ui->lineEditAmount->text().toStdString();
  outputData.timeStr = ui->lineEditTime->text().toStdString();
  outputData.rateStr = ui->lineEditRate->text().toStdString();
  outputData.yearsMonthsDays = 'm';
  if (ui->comboBox->currentText() == "Years") outputData.yearsMonthsDays = 'y';
  outputData.annuity = ui->radioButtonAnnuity->isChecked();
  return outputData;
}
