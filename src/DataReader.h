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
    string nodesFilenameXY;
    string nodesFilenameLatLon;
    string edgesFilename;
    string tagsFilename;
    int width,height;

    bool realMaps;

    Graph graph;
    GraphViewer* graphViewer;

    double maxX,maxY,minX,minY;

    void readNodes();
    void readEdges();
    void readTags();

    public:
        DataReader();

        Graph getGraph();

        void displayGraph();

        void readData(string city, string gridGraph);

        void setFiles(string city, string gridGraph);

        void setRealMaps(bool rm);

        GraphViewer * getGraphViewer();
};


#endif //TOURMATEAPP_DATAREADER_H
