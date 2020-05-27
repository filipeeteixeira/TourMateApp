//
// Created by filip on 20/05/2020.
//

#ifndef TOURMATEAPP_USERUTILS_H
#define TOURMATEAPP_USERUTILS_H

#include "DataReader.h"
#include "Utils.h"
#include "User.h"

void showTags(GraphViewer* gv, const vector<Vertex*>& vertexes);

void getStartPoint(User &user, DataReader &dataReader, string startTag);

void getEndPoint(User &user, DataReader &dataReader, string endTag);

int checkIfPathHasUserPreferences(User &user, DataReader &dataReader, Path*  path);

bool comparePaths(Path* path1, Path* path2);

void sortByUserPreferences(vector<Path*> & paths);

#endif //TOURMATEAPP_USERUTILS_H
