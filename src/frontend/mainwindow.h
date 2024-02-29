#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>

#include "../backend/expression_calculator.h"
#include "../backend/expression_calculator_controller.h"
#include "../backend/loan_calculator.h"
#include "../backend/loan_calculator_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  // MAIN WINDOW CONSTRUCTORS
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  // CLICK EVENT HANDLERS
  void update();
  void onOpsButtonClick();
  void onEqButtonClick();
  void onAcButtonClick();
  void onCButtonClick();
  void onGraphButtonClick();
  void onCalculateButtonClick();

 private:
  // FIELDS
  Ui::MainWindow *ui;
  s21::ExpressionCalculatorController expCalcController;
  s21::LoanCalculatorController loanCalcController;
  QVector<double> x, y;
};
#endif  // MAINWINDOW_H
