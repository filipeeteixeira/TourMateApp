//
// Created by filip on 10/05/2020.
//

#include <fstream>
#include <sstream>
#include "DataReader.h"

DataReader::DataReader(){
    this->width = 950;
    this->height = 500;

    nodesFilenameXY="";
    nodesFilenameLatLon="";
    edgesFilename="";
    tagsFilename="";

    realMaps=false;

    graphViewer = nullptr;

    minX = std::numeric_limits<double>::max();
    minY = std::numeric_limits<double>::max();
    maxX = std::numeric_limits<double>::min();
    maxY = std::numeric_limits<double>::min();
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

        getline(ssline,tmp,',');
        x=stod(tmp);

        getline(ssline,tmp,')');
        y=stod(tmp);

        if (realMaps) {
            if (x < minX) minX = x;
            if (x > maxX) maxX = x;
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
        }

        graph.addVertex(nodeId, x, y);

    }

    if(realMaps) { //para podermos testar com os GridGraphs
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

            getline(ssline, tmp, ',');
            lat = stod(tmp);

            getline(ssline, tmp, ')');
            lon = stod(tmp);

            Vertex *tmpGraph = graph.findVertex(nodeId2);
            tmpGraph->setLat(lat);
            tmpGraph->setLon(lon);
        }
    }
}

