//
// Created by filip on 11/05/2020.
//

#include "Vertex.h"

Vertex::Vertex(int id, double x, double y) : id(id), x(x), y(y){

}

Vertex::Vertex(int id, const string name, double x, double y): id(id), name(name), x(x), y(y){

}

int Vertex::getId() const{
    return id;
}

double Vertex::getX() const{
    return x;
}

double Vertex::getY() const{
    return y;
}

bool Vertex::getVisited() const{
    return visited;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setName(const string name) {
    this->name=name;
}

string Vertex::getName() const {
    return name;
}

bool Vertex::operator==(const Vertex &rhs) const {
    return id==rhs.id;
}

Vertex* Vertex::getPath() const{
    return path;
}

void Vertex::setPath(Vertex* v) {
    path = v;
}

vector<Edge> Vertex::getAdj() const{
    return adj;
}

double Vertex::getDist() const{
    return dist;
}

void Vertex::addEdge(Vertex *dest, double w) {
    adj.emplace_back(dest, w);
}
