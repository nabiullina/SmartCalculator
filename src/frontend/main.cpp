#include <QApplication>

#include "../backend/expression_calculator.h"
#include "../backend/expression_calculator_controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w(nullptr);
  w.show();
  return a.exec();
}
