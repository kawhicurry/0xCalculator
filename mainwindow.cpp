#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_pushButton_right_bracket_clicked()
//{
//    ui->textBrowser->moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
//}

#define set_insert_func(name)                                \
    void MainWindow::on_pushButton_##name##_clicked(){       \
    ui->textBrowser->setFocus();                             \
    ui->textBrowser->insertPlainText(#name);                 \
    }

set_insert_func(0);
set_insert_func(1);
set_insert_func(2);
set_insert_func(3);
set_insert_func(4);
set_insert_func(5);
set_insert_func(6);
set_insert_func(7);
set_insert_func(8);
set_insert_func(9);
set_insert_func(A);
set_insert_func(B);
set_insert_func(C);
set_insert_func(D);
set_insert_func(E);
set_insert_func(F);
void MainWindow::on_pushButton_left_bracket_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->insertPlainText("(");
}
void MainWindow::on_pushButton_right_bracket_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->insertPlainText(")");
}
void MainWindow::on_pushButton_add_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->insertPlainText("+");
}
void MainWindow::on_pushButton_subtract_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->insertPlainText("-");
}
void MainWindow::on_pushButton_multiply_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->insertPlainText("*");
}
void MainWindow::on_pushButton_divide_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->insertPlainText("/");
}
void MainWindow::on_pushButton_mod_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->insertPlainText("%");
}
void MainWindow::on_pushButton_power_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->insertPlainText("^");
}
void MainWindow::on_pushButton_DEL_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->textCursor().deletePreviousChar();
}
void MainWindow::on_pushButton_CE_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->clear();
}

void MainWindow::on_pushButton_equal_clicked(){
    ui->textBrowser->setFocus();
    QString s=ui->textBrowser->toPlainText();
    //获取并检查字符串有效性：是否包含非法字符，是否在数学语法上合法
    //分多次双目运算
    ui->textBrowser->
}

void MainWindow::on_pushButton_left_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
}
void MainWindow::on_pushButton_right_clicked(){
    ui->textBrowser->setFocus();
    ui->textBrowser->moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
}
