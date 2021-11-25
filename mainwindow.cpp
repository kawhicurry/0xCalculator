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
    Location::autoSave = 0;
    ui->actionAuto_Save->setText("Auto Save Off");
  }

  // init filePath
  QFile iniPathFile(iniPath);
  if (iniPathFile.open(QFile::WriteOnly)) {
    Location::filePath = iniPath;
  }

  // init Qss file(theme)
  QFile iniQssFile(iniQss);
  QString qssContent;
  if (iniQssFile.open(QFile::ReadOnly)) {
    qssContent = iniQssFile.readAll();
    globalQss = iniQss;
  } else {
    QFile defaultQss(":/Black.qss");
    defaultQss.open(QFile::ReadOnly);
    qssContent = defaultQss.readAll();
  }
  centralWidget()->setStyleSheet(qssContent);
}

MainWindow::~MainWindow() {
  QSettings *IniWrite = new QSettings("config.ini", QSettings::IniFormat);
  IniWrite->setValue("autoSave", Location::autoSave);
  IniWrite->setValue("filePath", Location::filePath);
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
  if (event->key() == Qt::Key_Up) {
    //读取历史文件
    ui->pushButton_Up->click();
  }
  if (event->key() == Qt::Key_Down) {
    ui->pushButton_Down->click();
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
void MainWindow::on_pushButton_Up_clicked() {
  ui->textBrowser_input->setFocus();
  if (Location::isRead) {
    --Location::line;
  } else {
    Location::line = CountLines(Location::filePath);
    Location::isRead = 1;
  }
  ui->textBrowser_output->setText(ReadLine(Location::filePath, Location::line));
}
void MainWindow::on_pushButton_Down_clicked() {
  ui->textBrowser_input->setFocus();
  if (Location::isRead) {
    ++Location::line;
  }
  ui->textBrowser_output->setText(ReadLine(Location::filePath, Location::line));
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

  Location::isRead = 0;

  QString s = ui->textBrowser_input->toPlainText();
  QString rst = parser(s);
  ui->textBrowser_output->setPlainText(rst);
  if (Location::autoSave) {
    save(Location::filePath, s, rst);
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
  save(Location::filePath, ui->textBrowser_input->toPlainText(),
       ui->textBrowser_output->toPlainText());
}

void MainWindow::on_actionRead_triggered() {
  QFile file(Location::filePath);
  if (!file.exists()) {
    return;
  }
  QDesktopServices::openUrl(QUrl(Location::filePath));
}

void MainWindow::on_actionHistory_location_triggered() {
  Location *new_win = new Location();
  new_win->show();
}

void MainWindow::on_actionAuto_Save_triggered() {
  Location::autoSave = !Location::autoSave;
  if (Location::autoSave) {
    ui->actionAuto_Save->setText("Auto Save On");
  } else {
    ui->actionAuto_Save->setText("Auto Save Off");
  }
}

void MainWindow::on_actionHelp_triggered() {
  Help *new_help = new Help();
  new_help->show();
}

// Style
void MainWindow::changeStyle(QString newStyle, QWidget *widget) {
  QString oldStyle = widget->styleSheet();
  oldStyle += newStyle;
  widget->setStyleSheet(oldStyle);
}

void MainWindow::on_actionLarge_font_size_triggered() {
  changeStyle("*{font:30px;}", MainWindow::centralWidget());
}
void MainWindow::on_actionNormal_font_size_triggered() {
  changeStyle("*{font:20px;}", MainWindow::centralWidget());
}
void MainWindow::on_actionSmall_font_size_triggered() {
  changeStyle("*{font:10px;}", MainWindow::centralWidget());
}

void MainWindow::on_actionBox_font_size_triggered() {
  bool ok;
  QFont font = QFontDialog::getFont(&ok, ui->textBrowser_input->font(), this,
                                    "自定义输入输出框文字");
  if (ok) {
    ui->textBrowser_input->setStyleSheet(
        "*{font:" + (QString::number(font.pointSize(), 10) + "px ;}"));
    ui->textBrowser_output->setStyleSheet(
        "*{font:" + (QString::number(font.pointSize(), 10) + "px ;}"));
  }
}

void MainWindow::on_actionBlack_theme_triggered() {
  globalQss = ":/Black.qss";
  QFile defaultQss(globalQss);
  defaultQss.open(QFile::ReadOnly);
  QString qssContent = defaultQss.readAll();
  centralWidget()->setStyleSheet(qssContent);
}

void MainWindow::on_actionWhite_theme_triggered() {
  globalQss = ":/White.qss";
  QFile defaultQss(globalQss);
  defaultQss.open(QFile::ReadOnly);
  QString qssContent = defaultQss.readAll();
  centralWidget()->setStyleSheet(qssContent);
}
