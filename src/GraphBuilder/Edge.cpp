//
// Created by filip on 11/05/2020.
//

#include "Edge.h"

Edge::Edge(Vertex *orig,Vertex *dest, double weight): orig(orig), dest(dest), weight(weight) {

}

Vertex * Edge::getDest() const{
    return dest;
}

double Edge::getWeight() const{
    return weight;
}

Vertex *Edge::getOrig() const {
    return orig;
}