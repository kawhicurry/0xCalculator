#include "location.h"

#include "ui_location.h"

location::location(QWidget *parent) : QDialog(parent), ui(new Ui::location) {
  ui->setupUi(this);

  ui->textEdit->setText(filePath);
}

QString location::filePath = "hello.txt";
bool location::autoSave = 1;

location::~location() { delete ui; }

void location::on_pushButton_path_clicked() {
  QString file_name =
      QFileDialog::getOpenFileName(NULL, "选择txt文件", ".", "*.txt");
  ui->textEdit->setText(file_name);
}

void location::on_pushButton_dir_clicked() {
  QString dir_name = QFileDialog::getExistingDirectory(NULL, "选择文件夹", ".");
  ui->textEdit->setText(dir_name);
}

void location::on_pushButton_cancel_clicked() { location::close(); }

void location::on_pushButton_sure_clicked() {
  QString new_path = ui->textEdit->toPlainText();
  QFileInfo info(new_path);

  if (info.exists()) {
    location::filePath = new_path;
    location::close();
  } else {
    bool flag = 0;
    if (new_path.endsWith('/')) {
      QDir d;
      d.mkdir(new_path);
      new_path += "result.txt";
      flag = 1;
    }
    if (flag || new_path.contains(".txt")) {
      QFile f(new_path);
      f.open(QIODevice::WriteOnly);
      f.close();
      location::close();
    } else {
      ui->prompt->setText("路径非法，请重新输入");
      location::close();
    }
  }
}
