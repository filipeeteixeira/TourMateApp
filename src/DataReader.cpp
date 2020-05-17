//
// Created by filip on 10/05/2020.
//

#include <fstream>
#include <sstream>
#include "DataReader.h"

DataReader::DataReader(){
    nodesFilenameXY="";
    nodesFilenameLatLon="";
    edgesFilename="";
    tagsFilename="";

    graphViewer = new GraphViewer(750, 750, false);
}

void DataReader::readNodes() {
    string tmp;

    ifstream nodesFile(this->nodesFilenameXY);
    string line;
    int totalNodes, nodeId;
    double x,y;

    getline(nodesFile,line);
    totalNodes= stoi(line);

    while (getline(nodesFile, line)) {
        stringstream ssline(line);

        getline(ssline,tmp,'(');
        getline(ssline, tmp, ',');
        nodeId=stoi(tmp);

        getline(ssline,tmp,' ');
        getline(ssline,tmp,',');
        x=stof(tmp);

        if (x<graph.getminX()){graph.setminX(x);}
        if (x<graph.getmaxX()){graph.setmaxX(x);}

        getline(ssline,tmp,' ');
        getline(ssline,tmp,')');
        y=stof(tmp);

        if (x<graph.getminY()){graph.setminY(y);}
        if (x<graph.getmaxY()){graph.setmaxY(y);}

        graph.addVertex(nodeId, x, y);
    }

    if(!nodesFilenameLatLon.empty()) { //para podermos testar com os GridGraphs
        ifstream nodesFile2(this->nodesFilenameLatLon);
        string line2;
        int totalNodes2, nodeId2;
        double lat, lon;

        getline(nodesFile2, line2);
        totalNodes2 = stoi(line2);

        while (getline(nodesFile2, line2)) {
            stringstream ssline(line2);

            getline(ssline, tmp, '(');
            getline(ssline, tmp, ',');
            nodeId2 = stoi(tmp);

            getline(ssline, tmp, ' ');
            getline(ssline, tmp, ',');
            lat = stof(tmp);

            getline(ssline, tmp, ' ');
            getline(ssline, tmp, ')');
            lon = stof(tmp);

            Vertex *tmpGraph = graph.findVertex(nodeId2);
            tmpGraph->setLat(lat);
            tmpGraph->setLon(lon);
        }
    }
}

void DataReader::readEdges() {
    ifstream edgesFile(this->edgesFilename);

    string line;
    int pointA, pointB;
    int totalEdges;
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

        if (!nodesFilenameLatLon.empty())
            graph.addEdge(pointA,pointB,1); //weight between nodes
        else
            graph.addEdge(pointA,pointB,1);
    }
}

void DataReader::readTags() {
    ifstream tagsFile(this->tagsFilename);

    string line;
    int totalTags, nNodes;
    string tagname;
    string tmp;

    getline(tagsFile,line);
    int numTags = stoi(line);

    stringstream ssline(line);

    for (int i = 0; i < numTags; i++) {
        string tag;
        getline(tagsFile, tmp,'=');
        getline(tagsFile, tag);

        getline(tagsFile, line);
        int numNodes = stoi(line);
        for (int j = 0; j < numNodes; j++) {
            getline(tagsFile, line);
            Vertex *v = graph.findVertex(stoi(line));
            v->setTag(tag);
        }
    }
}

Graph DataReader::getGraph() {
    return graph;
}

void DataReader::displayGraph(int width, int height) {
    if(!nodesFilenameXY.empty()) {
        graphViewer->createWindow(width, height);
        graphViewer->defineVertexColor("black");
        graphViewer->defineEdgeColor("black");
        graphViewer->defineEdgeCurved(false);

        Vertex* currentVertex = new Vertex(0,0,0);
        vector<Vertex*> vertexSet = graph.getVertexSet();
        int edgeID = 0;
        double offsetX = vertexSet.at(0)->getX();
        double offsetY = vertexSet.at(0)->getY();

        vector<Edge> edges;
        vector<Vertex> auxiliar_edges;
        vector<Edge> currentEdges;

        for(size_t i = 0; i < vertexSet.size(); i++){
            currentVertex = vertexSet.at(i);
            graphViewer->addNode(currentVertex->getId(), currentVertex->getX()-offsetX, currentVertex->getY()-offsetY);
            currentEdges = currentVertex->getAdj();
            auxiliar_edges.insert(auxiliar_edges.end(), currentEdges.size(), *currentVertex);
            edges.insert(edges.end(), currentEdges.begin(), currentEdges.end());
        }

        for(size_t i = 0; i < edges.size(); i++){
            graphViewer->addEdge(edgeID, auxiliar_edges[i].getId(), edges[i].getDest()->getId(), EdgeType::DIRECTED);
            edgeID++;
        }

        graphViewer->rearrange();
    }
    else{
        cout << "There is no graph loaded! Load one in Load Graph menu." << endl;
        sleep(2);
    }
}

void DataReader::readData(string city, string gridGraph) { //só para debug depois fica só a cidade
    this->graph = Graph();
    this->setFiles(city, gridGraph);
    this->readNodes();
    this->readEdges();

    if(!city.empty())
        this->readTags();
}

void DataReader::setFiles(string city, string gridGraph){
    if (!city.empty()) {
        nodesFilenameXY = "../res/PortugalMaps/" + city + "/nodes_x_y_" + toLower(city) + ".txt";
        nodesFilenameLatLon = "../res/PortugalMaps/" + city + "/nodes_lat_lon_" + toLower(city) + ".txt";
        edgesFilename = "../res/PortugalMaps/" + city + "/edges_" + toLower(city) + ".txt";
        tagsFilename = "../res/TagExamples/" + city + "/t03_tags_" + toLower(city) + ".txt";
    }
    else{
        nodesFilenameXY = "../res/GridGraphs/" + gridGraph + "/nodes.txt";
        nodesFilenameLatLon = "";
        edgesFilename = "../res/GridGraphs/" + gridGraph + "/edges.txt";
    }
}
