//
// Created by filip on 11/05/2020.
//

#include <algorithm>
#include "Vertex.h"
#include "Graph.h"

Vertex * Graph::findVertex(const int &id) const {
    auto i = vertexMap.find(id);
    if (i == vertexMap.end()) {
        return nullptr;
    }
    return vertexSet.at(i->second);
}

bool Graph::addVertex(const int &id, const double &x, const double &y) {
    if ( findVertex(id) != NULL)
        return false;
    vertexSet.push_back(new Vertex(id, x, y));
    vertexMap.insert(make_pair(id, vertexSet.size() - 1));
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


/**
* Initializes single-source shortest path data (path, dist).
* Receives the content of the source vertex and returns a pointer to the source vertex.
* Used by all single-source shortest path algorithms.
*/

Vertex * Graph::initSingleSource(const int &origin) {
    for (auto v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    auto s = findVertex(origin);
    s->dist = 0;
    return s;
}
/**
* Analyzes an edge in single-source shortest path algorithm.
* Returns true if the target vertex was relaxed (dist, path).
* Used by all single-source shortest path algorithms.
*/
bool Graph::relax(Vertex *v, Vertex *w, double weight) {
    if (v->dist + weight < w->dist) {
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    else
        return false;
}

/**
 * Dijkstra algorithm.
 */

void Graph::dijkstraShortestPath(const Vertex &origin, const Vertex &dest) {
    auto s = initSingleSource(origin.getId());
    bool found_dest = false;
    MutablePriorityQueue<Vertex> q;
    q.insert(s);
    while( !q.empty() && !found_dest) {
        auto v = q.extractMin();
        for(auto e : v->adj) {
            auto oldDist = e.dest->dist;
            if(e.dest->getId() == dest.getId())
                found_dest = true;
            if (relax(v, e.dest, e.weight)) {
                if (oldDist == INF)
                    q.insert(e.dest);
                else
                    q.decreaseKey(e.dest);
            }
        }
    }
}

vector<int> Graph::getPath(const Vertex &origin, const Vertex &dest) const {
    vector<int> res;
    auto v = findVertex(dest.getId());
    if (v == nullptr || v->dist == INF)
        return res;
    for ( ; v != nullptr; v = v->path)
        res.push_back(v->getId());
    reverse(res.begin(), res.end());
    return res;
}


