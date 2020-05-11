//
// Created by filip on 10/05/2020.
//

#ifndef TOURMATEAPP_DATAREADER_H
#define TOURMATEAPP_DATAREADER_H

#include <string>
#include <graphviewer.h>
#include "GraphBuilder/Graph.h"

using namespace std;

class DataReader {
    string nodesFilename;
    string edgesFilename;

    Graph graph;
    GraphViewer* graphViewer;

    void readNodes();
    void readEdges();

    public:
        DataReader(const string &nodesFilename,const string &edgesFilename);

        Graph getGraph();

        void viewGraph();

        void readData();
};


#endif //TOURMATEAPP_DATAREADER_H
