//
// Created by filip on 10/05/2020.
//

#ifndef TOURMATEAPP_VERTEX_H
#define TOURMATEAPP_VERTEX_H

#include "Edge.h"
#include "MutablePriorityQueue.h"
#include <vector>
#include <string>
#include "../Utils.h"

using namespace std;

class Edge;

class Vertex {
    int id;
    string name = "undefined"; //nome do local
    double x;
    double y;
    double lat;
    double lon;
    bool visited=false;
    string tag;

    double dist = 0;
    vector<Edge> adj;		// outgoing edges
    vector<Vertex *>paths;
    vector<int>time;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    void addEdge(Vertex *dest, double w);
public:

    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    Vertex(int id, double x, double y);

    Vertex(int id, const string name, double x, double y);

    string getName() const;

    void setName(const string name);

    int getId() const;

    double getX() const;

    double getY() const;

    double getLat() const;

    double getLon() const;

    void setLat(double lat);

    void setLon(double lon);

    string getTag();

    void setTag(string tag);

    bool operator==(const Vertex &rhs) const;

    bool getVisited() const;

    void setVisited(bool visited);

    vector<Edge> getAdj() const;

    double getDist() const;

    long double distance(Vertex *v);

    friend class Graph;
    friend class MutablePriorityQueue<Vertex>;
};

#endif //TOURMATEAPP_VERTEX_H
