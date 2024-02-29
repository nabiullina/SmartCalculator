#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      expCalcController(new s21::ExpressionCalculator()),
      loanCalcController(new s21::LoanCalculator()) {
  ui->setupUi(this);

  for (auto button : ui->ops->buttons()) {
    connect(button, &QPushButton::clicked, this, &MainWindow::onOpsButtonClick);
  }

  connect(ui->pushButtonAC, &QPushButton::clicked, this,
          &MainWindow::onAcButtonClick);
  connect(ui->pushButtonEq, &QPushButton::clicked, this,
          &MainWindow::onEqButtonClick);
  connect(ui->pushButtonC, &QPushButton::clicked, this,
          &MainWindow::onCButtonClick);
  connect(ui->pushButtonGraph, &QPushButton::clicked, this,
          &MainWindow::onGraphButtonClick);
  connect(ui->pushButtonCalculate, &QPushButton::clicked, this,
          &MainWindow::onCalculateButtonClick);

  ui->paymentsTable->hide();
  ui->monthlyPayment->hide();

  for (int i = 0; i < ui->comboBoxPaymentType->count(); ++i) {
    ui->comboBoxPaymentType->setItemData(i, Qt::AlignRight,
                                         Qt::TextAlignmentRole);
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::update() {
  QPushButton *button = (QPushButton *)sender();
  ui->lineExpression->setText(ui->lineExpression->text() + button->text());
}

/**
 * Handles calculate loan button click event.
 */
void MainWindow::onCalculateButtonClick() {
  ui->labelMonthlyPayment->show();
  ui->paymentsTable->clear();
  ui->paymentsTable->hide();
  ui->monthlyPayment->hide();

  try {
    loanCalcController.setAmount(ui->spinBoxAmount->value());
    loanCalcController.setRate(ui->spinBoxRate->value());
    loanCalcController.setMonths(ui->spinBoxMonths->value());
  } catch (std::exception e) {
    QMessageBox::about(this, "Invalid expression", "Invalid parameters");
    return;
  }

  if (ui->comboBoxPaymentType->currentText() == "differentiated") {
    loanCalcController.CalculateDifferentiatedPayment();

    ui->paymentsTable->show();
    ui->paymentsTable->setColumnCount(1);
    ui->paymentsTable->setShowGrid(true);
    ui->paymentsTable->setHorizontalHeaderLabels({"Payment amount"});
    ui->paymentsTable->horizontalHeader()->setStretchLastSection(true);
    ui->paymentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto payments = loanCalcController.getDifferentiatedPayment();
    auto it = payments.begin();
    int i = 0;

    while (it != payments.end()) {
      ui->paymentsTable->insertRow(i);
      auto item = new QTableWidgetItem(QString("%L1").arg(*it, 0, 'f', 2));
      ui->paymentsTable->setItem(i, 0, item);
      ++it;
      ++i;
    }

    ui->paymentsTable->resizeColumnsToContents();
  } else {
    loanCalcController.CalculateAnnuityPayment();
    ui->monthlyPayment->show();
    ui->monthlyPayment->setText(
        QString("%L1").arg(loanCalcController.getAnnuityPayment(), 0, 'f', 2));
  }

  ui->overpaymentAmount->setText(
      QString("%L1").arg(loanCalcController.getOverpayment(), 0, 'f', 2));
  ui->totalPaymentSum->setText(
      QString("%L1").arg(loanCalcController.getTotalPaymentSum(), 0, 'f', 2));
}

/**
 * Handles operators and operations button click event.
 */
void MainWindow::onOpsButtonClick() { update(); }

/**
 * Handles equal button click event.
 */
void MainWindow::onEqButtonClick() {
  QString valueAsString = "";
  std::string expression = ui->lineExpression->text().toStdString();
  try {
    expCalcController.setExpression(expression);
    expCalcController.setXValue(ui->spinBoxValueX->value());
    long double res = expCalcController.Calculate();
    valueAsString = QString::number(res, 'g', 20);
  } catch (std::exception e) {
    QMessageBox::about(this, "Invalid expression", "Invalid input");
  }

  ui->lineExpression->setText(valueAsString);
}

/**
 * Handles all clear button click event.
 */
void MainWindow::onAcButtonClick() { ui->lineExpression->setText(""); }

/**
 * Handles clear button click event.
 */
void MainWindow::onCButtonClick() {
  QString expression = ui->lineExpression->text();
  expression.chop(1);
  ui->lineExpression->setText(expression);
}

/**
 * Handles add graph button click event.
 */
void MainWindow::onGraphButtonClick() {
  ui->graph->clearGraphs();

  if (ui->lineExpression->text() != "nan" &&
      ui->lineExpression->text() != "inf") {
    double x_begin = ui->spinBoxXMin->text().toDouble();
    double x_end = ui->spinBoxXMax->text().toDouble();
    double y_begin = ui->spinBoxYMin->text().toDouble();
    double y_end = ui->spinBoxYMax->text().toDouble();

    ui->graph->xAxis->setRange(x_begin, x_end);
    ui->graph->yAxis->setRange(y_begin, y_end);
    long double h = 0.1;
    long double Y = 0.0;
    QString needle = ui->lineExpression->text();
    QByteArray ba_x = needle.toLocal8Bit();
    char *str = ba_x.data();

    try {
      for (long double X_ = x_begin; X_ < x_end; X_ += h) {
        expCalcController.setExpression(str);
        expCalcController.setXValue(X_);
        Y = expCalcController.Calculate();
        x.push_back(X_);
        y.push_back(Y);
      }
    } catch (std::exception e) {
      QMessageBox::about(this, "Invalid expression", "Invalid input");
    }

    ui->graph->addGraph();
    ui->graph->graph(0)->addData(x, y);
    ui->graph->replot();
  } else {
    QMessageBox::about(this, "Invalid expression", "Invalid input");
  }
  x.clear();
  y.clear();
}
