#ifndef LOCATION_H
#define LOCATION_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMimeDatabase>
#include <QMimeType>

namespace Ui {
class location;
}

class Location : public QDialog {
  Q_OBJECT

 public:
  explicit Location(QWidget *parent = nullptr);
  ~Location();

  static QString filePath;
  static int line;
  static bool isRead;
  static bool autoSave;

 private slots:
  void on_pushButton_path_clicked();

  void on_pushButton_dir_clicked();

  void on_pushButton_cancel_clicked();

  void on_pushButton_sure_clicked();

 private:
  Ui::location *ui;
};

#endif  // LOCATION_H
