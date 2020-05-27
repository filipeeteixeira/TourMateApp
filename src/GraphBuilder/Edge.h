//
// Created by filip on 11/05/2020.
//

#ifndef TOURMATEAPP_EDGE_H
#define TOURMATEAPP_EDGE_H

#include "Vertex.h"
#include "Path.h"

class Vertex;

class Edge {
    Vertex *orig;
    Vertex *dest;      // destination vertex
    double weight;         // edge weight
    Path * path;    //usado para o grafo dos pontos de interesse
public:
    Edge(Vertex *orig, Vertex *d, double w);
    Vertex * getDest() const;
    Vertex * getOrig() const;
    double getWeight() const;

    void setEdgePath(Path * path);

    Path * getEdgePath() const;

    friend class Graph;
    friend class Vertex;
};


#endif //TOURMATEAPP_EDGE_H
