//
// Created by filip on 23/05/2020.
//

#ifndef TOURMATEAPP_PATH_H
#define TOURMATEAPP_PATH_H

#include <vector>

using namespace std;

class Path {
private:
    vector <int> path;
    double weight;

public:
    Path(vector<int> path);

    void setWeight(double weight);
    double getWeight() const;
    vector<int> getPath() const;
    void setPath(vector <int> path);
    Path * operator+ (const Path* path1);
    bool operator==(const Path&path1);
};


#endif //TOURMATEAPP_PATH_H
