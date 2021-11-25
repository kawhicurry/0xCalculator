#include "parser.h"

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

bool pd(char i) {
  if ((i <= 57 && i >= 48) || (i >= 65 && i <= 70)) return 0;
  return 1;
}
int pro(char i) {
  if (i == '+' || i == '-') return 1;
  if (i == '*' || i == '/') return 2;
  if (i == '(') return 0;
  if (i == ')') return -1;
  return 255;
}
// QString parser(QString expression) {
//  const int N = 100;
//  char s[N], stack1[N];
//  int read[N], sta[N], stack2[N], stt[N];
//  bool f[N] = {0}, flag[N] = {0};
//  string c, sc;
//  string str=expression.toStdString();

//  int l = str.length();
//  for (int i = 0; i < l; i++) {
//    s[i] = str[i];
//  }
//  int j = 0, k = 0, m = 0;
//  while (j < l) {
//    if (!pd(s[j]))  // number
//    {
//      if (s[j] <= 57 && s[j] >= 48) {
//        sta[k] = s[j] - 48;
//        j++;
//        k++;
//      } else if (s[j] >= 65 && s[j] <= 70) {
//        sta[k] = s[j] - 55;
//        j++;
//        k++;
//      }
//    } else if (pd(s[j]))  // character
//    {
//      if (!pd(s[j - 1]) && j > 0)  // number before
//      {
//        int cnt = 0;
//        char c = s[j];
//        for (int h = 0; k > 0; h++) {
//          cnt += sta[k - 1] * pow(16, h);
//          k--;
//        }
//        read[m] = cnt;
//        m++;
//        j++;
//        read[m] = c;
//        f[m] = 1;
//        m++;

//      } else {  // character before
//        char c = s[j];
//        read[m] = c;
//        f[m] = 1;
//        m++;
//        j++;
//      }
//    }
//  }
//  if (!pd(s[l - 1]))  // number
//  {
//    int cnt = 0;
//    for (int h = 0; k > 0; h++) {
//      cnt += sta[k - 1] * pow(16, h);
//      k--;
//    }
//    read[m] = cnt;
//    m++;
//    j++;
//  }
//  int a = 0, b = 0;  // reverse
//  for (int i = 0; i < m; i++) {
//    if (f[i] == 0) {
//      stack2[a] = read[i];
//      a++;
//    } else if (f[i] == 1) {
//      if (read[i] == '(') {
//        stack1[b] = '(';
//        b++;
//      } else if (pro(read[i]) == 1)  //+-
//      {
//        while (pro(stack1[b - 1]) >= 1 && b > 0) {
//          stack2[a] = stack1[b - 1];
//          flag[a] = 1;
//          b--;
//          a++;
//        }
//        stack1[b] = read[i];
//        b++;
//      } else if (pro(read[i]) == 2)  //*/
//      {
//        while (pro(stack1[b - 1]) == 2 && b > 0) {
//          stack2[a] = stack1[b - 1];
//          flag[a] = 1;
//          b--;
//          a++;
//        }
//        stack1[b] = read[i];
//        b++;
//      } else if (read[i] == ')') {
//        while (stack1[b - 1] != '(') {
//          stack2[a] = stack1[b - 1];
//          flag[a] = 1;
//          b--;
//          a++;
//        }
//        b--;
//      }
//    }
//  }
//  while (b > 0) {
//    stack2[a] = stack1[b - 1];
//    flag[a] = 1;
//    a++;
//    b--;
//  }
//  // calculation
//  int g = 0, cn = 0;
//  for (int i = 0; i < a; i++) {
//    if (!flag[i])  // number
//    {
//      stt[g] = stack2[i];
//      g++;
//    } else if (flag[i])  // character
//    {
//      switch (stack2[i]) {
//        case '+':
//          cn = stt[g - 2] + stt[g - 1];
//          break;
//        case '-':
//          cn = stt[g - 2] - stt[g - 1];
//          break;
//        case '*':
//          cn = stt[g - 2] * stt[g - 1];
//          break;
//        case '/':
//          cn = stt[g - 2] / stt[g - 1];
//          break;
//      }
//      g -= 2;
//      stt[g] = cn;
//      g++;
//    }
//  }
//  int x;
//  while (cn != 0) {
//    x = cn % 16;
//    if (x < 10)
//      c = x + '0';
//    else
//      c = x + 'A' - 10;
//    sc = c + sc;
//    cn /= 16;
//  }
//  cout << str << "=";
//  cout << sc << endl;
//  return QString::fromStdString(sc);
//}

