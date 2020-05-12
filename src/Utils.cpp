//
// Created by dmbg1 on 12/05/2020.
//
#include "Utils.h"

void clear()
{
    for(int i=0; i < 50; i++)cout << endl;
}

bool readInt(int & n, const string msg)
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


