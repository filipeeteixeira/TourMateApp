//
// Created by filip on 10/05/2020.
//

#ifndef TOURMATEAPP_VERTEX_H
#define TOURMATEAPP_VERTEX_H

#include "Edge.h"
#include "MutablePriorityQueue.h"
#include <vector>
#include <string>

using namespace std;

class Edge;

class Vertex {
    int id;
    string name = "undefined"; //nome do local
    double x;
    double y;
    bool visited=false;

    double dist = 0;
    vector<Edge> adj;		// outgoing edges
    Vertex *path = nullptr;
    int queueIndex = 0; 		// required by MutablePriorityQueue
    void addEdge(Vertex *dest, double w);
public:
    Vertex(int id, double x, double y);

    Vertex(int id, const string name, double x, double y);

    string getName() const;

    void setName(const string name);

    int getId() const;

    double getX() const;

    double getY() const;

    bool operator==(const Vertex &rhs) const;

    bool getVisited() const;

    void setVisited(bool visited);

    Vertex* getPath() const;

    void setPath(Vertex* v);

    vector<Edge> getAdj() const;

    double getDist() const;

    friend class Graph;
    friend class MutablePriorityQueue<Vertex>;
};

#endif //TOURMATEAPP_VERTEX_H
