//
// Created by filip on 23/05/2020.
//

#include "Path.h"

Path::Path(vector<int> path) {
    this->path=path;
    this->weight=0;
}

double Path::getWeight() const {
    return weight;
}

vector<int> Path::getPath() const {
    return path;
}

void Path::setPath(vector<int> path) {
    this->path=path;
}

void Path::setWeight(double weight) {
    this->weight=weight;
}

Path *Path::operator+(const Path *path1) {
    Path* res = new Path(*this);
    vector <int> temp = this->getPath();
    for (int i=1;i <path1->getPath().size();i++)
        temp.push_back(path1->getPath()[i]);
    res->setPath(temp);
    res->weight += path1->weight;
    return res;
}

bool Path::operator==(const Path &path1) {
    if(path.size() != path1.getPath().size()){
        return false;
    }
    else
    {
        int i = 0;
        while(i<path.size()) {
            if(path[i] != path1.getPath()[i]){
                break;
            }
            i++;
        }
        if(i == path.size())
            return true;
    }
    return false;
}
