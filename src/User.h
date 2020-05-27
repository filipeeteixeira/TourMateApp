//
// Created by dmbg1 on 12/05/2020.
//

#ifndef TOURMATEAPP_USER_H
#define TOURMATEAPP_USER_H

#include <string>
#include <list>
#include "GraphBuilder/Vertex.h"
#include "Preferences.h"
#include "DataReader.h"

enum Transport {onFoot, car, metro};
class DataReader;
class Preferences;
using namespace std;

class User {
public:
    User();

    string getName() const;
    unsigned int getAge() const;

    void setName(string newName);
    void setAge(int newAge);

    double getAvailableTime() const;

    Preferences * getPreferences() const;
    void addPreferences(DataReader *dataReader, string tag);

    Vertex * getUserSP();
    Vertex * getUserEP();

    void setUserSP(Vertex * sp);
    void setUserEP(Vertex * ep);
    void setAvailableTime(double time);
    Transport getTransport();
    void setTransport(Transport transport);
private:
    Transport transport;
    Preferences *preferences;
    string name;
    unsigned int age;
    double availableTime;
    Vertex * startPoint;
    Vertex * endPoint;
};


#endif //TOURMATEAPP_USER_H
