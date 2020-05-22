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

double Vertex::getLat() const{
    return lat;
}

double Vertex::getLon() const{
    return lon;
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

vector<Edge> Vertex::getAdj() const{
    return adj;
}

double Vertex::getDist() const{
    return dist;
}

void Vertex::addEdge(Vertex *dest, double w) {
    adj.emplace_back(dest, w);
}

void Vertex::removeEdge(Vertex *dest) {
    for(int i=0; i<adj.size(); i++){
        if(adj.at(i).getDest() == dest) {
            adj.erase(adj.begin() + i); return;
        }
    }
}


void Vertex::setLon(double lon){
    this->lon=lon;
}

void Vertex::setLat(double lat) {
    this->lat=lat;
}

long double Vertex::distance(Vertex *v)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    long double lat1 = toRadians(lat);
    long double lon1 = toRadians(lon);
    long double lat2 = toRadians(v->getLat());
    long double lon2 = toRadians(v->getLon());

    // Haversine Formula
    long double dlon = lon2 - lon1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                      pow(sin(dlon / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}

string Vertex::getTag() {
    return tag;
}

void Vertex::setTag(string tag) {
    this->tag=tag;
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}
