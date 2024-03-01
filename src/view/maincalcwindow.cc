#include "maincalcwindow.h"

#include <iostream>

#include "creditcalcwindow.h"
#include "deposcalcwindow.h"
#include "plotwindow.h"
#include "ui_maincalcwindow.h"

MainCalcWindow::MainCalcWindow(bool p, s21::AllControllers *ac)
    : ui(new Ui::MainCalcWindow),
      allControllers(ac),
      countBracket(0),
      needSetX(false),
      plotting(p) {
  ui->setupUi(this);
  if (plotting) setWindowTitle("SmartCalcV2.0 - PlotCalc");
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_abs, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_br_close, SIGNAL(clicked()), this,
          SLOT(ClickButton()));
  connect(ui->pushButton_br_open, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_c, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_unar, SIGNAL(clicked()), this, SLOT(ClickButton()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(ClickButton()));
}

MainCalcWindow::~MainCalcWindow() { delete ui; }

void MainCalcWindow::on_creditCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  CreditCalcWindow *window = new CreditCalcWindow(allControllers);
  window->resize(width, height);
  window->show();
}

void MainCalcWindow::on_plotCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  MainCalcWindow *window = new MainCalcWindow(true, allControllers);
  window->resize(width, height);
  window->show();
}

void MainCalcWindow::on_mainCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  MainCalcWindow *window = new MainCalcWindow(false, allControllers);
  window->resize(width, height);
  window->show();
}

void MainCalcWindow::on_deposCalcButton_clicked() {
  int width = this->width();
  int height = this->height();
  close();
  DeposCalcWindow *window = new DeposCalcWindow(allControllers);
  window->resize(width, height);
  window->show();
}

void MainCalcWindow::ClickButton() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonText = button->text();
  QString textLabel = ui->resultLabel->text();
  QString textLine = ui->resultLine->text();
  QChar backChLabel, frontChLine;
  if (textLabel.length() > 0) backChLabel = textLabel.back();
  if (textLine.length() > 0) frontChLine = textLine.front();
  if (buttonText.length() == 0 && frontChLine != 'S') {
    textLine.remove(textLine.length() - 1, 1);
    ui->resultLine->setText(textLine);
  } else if ((buttonText.front() >= '0' && buttonText.front() <= '9') ||
             buttonText == ".") {
    SetNumber(&textLine, &buttonText, &frontChLine);
  } else if (buttonText == "C") {
    ClearLine();
  } else if (buttonText == "+/-" && textLine != "x" && textLine.length() > 0) {
    SetNegate(&frontChLine, &textLine);
  } else if (buttonText == ")" && frontChLine != 'S') {
    if (countBracket > 0 && (textLine.length() > 0 || backChLabel == ')')) {
      ui->resultLabel->setText(textLabel + textLine + buttonText);
      ui->resultLine->setText("");
      --countBracket;
    }
  } else if (buttonText == "(" && frontChLine != 'S') {
    if (textLine.length() == 0 && backChLabel != ')') {
      ui->resultLabel->setText(textLabel + buttonText);
      ++countBracket;
    }
  } else if ((buttonText == "+" || buttonText == "-" || buttonText == "/" ||
              buttonText == "^" || buttonText == "mod" || buttonText == "x") &&
             frontChLine != 'S') {
    SetOperator(&textLine, &textLabel, &buttonText, &backChLabel);
  } else if (buttonText == "=" && textLabel.length() > 0 && countBracket == 0) {
    SetResult(&textLine, &textLabel, &frontChLine);
  } else if (buttonText == "X" && frontChLine != 'S') {
    needSetX = true;
    ui->resultLine->setText("x");
  } else if (buttonText == "e" && !textLine.contains("e") &&
             textLine.length() > 0) {
    if (textLine.back() != '.') ui->resultLine->setText(textLine + "e");
  } else {
    SetFunction(&textLine, &textLabel, &buttonText, &backChLabel, &frontChLine);
  }
}