void DataReader::readEdges(Transport transport) {
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

        getline(ssline,tmp,')');
        pointB=stoi(tmp);

        if (realMaps) {
            switch (transport) {
                case onFoot:
                    graph.addBidirectionalEdge(pointA, pointB, graph.findVertex(pointA)->distance(
                    graph.findVertex(pointB)) / 4.5); //weight between nodes
                    break;
                case car:
                    graph.addBidirectionalEdge(pointA, pointB, graph.findVertex(pointA)->distance(
                            graph.findVertex(pointB)) / 50.0);
                    break;
                case bus:
                    graph.addBidirectionalEdge(pointA, pointB, graph.findVertex(pointA)->distance(
                            graph.findVertex(pointB)) / 16.0);
                    break;
            }
        }
        else
            graph.addBidirectionalEdge(pointA,pointB,1);
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

GraphViewer * DataReader::getGraphViewer() {
    return graphViewer;
}

void DataReader::displayGraph() {
    if (this->graphViewer!= nullptr){
        this->graphViewer->closeWindow();
        delete this->graphViewer;
    }

    this->graphViewer= new GraphViewer(width, height, false);
    if(!nodesFilenameXY.empty()) {
        graphViewer->createWindow(width, height);
        graphViewer->defineVertexColor("black");
        graphViewer->defineEdgeColor("black");
        graphViewer->defineEdgeCurved(false);

        if(realMaps) {
            double yPercent, xPercent;
            for (Vertex* vertex : graph.getVertexSet()) {
                yPercent =(vertex->getY() - minY)/(maxY - minY);
                xPercent = (vertex->getX() - minX)/(maxX - minX);
                graphViewer->addNode(vertex->getId(), (int)(xPercent*width), (int)(yPercent*height));
                graphViewer->setVertexSize(vertex->getId(), 5);
            }

            int id = 0;
            for (Vertex* vertex : graph.getVertexSet()) {
                for (auto edge : vertex->getAdj()) {
                    graphViewer->addEdge(id, vertex->getId(), edge->getDest()->getId(), EdgeType::UNDIRECTED);
                    graphViewer->setEdgeColor(id, "gray");
                    graphViewer->setEdgeLabel(id, "");
                    id++;
                }
            }
            graphViewer->rearrange();
        }
        else{ //grid maps
            int edgeID = 0;
            for (auto vertex : this->graph.getVertexSet()) {
                graphViewer->addNode(vertex->getId(), vertex->getX(), vertex->getY());
                graphViewer->setVertexLabel(vertex->getId(), to_string(vertex->getId()));
                for (auto edge : vertex->getAdj())
                    graphViewer->addEdge(edgeID++, vertex->getId(), edge->getDest()->getId(), EdgeType::DIRECTED);
            }

        }
        graphViewer->rearrange();

    }
    else{
        cout << "There is no graph loaded! Load one in Load Graph menu." << endl;
        sleep(2);
    }
    //delete graphViewer;
}

void DataReader::showPath(Path *path, User &user){

    /*this->graphViewer= new GraphViewer(width, height, false);
    graphViewer->createWindow(width, height);
    graphViewer->defineVertexColor("black");
    graphViewer->defineEdgeColor("black");
    graphViewer->defineEdgeCurved(false);*/

    int id =0;
    for(auto v: graph.getVertexSet()){
        for (auto e : v->getAdj()) {
            graphViewer->removeEdge(id);
            id++;
        }
    }

    Vertex * tmpVertex= nullptr;
    for (int i=0; i<path->getPath().size();i++) {
        graphViewer->setVertexColor(path->getPath()[i], "YELLOW");
        graphViewer->setVertexSize(path->getPath()[i], 10);
        for( auto &up : user.getPreferences()){
            tmpVertex = graph.findVertex(path->getPath()[i]);
            if(tmpVertex->getTag()== up){
                graphViewer->setVertexSize(tmpVertex->getId(), 10);
                graphViewer->setVertexColor(tmpVertex->getId(), "BLUE");
            }
        }

    }

    id = 0;
    bool add;
    for (Vertex* vertex : graph.getVertexSet()) {
        for (auto edge : vertex->getAdj()) {
                graphViewer->addEdge(id, vertex->getId(), edge->getDest()->getId(), EdgeType::UNDIRECTED);
                graphViewer->setEdgeColor(id, "gray");
                graphViewer->setEdgeLabel(id, "");
                id++;
        }
    }

    for (int i = 0; i < path->getPath().size()-1; i++) {
        graphViewer->addEdge(id, path->getPath()[i], path->getPath()[i+1], EdgeType::DIRECTED);
        graphViewer->setEdgeColor(id, "ORANGE");
        graphViewer->setEdgeThickness(id, 10);
        id++;
    }

    graphViewer->rearrange();
}

void DataReader::readData(string city, string gridGraph, Transport transport) { //só para debug depois fica só a cidade
    this->graph = Graph();

    this->setFiles(city, gridGraph);
    this->readNodes();
    this->readEdges(transport);
    if(realMaps)
        this->readTags();
}

void DataReader::setFiles(string city, string gridGraph){
    if (realMaps) {
        /*nodesFilenameXY = "../res/PortugalMaps/" + city + "/nodes_x_y_" + toLower(city) + ".txt";
        nodesFilenameLatLon = "../res/PortugalMaps/" + city + "/nodes_lat_lon_" + toLower(city) + ".txt";
        edgesFilename = "../res/PortugalMaps/" + city + "/edges_" + toLower(city) + ".txt";
        tagsFilename = "../res/TagExamples/" + city + "/t03_tags_" + toLower(city) + ".txt";*/

        nodesFilenameXY = "../res/NewMaps/Porto/porto_strong_nodes_xy.txt";
        nodesFilenameLatLon = "../res/NewMaps/Porto/porto_strong_nodes_latlng.txt";
        edgesFilename = "../res/NewMaps/Porto/porto_strong_edges.txt";
        tagsFilename = "../res/NewMaps/Porto/porto_tags.txt";
        stcpFilename = "../res/TagExamples/Porto/porto_tags.txt";
        metroFilename = "../res/TagExamples/Porto/porto_tags.txt";
    }
    else{
        nodesFilenameXY = "../res/GridGraphs/" + gridGraph + "/nodes.txt";
        nodesFilenameLatLon = "";
        edgesFilename = "../res/GridGraphs/" + gridGraph + "/edges.txt";
    }
}

void DataReader::setRealMaps(bool rm) {
    this->realMaps=rm;
}