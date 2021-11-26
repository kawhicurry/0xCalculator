#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("0xCalculator");
  w.setWindowOpacity(0.9);
  w.show();
  return a.exec();
}
