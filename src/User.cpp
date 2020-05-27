//
// Created by dmbg1 on 12/05/2020.
//

#include "User.h"

User::User() {
    name = "UNDEFINED";
    age = 0;
    availableTime = 0;
    startPoint = nullptr;
    endPoint = nullptr;
    preferences = new Preferences();
}

Preferences * User::getPreferences() const{
    return preferences;
}

string User::getName() const {
    return name;
}

unsigned int User::getAge() const {
    return age;
}

void User::setName(string newName) {
    name = newName;
}

void User::setAge(int newAge) {
    age = newAge;
}

double User::getAvailableTime() const {
    return availableTime;
}

Vertex * User::getUserSP(){
    return startPoint;
}

Vertex * User::getUserEP(){
    return endPoint;
}

void User::setUserEP(Vertex * ep) {
    this->endPoint=ep;
}

void User::setUserSP(Vertex * sp) {
    this->startPoint=sp;
}

void User::setAvailableTime(double time) {
    this->availableTime = time;
}

Transport User::getTransport(){
    return transport;
}

void User::addPreferences(DataReader *dataReader, string tagName){
    double time=0;
    cout << "Loading your preferences..." << endl;
    for ( auto &v : dataReader->getGraph()->getVertexSet()){
        if(v->getTag()==tagName){ //se os pontos forem demasiado afastados do ponto inicial e final nao serao adicionados ao grafo
            dataReader->getGraph()->dijkstraShortestPath(*startPoint,*v);
            time+=v->getDist();
            dataReader->getGraph()->dijkstraShortestPath(*v,*endPoint);
            time+=endPoint->getDist();
            if(time<=availableTime)
                preferences->addUserPreferences(v);
        }
    }
    cout << "Preferences loaded." << endl;
}

void User::setTransport(Transport transport) {
    this->transport=transport;
}
