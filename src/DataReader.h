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
    int width,height;

    bool realMaps;

    Graph graph;
    GraphViewer* graphViewer;

    double maxX,maxY,minX,minY;

    void readNodes();
    void readEdges(Transport transport);
    void readTags();

    public:
        DataReader();

        Graph getGraph();

        void displayGraph();

        void readData(string city, string gridGraph, Transport transport);

        void setFiles(string city, string gridGraph);

        void setRealMaps(bool rm);

        GraphViewer * getGraphViewer();
};

#endif //TOURMATEAPP_DATAREADER_H