//
// Created by dmbg1 on 12/05/2020.
//

#include "User.h"

User::User() {
    name = "UNDEFINED";
    age = 0;
}

void User::addPreference(string preference) {
    preferences.push_back(preference);
    preferences.sort();
    preferences.unique();
}

string User::getName() const {
    return name;
}

unsigned int User::getAge() const {
    return age;
}

list<string> User::getPreferences() const {
    return preferences;
}

void User::setName(string newName) {
    name = newName;
}

void User::setAge(int newAge) {
    age = newAge;
}
