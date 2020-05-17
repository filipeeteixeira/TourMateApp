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

#include <unistd.h>

using namespace std;

#define INF std::numeric_limits<double>::max()

/*************************** Graph  **************************/

class Graph {
	vector<Vertex *> vertexSet;    // vertex set
    vector<vector<double>> dist;
    vector<vector<Vertex*> > pred;

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();

public:
	Vertex *findVertex(const int &id) const;
	bool addVertex(const int &id, const double &x, const double &y);
	bool addEdge(const int &sourc, const int &dest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;

	double getmaxX() const;
	double getmaxY() const;
    double getminX() const;
    double getminY() const;

    void setmaxX(double maxX);
    void setmaxY(double maxY);
    void setminX(double minX);
    void setminY(double minY);

	/*
	 *
	//FP04 - search
	vector<T> Graph<T>::dfs() const
	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...
*/
};

/**************** Search algorithm ************/
/*
template <class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;
	for(auto vertex :vertexSet)
	    vertex->visited = false;
    for (auto v : vertexSet)
        if (!v->visited)
            dfsVisit(v, res);
	return res;
}

void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for(auto a: v->adj){
	    auto vert = a.dest;
	    if(!vert->visited) dfsVisit(vert,res);
	}
}
 */
/**************** Single Source Shortest Path algorithms ************/
/*
template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	for (auto &v : vertexSet){
	    v->dist=INT64_MAX;
	    v->path= NULL;
	}
    Vertex<T> *s = findVertex(orig);
	s->dist=0;

	queue<Vertex<T>*> Q;
	Q.push(s);
	while(!Q.empty()){
	    Vertex<T> *tmp = Q.front();
	    Q.pop();
	    for (auto &w : tmp->adj){
	        if(w.dest->dist==INT64_MAX){
	            Q.push(w.dest);
	            w.dest->dist=tmp->dist +1;
	            w.dest->path=tmp;
	        }
	    }
	}
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (auto &v : vertexSet){
        v->dist=INT64_MAX;
        v->path= NULL;
    }
    Vertex<T> *s = findVertex(origin);
    s->dist=0;

    MutablePriorityQueue<Vertex<T> > Q;
    Q.insert(s);

    while(!Q.empty()){
        Vertex<T> *tmp = Q.extractMin();
        for (auto &w : tmp->adj){
            if(w.dest->dist>tmp->dist + w.weight){
                w.dest->dist=tmp->dist + w.weight;
                w.dest->path=tmp;
                if (!Q.inQueue(w.dest))
                    Q.insert(w.dest);
                else
                    Q.decreaseKey(w.dest);

            }
        }
    }

}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for (auto &v : vertexSet){
        v->dist=INT64_MAX;
        v->path= NULL;
    }
    Vertex<T> *s = findVertex(orig);
    s->dist=0;

    for(int i=1;i<=vertexSet.size()-1;i++){
        for (auto &v : vertexSet){
            for(auto&w : v->adj){
                if(w.dest->dist>v->dist + w.weight){
                    w.dest->dist=v->dist+w.weight;
                    w.dest->path=v;
                }
            }
        }
    }
    for (auto &v : vertexSet){
        for(auto&w : v->adj){
            if(w.dest->dist>v->dist + w.weight){
                cout << "There are cycles of negative weight\n";
            }
        }
    }

}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	Vertex<T>*VertexBehind = findVertex(dest)->path;
	while(VertexBehind!=NULL){
	    res.push_back(VertexBehind->info);
        VertexBehind=VertexBehind->getPath();
	}
	reverse(res.begin(),res.end());
	res.push_back(dest);
	return res;
}
*/


/**************** All Pairs Shortest Path  ***************/
/*
template<class T>
void Graph<T>::floydWarshallShortestPath() {
    dist.clear();
	dist= vector<vector<double>>(vertexSet.size(), vector<double>(vertexSet.size(), INT64_MAX));
	pred.clear();
	pred= vector<vector<Vertex<T>*>>(vertexSet.size(), vector<Vertex<T>*>(vertexSet.size(), NULL));

	for (int i=0; i<dist.size();i++){
	    dist[i][i]=0;
	}

	for (int v=0;v<vertexSet.size();v++){
	    for(int e=0;e< vertexSet[v]->adj.size();e++){
            for (int ve=0;ve<vertexSet.size();ve++) { // encontrar qual o index do vertice de destino no adj
                if (vertexSet[ve]==vertexSet[v]->adj[e].dest){
                    dist[v][ve]=vertexSet[v]->adj[e].weight;
                    pred[v][ve]=vertexSet[v];
                }
            }
	    }
	}

	for (int k=0;k<vertexSet.size();k++){
	    for(int i=0;i<vertexSet.size();i++){
	        for(int j=0;j<vertexSet.size();j++){
	            if(dist[i][j]>dist[i][k]+dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
	        }
	    }
	}
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
    int indexDest, indexOrig;

    for (int i=0; i<vertexSet.size();i++){
        if(vertexSet[i]==findVertex(dest)){
            res.push_back(vertexSet[i]->info);
            indexDest=i;
        }
        else if(vertexSet[i]==findVertex(orig)){
            indexOrig=i;
        }
    }
    Vertex<T> * before = pred[indexOrig][indexDest];
    res.push_back(before->getInfo());
    while(before!=findVertex(orig)){
        for (int i=0; i<vertexSet.size();i++){
            if(vertexSet[i]==findVertex(before->getInfo())) {
                before = pred[indexOrig][i];
                res.push_back(before->getInfo());
                break;
            }
        }
    }
    reverse(res.begin(),res.end());
	return res;
}
*/

#endif /* GRAPH_H_ */
