#include "location.h"

#include "ui_location.h"

Location::Location(QWidget *parent) : QDialog(parent), ui(new Ui::location) {
  ui->setupUi(this);

  ui->textEdit->setText(filePath);
}

QString Location::filePath = "result.txt";
int Location::line = 0;
bool Location::isRead = 0;
bool Location::autoSave = 1;

Location::~Location() { delete ui; }

void Location::on_pushButton_path_clicked() {
  QString file_name =
      QFileDialog::getOpenFileName(NULL, "选择txt文件", ".", "*.txt");
  ui->textEdit->setText(file_name);
}

void Location::on_pushButton_dir_clicked() {
  QString dir_name = QFileDialog::getExistingDirectory(NULL, "选择文件夹", ".");
  ui->textEdit->setText(dir_name + "/result.txt");
}

void Location::on_pushButton_cancel_clicked() { Location::close(); }

void Location::on_pushButton_sure_clicked() {
  QString new_path = ui->textEdit->toPlainText();
  QFileInfo info(new_path);

  if (!info.exists()) {
    if (new_path.contains(".txt")) {
      QFile f(new_path);
      f.open(QIODevice::WriteOnly);
      f.close();
    } else {
      ui->prompt->setText("路径或格式不合法，请重新输入");
    }
  }
  Location::filePath=new_path;
  Location::close();
}
