//
// Created by dmbg1 on 12/05/2020.
//
#include "Utils.h"
#include "DataReader.h"

void clear()
{
    for(int i=0; i < 50; i++)cout << endl;
}

bool readInt(unsigned int & n, const string msg)
{
    cout << msg << " ? ";
    while (!(cin >> n))
    {
        if (cin.eof())
        {
            cin.clear();
            return false;
        }
        else
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << msg << " ? ";
    }
    cin.ignore(1000, '\n');
    return true;
}

// Utility function for
// converting degrees to radians
long double toRadians(const long double degree)
{
// cmath library in C++
// defines the constant
// M_PI as the value of
// pi accurate to 1e-30
long double one_deg = (M_PI) / 180;
return (one_deg * degree);
}

void normalizeCity(string &s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        if (i == 0) {
            s[i] = toupper(s[i]);
        } else {
            s[i] = tolower(s[i]);
        }
    }
}

string toLower(string const str){
    string result;
    for (char c: str){
        result += tolower(c);
    }
    return result;
}


