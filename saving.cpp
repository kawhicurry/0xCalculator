#include "saving.h"

using namespace std;
static string getCurrentTime()  //输出当前时间
{
  time_t t = time(0);
  char ch[64] = {0};
  strftime(ch, sizeof(ch) - 1, "%Y-%m-%d %H:%M:%S", localtime(&t));
  return ch;
}
bool save(QString location, QString fomula, QString data) {
  string addr = location.toStdString();
  fstream f;
  f.open(addr, ios::out | ios::app);
  f << getCurrentTime() << " " << fomula.toStdString() << "="
    << data.toStdString()
    << endl;  //变量addr、以及gch的等式和输出结果变量还需加进去
  f.close();
  return 1;
}
QString read(QString location) {
  //文件数据写入
  string addr = location.toStdString();

  fstream f;
  f.open(addr, ios::in);
  string s;
  while (f >> s) cout << s << endl;
  f.close();  //文件数据读取
  return QString::fromStdString(s);
}
