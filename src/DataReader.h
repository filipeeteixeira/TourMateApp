//
// Created by filip on 10/05/2020.
//

#ifndef TOURMATEAPP_DATAREADER_H
#define TOURMATEAPP_DATAREADER_H

#include <string>
#include <graphviewer.h>
#include "GraphBuilder/Graph.h"

using namespace std;

enum Transport {onFoot, car, bus};

class DataReader {
    string nodesFilenameXY;
    string nodesFilenameLatLon;
    string edgesFilename;
    string tagsFilename;

    bool realMaps;

    Graph graph;
    GraphViewer* graphViewer;

    void readNodes();
    void readEdges(Transport transport);
    void readTags();

    public:
        DataReader();

        Graph getGraph();

        void displayGraph(int width, int height);

        void readData(string city, string gridGraph, Transport transport);

        void setFiles(string city, string gridGraph);

        void setRealMaps(bool rm);
};


#endif //TOURMATEAPP_DATAREADER_H
