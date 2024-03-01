#include "plotwindow.h"

#include <iostream>

#include "ui_plotwindow.h"

PlotWindow::PlotWindow(s21::PlotCalcController *c, QString e)
    : ui(new Ui::PlotWindow),
      controller(c),
      expression(e),
      countBracket(0),
      xMin(-50),
      xMax(50),
      yMin(0),
      yMax(0),
      numberPoints(1000000) {
  ui->setupUi(this);
  DrawGraph();
}

PlotWindow::~PlotWindow() { delete ui; }

void PlotWindow::DrawGraph() {
  std::vector<double> x(numberPoints);
  for (size_t i = 0; i < numberPoints; ++i) {
    x[i] = xMin + i * (xMax - xMin) / numberPoints;
  }
  std::vector<double> y = controller->PlotCalcResult(expression.toStdString(),
                                                     xMin, xMax, numberPoints);
  if (yMin == 0 && yMax == 0) {
    yMin = *std::min_element(y.begin(), y.end());
    yMax = *std::max_element(y.begin(), y.end());
  }
  ui->spinBoxXMax->setRange(1, 1000000);
  ui->spinBoxXMin->setRange(-1000000, -1);
  ui->spinBoxXMax->setValue(xMax);
  ui->spinBoxXMin->setValue(xMin);
  ui->spinBoxYMax->setRange(1, 1000000);
  ui->spinBoxYMin->setRange(-1000000, -1);
  ui->spinBoxYMax->setValue(yMax);
  ui->spinBoxYMin->setValue(yMin);
  ui->spinBoxNumPoints->setRange(10, 2000000);
  ui->spinBoxNumPoints->setValue(numberPoints);
  ui->widget->addGraph();
  ui->widget->xAxis->setLabel("X");
  ui->widget->yAxis->setLabel("Y");
  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);
  ui->labelExpression->setText(expression);
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
  ui->widget->graph(0)->setData(QVector<double>(x.begin(), x.end()),
                                QVector<double>(y.begin(), y.end()));
  ui->widget->replot();
}

void PlotWindow::on_pushButtonAccept_clicked() {
  xMin = ui->spinBoxXMin->value();
  xMax = ui->spinBoxXMax->value();
  yMin = ui->spinBoxYMin->value();
  yMax = ui->spinBoxYMax->value();
  numberPoints = ui->spinBoxNumPoints->value();
  DrawGraph();
}