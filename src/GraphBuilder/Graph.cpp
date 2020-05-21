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

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    v2->addEdge(v1,w);
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
        v->paths[0] = NULL;
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
        w->paths.push_back(v);
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

vector<int> Graph::dfs() const {
    vector<int> res;
    for(auto vertex :vertexSet)
        vertex->visited = false;
    for (auto v : vertexSet)
        if (!v->visited)
            dfsVisit(v, res);
    return res;
}

void Graph::dfsVisit(Vertex *v, vector<int> & res) const {
    v->visited = true;
    res.push_back(v->getId());
    for(auto a: v->adj){
        auto vert = a.dest;
        if(!vert->visited) dfsVisit(vert,res);
    }
}

/*
 • Pesquisa em profundidade no grafo G determina floresta de expansão,
numerando vértices em pós-ordem (ordem inversa de numeração em
pré-ordem)
• Inverter todas as arestas de G (grafo resultante é Gr)
• Segunda pesquisa em profundidade, em Gr, começando sempre pelo
vértice de numeração mais alta ainda não visitado
• Cada árvore obtida é um componente fortemente conexo, i.e., a partir
de um qualquer dos nós pode chegar-se a todos os outros
 */

bool Graph::stronglyConnected() {

    vector<int> vec1 = dfs();

    Graph Gr;

    for (int i = 0; i < getNumVertex(); i++) {
        for (size_t j = 0; j < vertexSet.at(i)->adj.size(); j++) {
            Gr.addVertex(vertexSet.at(i)->getAdj().at(j).getDest()->getId(), vertexSet.at(i)->getAdj().at(j).getDest()->getX(), vertexSet.at(i)->getAdj().at(j).getDest()->getY());
            Gr.addVertex(vertexSet.at(i)->getId(), vertexSet.at(i)->getX(), vertexSet.at(i)->getY());
            Gr.addBidirectionalEdge(vertexSet.at(i)->getAdj().at(j).getDest()->getId(), vertexSet.at(i)->getId(), vertexSet.at(i)->adj.at(j).weight);
        }
    }

    vector<int> vec2 = Gr.dfs();

    return !((int) vec1.size() != getNumVertex() || (int) vec2.size() != getNumVertex());
}

Vertex* Graph::dfsAllPaths(Vertex* origin, Vertex* dest) {
    static int time;

    Vertex* path;
    origin->visited = true;
    if(origin == dest){
        origin->time.push_back(time);
        time -= 2;
        return dest;
    }
    else {
        for(auto a: origin->adj) {
            auto vert = a.dest;
            time += 2;
            if(time<=16)
                path = dfsAllPaths(vert, dest);
            else
                return NULL;
            time -= 2;
            if (path != NULL) {
                if (path != dest)
                    for (int i = 0; i < path->paths.size(); i++) {
                        origin->time.push_back(time);
                        origin->paths.push_back(path);
                    }
                else{
                    origin->time.push_back(time);
                    origin->paths.push_back(path);
                }
            }
        }
    }
    return origin; // This return value won't be used for anything
}

void Graph::dfsAllPathsVisit(const int origin, const int dest) {
    Vertex* originV = findVertex(origin);
    Vertex* destV = findVertex(dest);
    for(auto vertex : vertexSet)
        vertex->setVisited(false);
    dfsAllPaths(originV, destV);
    printAllPaths(originV, destV);
}

void Graph::printAllPaths(Vertex* origin, Vertex* dest) {

    static int i = 0;

    if(origin == dest){
        cout << origin->getId() << endl;
        i++;
    }
    else
        {
        cout << origin->getId() <<"->";
        printAllPaths(origin->paths[i], dest);
    }

    if(i < origin->paths.size())
        printAllPaths(origin, dest);
}

//-------------------------------------------------------
// utility function for printing
// the found path in graph
void printpath(vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        cout << path[i] << " ";
    cout << endl;
}

// utility function to check if current
// vertex is already present in path
int isNotVisited(int x, vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}
/*
 *
 *
 * create a queue which will store path(s) of type vector
initialise the queue with first path starting from src

Now run a loop till queue is not empty
   get the frontmost path from queue
   check if the lastnode of this path is destination
       if true then print the path
   run a loop for all the vertices connected to the
   current vertex i.e. lastnode extracted from path
      if the vertex is not visited in current path
         a) create a new path from earlier path and
             append this vertex
         b) insert this new path to queue
 * */

double Graph::getPathTime(vector<int> path){
    double time = 0.0;
    for(int i=0; i < path.size() - 1; i++){
        for(auto edge: findVertex(path.at(i))->getAdj()) {
            if(edge.getDest()->getId() == path.at(i+1))
            {
                time += edge.weight;
                break;
            }
        }
    }
    return time;
}

// utility function for finding paths in graph
// from source to destination
vector<vector<int>> Graph::BFS_Paths(int src_id, int dest_id, double maxTime)
{
    // create a queue which stores
    // the paths
    vector<vector<int>> paths;
    queue<vector<int> > paths_queue;

    // path vector to store the current path
    vector<int> path;
    path.push_back(src_id);
    paths_queue.push(path);
    while (!paths_queue.empty()) {
        path = paths_queue.front();
        paths_queue.pop();
        int last = path[path.size() - 1];

        // if last vertex is the desired destination
        // then print the path
        if (last == dest_id) {
            printpath(path);
            paths.push_back(path);
        }

        if(getPathTime(path) > maxTime){
            continue;
        }

        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for (auto & e : findVertex(last)->getAdj()) {
            auto w = e.dest;
            if (isNotVisited(w->getId(), path)) {
                vector<int> newpath(path);
                newpath.push_back(w->getId());
                paths_queue.push(newpath);
            }
        }
    }

    return paths;
}

