//
// Created by filip on 11/05/2020.
//

#include "Vertex.h"
#include "Graph.h"

Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->id == id)
            return v;
    return NULL;
}

bool Graph::addVertex(const int &id, const double &x, const double &y) {
    if ( findVertex(id) != NULL)
        return false;
    vertexSet.push_back(new Vertex(id, x, y));
    return true;
}

bool Graph::addEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

