//
// Created by breno on 5/12/2020.
//

#ifndef TOURMATEAPP_UTILS_H
#define TOURMATEAPP_UTILS_H

#include <string>
#include <iostream>
#include <math.h>

using namespace std;

void clear();

bool readInt(unsigned int & n, const string msg);

long double toRadians(const long double degree);

void normalizeCity(string &s);

string toLower(string const str);

#endif //TOURMATEAPP_UTILS_H
