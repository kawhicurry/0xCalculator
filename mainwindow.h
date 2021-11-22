#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

#define declare_clicked_func(name) \
    void on_pushButton_##name##_clicked();

    declare_clicked_func(0);
    declare_clicked_func(1);
    declare_clicked_func(2);
    declare_clicked_func(3);
    declare_clicked_func(4);
    declare_clicked_func(5);
    declare_clicked_func(6);
    declare_clicked_func(7);
    declare_clicked_func(8);
    declare_clicked_func(9);
    declare_clicked_func(A);
    declare_clicked_func(B);
    declare_clicked_func(C);
    declare_clicked_func(D);
    declare_clicked_func(E);
    declare_clicked_func(F);
    declare_clicked_func(left_bracket);
    declare_clicked_func(right_bracket);
    declare_clicked_func(add);
    declare_clicked_func(subtract);
    declare_clicked_func(multiply);
    declare_clicked_func(divide);
    declare_clicked_func(mod);
    declare_clicked_func(power);
    declare_clicked_func(DEL);
    declare_clicked_func(CE);
    declare_clicked_func(equal);
    declare_clicked_func(left);
    declare_clicked_func(right);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
