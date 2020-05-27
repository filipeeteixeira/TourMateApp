//
// Created by filip on 26/05/2020.
//

#ifndef TOURMATEAPP_PREFERENCES_H
#define TOURMATEAPP_PREFERENCES_H

#include "GraphBuilder/Vertex.h"
#include "GraphBuilder/Graph.h"
#include "User.h"

class Graph;
class User;

using namespace std;

class Preferences {
    private:
        vector<Vertex *>userPreferences;

        Graph *graph;
    public:
        void addUserPreferences(Vertex * preference);

        void buildPreferencesGraph(Graph *cityGraph, User *user);

        Graph * getGraph();

        vector<Vertex *> getUserPreferences();

};




#endif //TOURMATEAPP_PREFERENCES_H
