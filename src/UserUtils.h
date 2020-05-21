//
// Created by filip on 20/05/2020.
//

#ifndef TOURMATEAPP_USERUTILS_H
#define TOURMATEAPP_USERUTILS_H

#include "DataReader.h"
#include "Utils.h"
#include "User.h"

void showTags(GraphViewer* gv, const vector<Vertex*>& vertexes);

void getStartPoint(User user, DataReader dataReader, string startTag);


#endif //TOURMATEAPP_USERUTILS_H
