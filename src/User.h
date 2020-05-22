//
// Created by dmbg1 on 12/05/2020.
//

#ifndef TOURMATEAPP_USER_H
#define TOURMATEAPP_USER_H

#include <string>
#include <list>
#include "GraphBuilder/Vertex.h"

using namespace std;

class User {
public:
    User();
    void addPreference(string preference);
    string getName() const;
    unsigned int getAge() const;
    void setName(string newName);
    void setAge(int newAge);
    list<string> getPreferences() const;
    unsigned int getAvailableTime() const;

    Vertex * getUserSP();
    Vertex * getUserEP();

    void setUserSP(Vertex * sp);
    void setUserEP(Vertex * ep);

private:
    list<string> preferences;
    string name;
    unsigned int age;
    unsigned int availableTime;
    Vertex * startPoint;
    Vertex * endPoint;
};


#endif //TOURMATEAPP_USER_H
