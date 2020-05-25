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
    Edge * findEdge(const int &source, const int &dest) const;
	bool addVertex(const int &id, const double &x, const double &y);
	bool addBidirectionalEdge(const int &sourc, const int &dest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;

	Vertex* dfsAllPaths(Vertex* origin, Vertex* dest);
	void printAllPaths(Vertex* origin, Vertex* dest);
    Vertex *initSingleSource(const int &origin);
    bool relax(Vertex *v, Vertex *w, double weight);
    void dijkstraShortestPath(const Vertex &origin, const Vertex &dest);
    vector<int> dfs() const;
    bool stronglyConnected();

    void dfsVisit(Vertex *v, vector<int> &res) const;

    double getPathTime(vector<int> path);

    Path * getPathTo(int dest) const;

    double path_cost(vector<int> path);

    vector<int> getNodes(vector<int> path, int start, int end);

    vector<Path*> YenKSP(int src_id, int dest_id, double k);

    Edge * removeBidirectionalEdge(const int &sourc, const int &dest);

    int dijkstraShortestPathToTransport(const Vertex &origin);

    vector<int> getMetroNodes();

    void addMetroNodes(int node);

};

#endif /* GRAPH_H_ */
