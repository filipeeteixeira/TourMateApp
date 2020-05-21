//
// Created by filip on 11/05/2020.
//

#ifndef TOURMATEAPP_EDGE_H
#define TOURMATEAPP_EDGE_H

#include "Vertex.h"

class Vertex;

class Edge {
    Vertex *dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex *d, double w);
    Vertex * getDest() const;
    double getWeight() const;
    friend class Graph;
    friend class Vertex;
};


#endif //TOURMATEAPP_EDGE_H
