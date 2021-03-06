//
// Created by filip on 11/05/2020.
//

#include <algorithm>
#include <utility>
#include "Vertex.h"
#include "Graph.h"
#include "../User.h"

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

bool Graph::addEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}

Edge * Graph::removeEdge(const int &sourc, const int &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return nullptr;

    return v1->removeEdge(v2);
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

vector<int> Graph::getMetroNodes() {
    return metroNodes;
}

void Graph::addMetroNodes(int node) {
    metroNodes.push_back(node);
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

bool poiInPreferences(const User& user, Vertex *v){
    for(const auto& pref: user.getPreferences()){
        if(pref == v->getTag())
            return true;
    }
    return false;
}

//dataReader.getGraph().findVertex(i)->getTag() == preference
Path *Graph::getPathTo(int dest, const User& user) const{
    int preferencesInPath = 0;
    vector<int> res;
    Vertex *v = findVertexAlg(dest);
    Vertex *auxv = v;
    if (v == nullptr || v->dist == INF) // missing or disconnected
        return nullptr;
    for ( ; v != nullptr; v = v->path) {
        res.push_back(v->getId());
        if(poiInPreferences(user, v)) preferencesInPath++;
        //cout << v->getId() <<"->";
    }
    reverse(res.begin(), res.end());
    Path * path = new Path(res);
    path->setWeight(auxv->getDist());
    path->preferences = preferencesInPath;
    return path;
}

/*
 * ================================================================================================
 * DIJKSTRA ALGORITHM
 * ================================================================================================
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
/*
 * returns id of transport stop
 */
int Graph::dijkstraShortestPathToTransport(const Vertex &origin) {
    auto s = initSingleSource(origin.getId());
    MutablePriorityQueue<Vertex> q;
    q.insert(s);
    while( !q.empty()) {
        auto v = q.extractMin();
        for(auto e : v->adj) {
            auto oldDist = e->dest->dist;
            if (relax(v, e->dest, e->weight)) {
                if (oldDist == INF)
                    q.insert(e->dest);
                else
                    q.decreaseKey(e->dest);
                if(e->dest->getStation()) {
                    return e->dest->getId();
                }
            }
        }
    }
    return -1;
}

/*
 * ================================================================================================
 * DFS ALGORITHM
 * ================================================================================================
 */

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
            Gr.addEdge(vertexSet.at(i)->getAdj().at(j)->getDest()->getId(), vertexSet.at(i)->getId(), vertexSet.at(i)->adj.at(j)->weight);
        }
    }

    vector<int> vec2 = Gr.dfs();

    return !((int) vec1.size() != getNumVertex() || (int) vec2.size() != getNumVertex());
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

/*
 * ================================================================================================
 * YEN'S ALGORITHM
 * ================================================================================================
 */

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


double Graph::path_cost(vector<int> path) {
    double pathcost = 0;
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

vector<Path*> Graph::YenKSP(int src_id, int dest_id, double maxTime, User user, int Kn){
    vector<Path *> A;
    dijkstraShortestPath(*findVertexAlg(src_id), *findVertexAlg(dest_id));

    if(getPathTo(dest_id, user)->getWeight() > maxTime)
        return A;

    A.push_back(getPathTo(dest_id, user));
    PQ B;

    for(int k=1; k < Kn; k++){
        for(int i=0; i <= A.at(k-1)->getPath().size()-2; i++){
            vector<Edge*> removed_edges = {};

            int spurNode = A[k-1]->getPath().at(i); //encontrar o no a fixar
            vector<int> rootNodes = getNodes(A[k-1]->getPath(), 0, i); //encontrar o rootPath apartir do caminho encontrado pelo dijkstra
            Path * rootPath = new Path(rootNodes);
            rootPath->setWeight(path_cost(rootNodes)); //calcular o peso do rootPath e atribui-lo

            //eliminar edges para o dijkstra poder encontrar outros caminhos alternativos
            for(auto path: A){
                if(rootPath->getPath() == getNodes(path->getPath(), 0, i) && path->getPath().size() - 1 > i){
                    removed_edges.push_back(removeEdge(path->getPath().at(i), path->getPath().at(i+1)));
                }
            }

            //Calcular dijkstra para o grafo sem as arestas removidas
            dijkstraShortestPath(*findVertexAlg(spurNode), *findVertexAlg(dest_id));
            Path *spurPath =  getPathTo(dest_id, user); //getPathTo ja calcula o weight

            //caso o spurPath seja nulo não queremos adicionar o totalPath uma vez que isso significa que o vertice de destino nao tem ligação com os restantes
            if(spurPath!= nullptr) {
                Path *totalPathP = *rootPath + spurPath;
                if (!pathInPQ(totalPathP, B))
                    B.push(totalPathP);
            }

            //Adicionar de volta as arestas removidas do grafo
            for (Edge* edge: removed_edges){
                if (edge != NULL)
                    this->addEdge(edge->orig->getId(), edge->dest->getId(), edge->weight);
            }
        }
        //se B estiver vazio quer dizer que já não há mais caminhos possiveis
        if(B.empty() || B.top()->getWeight() > maxTime) // se o caminho retirado de B tiver um peso maior que o input do utilizador deixamos de calcular caminhos alternativos
            break;
        //Adicionar o melhor caminho a A
        A.push_back(B.top());
        B.pop();
    }

    return A;
}

