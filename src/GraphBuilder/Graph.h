/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "Vertex.h"
#include "Edge.h"
#include "Path.h"
#include "../User.h"

#include <unistd.h>
#include <unordered_map>

using namespace std;

#define INF std::numeric_limits<double>::max()

/*************************** Graph  **************************/

class Graph {
	vector<Vertex *> vertexSet;    // vertex set
    vector<vector<double>> dist;
    vector<vector<Vertex*> > pred;

    unordered_map<int, int> vertexMap; //map para guardar a posição no vetor de cada nodeId

    vector<int> metroNodes;

public:
	Vertex *findVertex(const int &id) const;
    Vertex *findVertexAlg(const int &id) const;
	bool addVertex(const int &id, const double &x, const double &y);
	Edge * addEdge(const int &sourc, const int &dest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;

    Vertex *initSingleSource(const int &origin);
    bool relax(Vertex *v, Vertex *w, double weight);
    void dijkstraShortestPath(const Vertex &origin, const Vertex &dest);
    vector<int> dfs() const;
    bool stronglyConnected();

    void dfsVisit(Vertex *v, vector<int> &res) const;

    Path * getPathTo(int dest) const;

    double path_cost(vector<int> path);

    vector<int> getNodes(vector<int> path, int start, int end);

    vector<Path*> YenKSP(int src_id, int dest_id, double k);

    Edge * removeEdge(const int &sourc, const int &dest);

    int dijkstraShortestPathToTransport(const Vertex &origin);

    vector<int> getMetroNodes();

    void addMetroNodes(int node);

    Path * getPathToTEMP(int dest) const;

    Edge * findEdge(int &orig, int &dest);

    Edge * addEdge(Edge * e);

};

#endif /* GRAPH_H_ */
