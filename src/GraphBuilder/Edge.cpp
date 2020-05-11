//
// Created by filip on 11/05/2020.
//

#include "Edge.h"

Edge::Edge(Vertex *dest, double weight): dest(dest), weight(weight) {

}

Vertex * Edge::getDest() const{
    return dest;
}

double Edge::getWeight() const{
    return weight;
}