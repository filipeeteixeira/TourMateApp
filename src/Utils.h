//
// Created by breno on 5/12/2020.
//

#ifndef TOURMATEAPP_UTILS_H
#define TOURMATEAPP_UTILS_H

using namespace std;

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

#endif //TOURMATEAPP_UTILS_H
