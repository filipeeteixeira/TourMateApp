//
// Created by filip on 10/05/2020.
//

#include <fstream>
#include <sstream>
#include "DataReader.h"

DataReader::DataReader(const string &nodesFilename,const string &edgesFilename) : nodesFilename(nodesFilename),
                                                                       edgesFilename(edgesFilename){

    graphViewer = new GraphViewer(750, 750, false);
}

void DataReader::readNodes() {
    ifstream nodesFile(this->nodesFilename);
    string line;
    int totalNodes, nodeId;
    double x,y;
    string tmp;

    getline(nodesFile,line);
    //totalNodes= stoi(line);

    while (getline(nodesFile, line)) {
        stringstream ssline(line);

        getline(ssline,tmp,'(');
        getline(ssline, tmp, ',');
        nodeId=stoi(tmp);

        getline(ssline,tmp,' ');
        getline(ssline,tmp,',');
        x=stoi(tmp);

        getline(ssline,tmp,' ');
        getline(ssline,tmp,')');
        y=stoi(tmp);

        graph.addVertex(nodeId, x, y);
    }
}

void DataReader::readEdges() {
    ifstream edgesFile(this->edgesFilename);

    string line;
    int pointA, pointB, totalEdges;
    string tmp;

    getline(edgesFile,line);
    totalEdges= stoi(line);

    while (getline(edgesFile, line)) {
        stringstream ssline(line);

        getline(ssline,tmp,'(');
        getline(ssline, tmp, ',');
        pointA=stoi(tmp);

        getline(ssline,tmp,' ');
        getline(ssline,tmp,')');
        pointB=stoi(tmp);

        graph.addEdge(pointA,pointB,1); //we need to calculate weight between nodes
    }
}

Graph DataReader::getGraph() {
    return graph;
}

void DataReader::viewGraph() {
    graphViewer->createWindow(750, 750);
    graphViewer->defineVertexColor("black");
    graphViewer->defineEdgeColor("black");

    int edgeID = 0;
    for (auto vertex : this->graph.getVertexSet()) {
        graphViewer->addNode(vertex->getId(), vertex->getX(), vertex->getY());
        graphViewer->setVertexLabel(vertex->getId(), to_string(vertex->getId()));
        for (auto edge : vertex->getAdj())
            graphViewer->addEdge(edgeID++, vertex->getId(), edge.getDest()->getId(), EdgeType::UNDIRECTED);
    }

    graphViewer->defineEdgeCurved(false);
    graphViewer->rearrange();
}

void DataReader::readData() {
    this->graph = Graph();
    this->readNodes();
    this->readEdges();
}