void MainCalcWindow::SetNumber(QString *textLine, const QString *buttonText,
                               const QChar *frontChLine) {
  bool setX = false;
  if (*frontChLine == 'S') {
    *textLine = textLine->remove("Set x: ");
    setX = true;
  }
  if (*buttonText == ".") {
    if (!textLine->contains(".")) ui->resultLine->setText(*textLine + ".");
  } else {
    if (*textLine == "inf") {
      ui->resultLine->setText(*buttonText);
    } else {
      ui->resultLine->setText(*textLine + *buttonText);
    }
  }
  if (setX) ui->resultLine->setText("Set x: " + ui->resultLine->text());
}

void MainCalcWindow::ClearLine() {
  ui->resultLabel->setText("");
  ui->resultLine->setText("");
  countBracket = 0;
  needSetX = false;
}

void MainCalcWindow::SetNegate(const QChar *frontChLine, QString *textLine) {
  bool setX = false;
  if (*frontChLine == 'S') {
    *textLine = textLine->remove("Set x: ");
    setX = true;
  }
  double number = textLine->toDouble() * -1;
  ui->resultLine->setText(QString::number(number));
  if (setX) ui->resultLine->setText("Set x: " + ui->resultLine->text());
}

void MainCalcWindow::SetOperator(const QString *textLine,
                                 const QString *textLabel,
                                 const QString *buttonText,
                                 const QChar *backChLabel) {
  QString bufButtonText = *buttonText;
  if (bufButtonText == "x") bufButtonText = "*";
  if (textLine->length() == 0 && *backChLabel == ')') {
    ui->resultLabel->setText(*textLabel + bufButtonText);
    ui->resultLine->setText("");
  } else if (textLine->length() > 0) {
    if (textLine->back() == 'e') {
      if (bufButtonText == "+" || bufButtonText == "-")
        ui->resultLine->setText(*textLine + bufButtonText);
    } else if (*backChLabel == '(' || *backChLabel == '+' ||
               *backChLabel == '-' || *backChLabel == '/' ||
               *backChLabel == '^' || *backChLabel == 'd' ||
               *backChLabel == '*' || textLabel->length() == 0) {
      ui->resultLabel->setText(*textLabel + *textLine + bufButtonText);
      ui->resultLine->setText("");
    }
  }
}

void MainCalcWindow::SetResult(QString *textLine, QString *textLabel,
                               const QChar *frontChLine) {
  if (plotting) {
    PlotWindow *window =
        new PlotWindow(&allControllers->plotController, *textLabel + *textLine);
    if (allControllers->plotController.GetError()) {
      ui->resultLine->setText("ERROR");
    } else {
      window->show();
    }
  } else {
    if (!needSetX) {
      std::string xValue = "0";
      if (*frontChLine == 'S') {
        *textLine = textLine->remove("Set x: ");
        xValue = textLine->toStdString();
      } else {
        *textLabel = *textLabel + *textLine;
      }
      std::string str = textLabel->toStdString();
      double result =
          allControllers->mainController.MainCalcResult(&str, &xValue);
      if (!allControllers->mainController.GetError()) {
        ui->resultLine->setText(QString::number(result, 'c', 7));
      } else {
        ui->resultLine->setText("ERROR");
      }
      ui->resultLabel->setText("");
    } else {
      ui->resultLabel->setText(*textLabel + *textLine);
      ui->resultLine->setText("Set x: ");
      needSetX = false;
    }
  }
}

void MainCalcWindow::SetFunction(const QString *textLine,
                                 const QString *textLabel,
                                 const QString *buttonText,
                                 const QChar *backChLabel,
                                 const QChar *frontChLine) {
  if (*buttonText != ")" && *backChLabel != ')' && *frontChLine != 'S' &&
      *buttonText != "=" && *buttonText != "+/-" && *buttonText != "e") {
    if (*textLine == "") {
      ui->resultLabel->setText(*textLabel + *buttonText + "(");
      ++countBracket;
    } else {
      ui->resultLabel->setText(*textLabel + *buttonText + "(" + *textLine +
                               ")");
    }
    ui->resultLine->setText("");
  } else {
    if (countBracket > 0 && textLine->length() > 0 && *frontChLine != 'S' &&
        *buttonText != "=" && *buttonText != "+/-" && *buttonText != "e") {
      ui->resultLabel->setText(*textLabel + *textLine + *buttonText);
      ui->resultLine->setText("");
    }
  }
}