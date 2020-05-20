//
// Created by dmbg1 on 12/05/2020.
//

#ifndef TOURMATEAPP_USER_H
#define TOURMATEAPP_USER_H

#include <string>
#include <list>

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
private:
    list<string> preferences;
    string name;
    unsigned int age;
    unsigned int availableTime;
};


#endif //TOURMATEAPP_USER_H