QString parser(QString expression) {
  const int N = 100;
  char s[N], stack1[N];
  int read[N], sta[N], stack2[N], stt[N];
  bool f[N] = {0}, flag[N] = {0}, ff = 0, fff = 0;
  string c, sc, as = expression.toStdString();
  string str;
  str = "0+" + as;
  int l = str.length();
  for (int i = 0; i < l; i++) {
    s[i] = str[i];
  }
  if (pd(s[l - 1]) && s[l - 1] != ')') ff = 1;
  int st = 0;
  for (int i = 0; i < l; i++)  // judge the brackets match or not
  {
    if (s[i] == '(') st++;
    if (s[i] == ')') st--;
  }
  if (st != 0) ff = 1;
  int j = 0, k = 0, m = 0;
  while (j < l && ff == 0) {
    if (!pd(s[j]))  // number
    {
      if (s[j] <= 57 && s[j] >= 48) {
        sta[k] = s[j] - 48;
        j++;
        k++;
      } else if (s[j] >= 65 && s[j] <= 70) {
        sta[k] = s[j] - 55;
        j++;
        k++;
      }
    } else if (pd(s[j]))  // character
    {
      if (!pd(s[j - 1]) && j > 0)  // number before
      {
        int cnt = 0;
        char c = s[j];
        for (int h = 0; k > 0; h++) {
          cnt += sta[k - 1] * pow(16, h);
          k--;
        }
        read[m] = cnt;
        m++;
        j++;
        read[m] = c;
        f[m] = 1;
        m++;

      } else {  // character before
        char c = s[j];
        read[m] = c;
        f[m] = 1;
        m++;
        j++;
      }
    }
  }
  if (!pd(s[l - 1]))  // number
  {
    int cnt = 0;
    for (int h = 0; k > 0; h++) {
      cnt += sta[k - 1] * pow(16, h);
      k--;
    }
    read[m] = cnt;
    m++;
    j++;
  }
  int a = 0, b = 0;  // reverse
  for (int i = 0; i < m; i++) {
    if (f[i] == 0) {
      stack2[a] = read[i];
      a++;
    } else if (f[i] == 1) {
      if (read[i] == '(') {
        stack1[b] = '(';
        b++;
      } else if (pro(read[i]) == 1)  //+-
      {
        while (pro(stack1[b - 1]) >= 1 && b > 0) {
          stack2[a] = stack1[b - 1];
          flag[a] = 1;
          b--;
          a++;
        }
        stack1[b] = read[i];
        b++;
      } else if (pro(read[i]) == 2)  //*/
      {
        while (pro(stack1[b - 1]) == 2 && b > 0) {
          stack2[a] = stack1[b - 1];
          flag[a] = 1;
          b--;
          a++;
        }
        stack1[b] = read[i];
        b++;
      } else if (read[i] == ')') {
        while (stack1[b - 1] != '(') {
          stack2[a] = stack1[b - 1];
          flag[a] = 1;
          b--;
          a++;
        }
        b--;
      }
    }
  }
  while (b > 0) {
    stack2[a] = stack1[b - 1];
    flag[a] = 1;
    a++;
    b--;
  }
  // calculation
  int g = 0, cn = 0;
  for (int i = 0; i < a; i++) {
    if (!flag[i])  // number
    {
      stt[g] = stack2[i];
      g++;
    } else if (flag[i])  // character
    {
      switch (stack2[i]) {
        case '+':
          cn = stt[g - 2] + stt[g - 1];
          break;
        case '-':
          cn = stt[g - 2] - stt[g - 1];
          break;
        case '*':
          cn = stt[g - 2] * stt[g - 1];
          break;
        case '/':
          if (stt[g - 1] != 0) {
            cn = stt[g - 2] / stt[g - 1];
            break;
          } else if (stt[g - 1] == 0) {
            ff = 1;
            break;
          }
      }
      g -= 2;
      stt[g] = cn;
      g++;
    }
  }
  int x;
  int cnn = cn;
  if (cn == 0 && !ff) {
    // cout<<str<<"="<<cn<<endl;
    return "0";
  }
  while (cn != 0 && !ff) {
    if (cn >= 0) {
      x = cn % 16;
      if (x < 10)
        c = x + '0';
      else
        c = x + 'A' - 10;
      sc = c + sc;
      cn /= 16;
    } else if (cn <= 0) {
      x = cn % 16;
      if (x > -10)
        c = -x + '0';
      else
        c = -x + 'A' - 10;
      sc = c + sc;
      cn /= 16;
    }
  }
  if (cnn < 0) sc = '-' + sc;
  if (!ff && !fff) {
    return QString::fromStdString(sc);
  } else if (ff && !fff) {
    return "error";
  }
  return 0;
}
