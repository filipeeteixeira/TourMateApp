//
// Created by filip on 11/05/2020.
//

#include <algorithm>
#include <utility>
#include "Vertex.h"
#include "Graph.h"

Vertex * Graph::findVertex(const int &id) const {
    auto i = vertexMap.find(id);
    if (i == vertexMap.end()) {
        return nullptr;
    }
    return vertexSet.at(i->second);
}

Vertex * Graph::findVertexAlg(const int &id) const {
    for (auto v : vertexSet){
        if(v->getId()==id){
            return v;
        }
    }
    return nullptr;
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

Edge * Graph::removeBidirectionalEdge(const int &sourc, const int &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return nullptr;

    v2->removeEdge(v1);
    return v1->removeEdge(v2);
}

Vertex * Graph::removeVertex(const int & vertexId)
{
    auto i = vertexMap.find(vertexId);
    if (i == vertexMap.end()) {
        return nullptr;
    }
    return vertexSet.at(i->second);
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

Path *Graph::getPathTo(int dest) const{
    vector<int> res;
    Vertex *v = findVertexAlg(dest);
    Vertex *auxv = v;
    if (v == nullptr || v->dist == INF) // missing or disconnected
        return nullptr;
    for ( ; v != nullptr; v = v->path) {
        res.push_back(v->getId());
        //cout << v->getId() <<"->";
    }
    reverse(res.begin(), res.end());
    Path * path = new Path(res);
    path->setWeight(auxv->getDist());
    return path;

}

/**
 * Dijkstra algorithm.
 */

void Graph::dijkstraShortestPath(const Vertex &origin, const Vertex &dest) {
    for (auto &v : vertexSet){
        v->dist=INF;
        v->path= NULL;
    }
    Vertex *s = findVertexAlg(origin.getId());
    s->dist=0;

    MutablePriorityQueue<Vertex > Q;
    Q.insert(s);

    while(!Q.empty()){
        Vertex *tmp = Q.extractMin();
        for (auto &w : tmp->adj){
            if(w->dest->dist>tmp->dist + w->weight){
                w->dest->dist=tmp->dist + w->weight;
                w->dest->path=tmp;
                if (!Q.inQueue(w->dest))
                    Q.insert(w->dest);
                else
                    Q.decreaseKey(w->dest);

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
        auto vert = a->dest;
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
            Gr.addVertex(vertexSet.at(i)->getAdj().at(j)->getDest()->getId(), vertexSet.at(i)->getAdj().at(j)->getDest()->getX(), vertexSet.at(i)->getAdj().at(j)->getDest()->getY());
            Gr.addVertex(vertexSet.at(i)->getId(), vertexSet.at(i)->getX(), vertexSet.at(i)->getY());
            Gr.addBidirectionalEdge(vertexSet.at(i)->getAdj().at(j)->getDest()->getId(), vertexSet.at(i)->getId(), vertexSet.at(i)->adj.at(j)->weight);
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
            auto vert = a->dest;
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
            if(edge->getDest()->getId() == path.at(i))
            {
                time += edge->weight;
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
        for (auto & e : findVertexAlg(last)->getAdj()) {
            auto w = e->dest;
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

vector<int> Graph::getNodes(vector<int> path, int start, int end){
    vector<int>::const_iterator first = path.begin() + start;
    vector<int>::const_iterator last =  path.begin() + end + 1;
    vector<int> newVec(first, last);
    return newVec;
}

struct Comparator{
    bool operator () (const Path *p1, const Path *p2) {
        return p1->getWeight()>p2->getWeight();
    }
};

using PQ = priority_queue<Path*, vector<Path*>, Comparator>;

bool pathInPQ(Path *path, PQ pq){
    while(!pq.empty()){
        if(*path == *pq.top()){
            pq.pop();
            return true;
        }
        pq.pop();
    }
    return false;
}


int Graph::path_cost(vector<int> path) {
    int pathcost = 0;
    if (path.size()>1)
        for (int i=0; i<path.size()-1;i++) {
               for(auto e : findVertex(path[i])->getAdj()) {
                   if (e->getDest()->getId()==path[i+1]){
                       pathcost+=e->getWeight();
                   }
               }
        }
    return pathcost;
}

vector<Path*> Graph::YenKSP(int src_id, int dest_id, int Kn){
    vector<Path *> A;

    //inicializa o vetor
    /*
    vector<vector<int> > A(100);
    for ( int i = 0 ; i < 100 ; i++ )
        A[i].resize(1000);
    */
    // Determine the shortest path from the source to the sink.
    //-> A[0] = Dijkstra(Graph, source, sink);
    dijkstraShortestPath(*findVertexAlg(src_id), *findVertexAlg(dest_id));
    A.push_back(getPathTo(dest_id));
    // Initialize the set to store the potential kth shortest path.

    // Função que compara os paths
    //auto compare = [](vector<int> const & a, vector<int> const & b) {return findVertex(a.at(a.size()-1))->getDist() > findVertex(b.at(b.size()-1))->getDist();};
    PQ B;
    // -> B = [];

    vector<Vertex*> auxVertexSet(vertexSet);


    for(int k=1; k <= Kn; k++){
        for(int i=0; i <= A.at(k-1)->getPath().size()-2; i++){
            vector<Edge*> removed_edges = {};
            vector<Vertex*> removed_vertices = {};
            int spurNode = A[k-1]->getPath().at(i);

            //build root path
            vector<int> rootNodes = getNodes(A[k-1]->getPath(), 0, i);
            Path * rootPath = new Path(rootNodes);
            rootPath->setWeight(path_cost(rootNodes));

            for(auto path: A){
                if(rootPath->getPath() == getNodes(path->getPath(), 0, i) && path->getPath().size() - 1 > i){
                    removed_edges.push_back(removeBidirectionalEdge(path->getPath().at(i), path->getPath().at(i+1)));
                }
            }


            for(auto rootPathNode: rootPath->getPath()){
                if(rootPathNode != spurNode)
                    removed_vertices.push_back(removeVertex(rootPathNode));
            }

            dijkstraShortestPath(*findVertexAlg(spurNode), *findVertexAlg(dest_id));
            Path *spurPath =  getPathTo(dest_id); //getPathTo ja calcula o weight

            if(spurPath!= nullptr) {
                Path *totalPathP = *rootPath + spurPath;
                if (!pathInPQ(totalPathP, B))
                    B.push(totalPathP);
            }


            // Add back the edges and nodes that were removed from the graph.
            for (Vertex* vertex: removed_vertices){
                if (vertex != NULL) this->addVertex(vertex);
            }

            for (Edge* edge: removed_edges){
                if (edge != NULL) this->addBidirectionalEdge(edge->orig->getId(), edge->dest->getId(), edge->weight);
            }
        }
        if(B.empty())
            break;

        //B.sort();
        A.push_back(B.top());
        B.pop();
    }

   return A;
}

void Graph::addVertex(Vertex *vertex) {
    vertexSet.push_back(vertex);
}

