#ifndef SAVING_H
#define SAVING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <QString>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool save(QString location, QString fomula, QString data);

QString ReadLine(QString filename, int line);

int CountLines(QString filename);

#endif  // SAVING_H
