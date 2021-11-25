#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->grabKeyboard();

  QSettings *iniRead = new QSettings("config.ini", QSettings::IniFormat);
  QString iniAuto = iniRead->value("autoSave").toString();
  QString iniPath = iniRead->value("filePath").toString();
  QString iniQss = iniRead->value("globalQss").toString();
  delete iniRead;

  // init autoSave
  if (!iniAuto.isEmpty() && !iniAuto.toInt()) {
    location::autoSave = 0;
  }

  // init filePath
  QFile iniPathFile(iniPath);
  if (iniPathFile.open(QFile::WriteOnly)) {
    location::filePath = iniPath;
  }

  // init Qss file(theme)
  QFile iniQssFile(iniQss);
  QString qssContent;
  if (iniQssFile.open(QFile::ReadOnly)) {
    qssContent = iniQssFile.readAll();
    globalQss = iniQss;
  } else {
    QFile defaultQss(globalQss);
    defaultQss.open(QFile::ReadOnly);
    qssContent = defaultQss.readAll();
  }
  centralWidget()->setStyleSheet(qssContent);
}

MainWindow::~MainWindow() {
  QSettings *IniWrite = new QSettings("config.ini", QSettings::IniFormat);
  IniWrite->setValue("autoSave", location::autoSave);
  IniWrite->setValue("filePath", location::filePath);
  IniWrite->setValue("globalQss", globalQss);
  delete IniWrite;

  delete ui;
}

QString MainWindow::globalQss = ":/Black.qss";

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return ||
        event->key() == Qt::Key_Equal) {
        //小键盘回车与主键盘回车
        ui->pushButton_equal->click();
    }
}


#define set_insert_func(name)                         \
  void MainWindow::on_pushButton_##name##_clicked() { \
    ui->textBrowser_input->setFocus();                \
    ui->textBrowser_input->insertPlainText(#name);    \
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
void MainWindow::on_pushButton_left_bracket_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->insertPlainText("(");
}
void MainWindow::on_pushButton_right_bracket_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->insertPlainText(")");
}
void MainWindow::on_pushButton_add_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->insertPlainText("+");
}
void MainWindow::on_pushButton_subtract_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->insertPlainText("-");
}
void MainWindow::on_pushButton_multiply_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->insertPlainText("*");
}
void MainWindow::on_pushButton_divide_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->insertPlainText("/");
}
void MainWindow::on_pushButton_mod_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->insertPlainText("%");
}
void MainWindow::on_pushButton_power_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->insertPlainText("^");
}
void MainWindow::on_pushButton_DEL_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->textCursor().deletePreviousChar();
}
void MainWindow::on_pushButton_CE_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->clear();
  ui->textBrowser_output->clear();
}

void MainWindow::on_pushButton_equal_clicked() {
  ui->textBrowser_input->setFocus();
  QString s = ui->textBrowser_input->toPlainText();
  QString rst = parser(s);
  ui->textBrowser_output->setPlainText(rst);
  if (location::autoSave) {
    save(location::filePath, s, rst);
  }
}

void MainWindow::on_pushButton_left_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
}
void MainWindow::on_pushButton_right_clicked() {
  ui->textBrowser_input->setFocus();
  ui->textBrowser_input->moveCursor(QTextCursor::Right,
                                    QTextCursor::MoveAnchor);
}

void MainWindow::on_actionAuthor_triggered() {
  Author *new_win = new Author();
  new_win->show();
}

void MainWindow::on_actionSave_triggered() {
  save(location::filePath, ui->textBrowser_input->toPlainText(),
       ui->textBrowser_output->toPlainText());
}

void MainWindow::on_actionRead_triggered() {
  QFile file(location::filePath);
  if (!file.exists()) {
    return;
  }
  QDesktopServices::openUrl(QUrl(location::filePath));
}

void MainWindow::on_actionHistory_location_triggered() {
  location *new_win = new location();
  new_win->show();
}

void MainWindow::on_actionAuto_Save_triggered() {
  location::autoSave = !location::autoSave;
  if (location::autoSave) {
    ui->actionAuto_Save->setText("Auto Save On");
  } else {
    ui->actionAuto_Save->setText("Auto Save Off");
  }
}

void MainWindow::on_actionLarge_font_size_triggered() {
  QString old_style = MainWindow::centralWidget()->styleSheet();
  old_style += "*{font:30px;}";
  MainWindow::centralWidget()->setStyleSheet(old_style);
}

void MainWindow::on_actionHelp_triggered() {
  Help *new_help = new Help();
  new_help->show();
}

void MainWindow::on_actionNormal_font_size_triggered() {
  QString old_style = MainWindow::centralWidget()->styleSheet();
  old_style += "*{font:20px;}";
  MainWindow::centralWidget()->setStyleSheet(old_style);
}

void MainWindow::on_actionSmall_font_size_triggered() {
  QString old_style = MainWindow::centralWidget()->styleSheet();
  old_style += "*{font:10px;}";
  MainWindow::centralWidget()->setStyleSheet(old_style);
}
