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

bool Graph::removeBidirectionalEdge(const int &sourc, const int &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->removeEdge(v2);
    v2->removeEdge(v1);
    return true;
}

void Graph::removeVertex(const int & vertexId)
{
    auto it = vertexSet.begin();
    while(it != vertexSet.end()) {
        if()
            vertexSet.erase(it);

        next(it, 1);
    }
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

vector<int> Graph::getPathTo(const int &dest) const{
    vector<int> res;
    auto v = findVertex(dest);
    if (v == nullptr || v->dist == INF) // missing or disconnected
        return res;
    for ( ; v != nullptr; v = v->path) {
        res.push_back(v->getId());
        //cout << v->getId() <<"->";
    }
    reverse(res.begin(), res.end());
    return res;

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
            if(paths.size() == 5)
                break;
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
                //cout << "newpath: " << getPathTime(newpath) << endl;
                if(getPathTime(path) <= maxTime){
                    paths_queue.push(newpath);
                }

            }
        }
    }

    return paths;
}

vector<int> getNodes(vector<int> path, int start, int end){
    vector<int>::const_iterator first = path.begin() + start;
    vector<int>::const_iterator last =  path.begin() + end;
    vector<int> newVec(first, last);
    return newVec;
}

vector<vector<int>> Graph::YenKSP(int src_id, int dest_id, int Kn){
    vector<vector<int>> A;
    // Determine the shortest path from the source to the sink.
    //-> A[0] = Dijkstra(Graph, source, sink);
    dijkstraShortestPath(*findVertex(src_id), *findVertex(dest_id));
    A.push_back(getPathTo(dest_id));
    // Initialize the set to store the potential kth shortest path.
    vector<int> B;
    // -> B = [];


    for(int k=1; k <= Kn; k++){
        for(int i=0; i <= A.at(k-1).size()-2; i++){
            int spurNode = A[k-1].at(i);
            vector<int> rootPath = A[k-1];

            for(auto path: A){
                if(rootPath == getNodes(path, 0, i)){
                    removeBidirectionalEdge(i, i+1);
                }
            }
            for(auto rootPathNode: rootPath){
                if(rootPathNode != spurNode)
                    remove
            }

            dijkstraShortestPath(*findVertex(spurNode), *findVertex(dest_id));
            vector<int> spurPath =  getPathTo(dest_id);
            vector<int> totalPath;
            totalPath.insert( totalPath.end(), spurPath.begin(), spurPath.end() );
        }
    }

    for k from 1 to K:  // ok
    // The spur node ranges from the first node to the next to last node in the previous k-shortest path.
    for i from 0 to size(A[k − 1]) − 2: // ok

    // Spur node is retrieved from the previous k-shortest path, k − 1.
    spurNode = A[k-1].node(i);
    // The sequence of nodes from the source to the spur node of the previous k-shortest path.
    rootPath = A[k-1].nodes(0, i);

    for each path p in A:
    if rootPath == p.nodes(0, i):
    // Remove the links that are part of the previous shortest paths which share the same root path.
    remove p.edge(i,i + 1) from Graph;

    for each node rootPathNode in rootPath except spurNode:
    remove rootPathNode from Graph;

    // Calculate the spur path from the spur node to the sink.
    spurPath = Dijkstra(Graph, spurNode, sink);

    // Entire path is made up of the root path and spur path.
    totalPath = rootPath + spurPath;
    // Add the potential k-shortest path to the heap.
    if (totalPath not in B):
    B.append(totalPath);

    // Add back the edges and nodes that were removed from the graph.
    restore edges to Graph;
    restore nodes in rootPath to Graph;

    if B is empty:
    // This handles the case of there being no spur paths, or no spur paths left.
    // This could happen if the spur paths have already been exhausted (added to A),
    // or there are no spur paths at all - such as when both the source and sink vertices
    // lie along a "dead end".
    break;
    // Sort the potential k-shortest paths by cost.
    B.sort();
    // Add the lowest cost path becomes the k-shortest path.
    A[k] = B[0];
    // In fact we should rather use shift since we are removing the first element
    B.pop();

    return A;
}
