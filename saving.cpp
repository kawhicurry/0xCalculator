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
//统计txt文件行数
int CountLines(QString filename) {
  ifstream f;
  int n = 0;
  string tmp;
  string stdfilename = filename.toStdString();
  // ios::in 表示以只读的方式读取文件
  f.open(stdfilename, ios::in);
  //文件打开失败:返回0
  if (f.fail()) {
    return 0;
  } else {
    //文件存在
    while (getline(f, tmp, '\n')) {
      n++;
    }
    f.close();
    return n;
  }
}
QString ReadLine(QString filename, int line)  //读取指定行文件
{
  // line行数限制 1 - lines
  if (line > 0 && line <= CountLines(filename)) {
    ifstream f;
    string stdfilename = filename.toStdString();
    f.open(stdfilename, ios::in);

    vector<string> strVec;
    //行0 - 行lines对应strvect[0] - strvect[lines]
    while (!f.eof()) {
      string inbuf;
      getline(f, inbuf, '\n');
      strVec.push_back(inbuf);
    }
    return QString::fromStdString(strVec[line - 1]);
  } else {
    return NULL;
  }
}
