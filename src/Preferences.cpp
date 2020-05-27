//
// Created by filip on 26/05/2020.
//

#include "Preferences.h"

void Preferences::addUserPreferences(Vertex *preference) {
    userPreferences.push_back(preference);
}

void Preferences::buildPreferencesGraph(Graph *cityGraph, User *user) {
    graph= new Graph();
    Vertex *sp = new Vertex(user->getUserSP()->getId(),user->getUserSP()->getX(),user->getUserSP()->getY());
    Vertex *ep = new Vertex(user->getUserEP()->getId(),user->getUserEP()->getX(),user->getUserEP()->getY());
    userPreferences.push_back(sp);
    userPreferences.push_back(ep);
    Path * tmpPath;
    Edge * tmpEdge;
    for ( auto &v : userPreferences) {
        if (v != user->getUserEP() and v != user->getUserSP())
            graph->addVertex(v->getId(), v->getX(), v->getY()); //adiciona vertice ao grafo das preferencias
    }
    for ( auto &v : userPreferences){
        for ( auto &v1 : userPreferences){
            cityGraph->dijkstraShortestPath(*v,*v1); //calcula a distancia entre os dois vertices
            if (cityGraph->findVertex(v1->getId())->getDist()<user->getAvailableTime() and v->getId() != v1->getId()){
                tmpPath = cityGraph->getPathTo(v1->getId());
                tmpEdge = graph->addEdge(v->getId(),v1->getId(),v1->getDist()); //adiciona a aresta entre os dois vertices com o respetivo peso
                tmpEdge->setEdgePath(tmpPath);
            }
        }
    }
}

Graph * Preferences::getGraph(){
    return graph;
}

vector<Vertex *> Preferences::getUserPreferences() {
    return userPreferences;
}
