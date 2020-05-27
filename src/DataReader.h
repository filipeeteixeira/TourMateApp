#ifndef TOURMATEAPP_DATAREADER_H
#define TOURMATEAPP_DATAREADER_H

#include <string>
#include <graphviewer.h>
#include "GraphBuilder/Graph.h"
#include "User.h"

using namespace std;

class DataReader {
    string nodesFilenameXY;
    string nodesFilenameLatLon;
    string edgesFilename;
    string tagsFilename;
    string metroFilename;
    int width,height;

    bool realMaps;

    Graph graph;
    GraphViewer* graphViewer;

    double maxX,maxY,minX,minY;

    void readNodes();
    void readEdges(Transport transport);
    void readTags();
    void readMetro();

    public:
        DataReader();

        Graph getGraph();

        void displayGraph();

        void readData(string city, string gridGraph, Transport transport);

        void setFiles(string city, string gridGraph);

        void setRealMaps(bool rm);

        GraphViewer * getGraphViewer();

        void showPath( Path *path, User &user);

        void showMetro(Path *path);

        string getFileNameXY() const;

};

#endif //TOURMATEAPP_DATAREADER_H