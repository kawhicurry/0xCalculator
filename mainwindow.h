#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QFontDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QSettings>

#include "author.h"
#include "boxfont.h"
#include "help.h"
#include "location.h"
#include "parser.h"
#include "saving.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  static QString globalQss;

  void setTextFontSize(int FontSize);

 private slots:

  void keyPressEvent(QKeyEvent *event);

  void changeStyle(QString newStyle, QWidget *widget);

#define clicked_func(name) void on_pushButton_##name##_clicked();

  clicked_func(0);
  clicked_func(1);
  clicked_func(2);
  clicked_func(3);
  clicked_func(4);
  clicked_func(5);
  clicked_func(6);
  clicked_func(7);
  clicked_func(8);
  clicked_func(9);
  clicked_func(A);
  clicked_func(B);
  clicked_func(C);
  clicked_func(D);
  clicked_func(E);
  clicked_func(F);
  clicked_func(left_bracket);
  clicked_func(right_bracket);
  clicked_func(add);
  clicked_func(subtract);
  clicked_func(multiply);
  clicked_func(divide);
  clicked_func(Up);
  clicked_func(Down);
  clicked_func(DEL);
  clicked_func(CE);
  clicked_func(equal);
  clicked_func(left);
  clicked_func(right);

#define triggered_func(name) void on_action##name##_triggered();

  triggered_func(Author);
  triggered_func(Save) triggered_func(Read);
  triggered_func(History_location);
  triggered_func(Auto_Save);
  triggered_func(Large_font_size);
  triggered_func(Help);
  triggered_func(Normal_font_size);
  triggered_func(Small_font_size);
  triggered_func(Box_font_size);
  triggered_func(Black_theme);
  triggered_func(White_theme);

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
