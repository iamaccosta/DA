#ifndef DA_P2_GRAPH_H
#define DA_P2_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

/************************* Vertex **************************/

template <class T>
class Vertex {
    T info; // contents

    int cap;
    bool visited;
    int dist;
    Vertex<T> *path = nullptr;
    int earliestStart;
    int degree;

public:
    vector<Edge<T>> adj;
    explicit Vertex(T in);
    T getInfo() const;


    void addAdj(Vertex<T> *dest, int capac, int dura, int resCap);
    vector<Edge<T>> getAdj() const;

    void setCap(int c);
    void setDist(int d);
    void setVisited(bool b);
    void setPath(Vertex<int> * v);
    void setES(int es);
    void setDegree(int degree);

    int getCap() const;
    int getDist() const;
    bool getVisited() const;
    Vertex *getPath() const;
    int getES() const;
    int getDegree() const;
};

template <class T>
Vertex<T>::Vertex(T in): info(in), dist(0), cap(0), visited(false) {}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
void Vertex<T>::addAdj(Vertex<T> *d, int capac, int dura, int resCap) {
    adj.push_back(Edge<T>(this, d, capac, dura, resCap));
}

template <class T>
vector<Edge<T>> Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
void Vertex<T>::setCap(int c){
    cap = c;
}

template <class T>
void Vertex<T>::setDist(int d) {
    dist = d;
}

template <class T>
void Vertex<T>::setVisited(bool b) {
    visited = b;
}

template <class T>
void Vertex<T>::setPath(Vertex<int> *v) {
    path = v;
}

template <class T>
void Vertex<T>::setES(int es){
    this->earliestStart = es;
}

template <class T>
void Vertex<T>::setDegree(int degree){
    this->degree = degree;
}

template <class T>
int Vertex<T>::getCap() const {
    return this->cap;
}

template<class T>
int Vertex<T>::getDist() const {
    return dist;
}

template<class T>
bool Vertex<T>::getVisited() const {
    return visited;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
int Vertex<T>::getES() const{
    return this->earliestStart;
}

template <class T>
int Vertex<T>::getDegree() const{
    return this->degree;
}

/************************* Edge **************************/
template <class T>
class Edge {
    Vertex<T> * orig;      // origin vertex
    Vertex<T> * dest;      // destination vertex
    int capacidade;         // edge weight
    int duracao;
    int flux;
    int residCap;
public:
    Edge(Vertex<T> *o, Vertex<T> *d, int c, int dura, int resCap);
    int getCapacidade() const;
    int getDuracao() const;
    int getFlux() const;
    Vertex<T> * getOrig() const;
    Vertex<T> * getDest() const;
    int getResidCap() const;

    void setFlux(int f);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, int c, int dura, int resCap): orig(o), dest(d), capacidade(c), duracao(dura), flux(0), residCap(resCap){}

template <class T>
int Edge<T>::getCapacidade() const {
    return capacidade;
}

template <class T>
int Edge<T>::getDuracao() const {
    return duracao;
}

template <class T>
int Edge<T>::getFlux() const {
    return flux;
}

template <class T>
Vertex<T> * Edge<T>::getOrig() const {
    return orig;
}

template <class T>
Vertex<T> * Edge<T>::getDest() const {
    return dest;
}

template<class T>
int Edge<T>::getResidCap() const {
    return residCap;
}

template <class T>
void Edge<T>::setFlux(int f) {
    flux = f;
}


/************************* Graph **************************/
template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set

    int **W = nullptr;   // dist
    int **P = nullptr;   // path

    bool relax(Vertex<T> *v, Vertex<T> *w, double weight);

public:
    Graph();
    ~Graph();
    vector<Vertex<T> *> getVertexSet() const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, int capac, int dura, int resCap);

    Vertex<T> *findVertex(const T &in) const;

    vector<T> getPath(const T &origin, const T &dest) const;
    Vertex<T> * initSingleSource(const T& origem);
    void unweightedShortestPath(const T& origem);
};

template <class T>
Graph<T>::Graph()= default;

/*** destructor ***/
template <class T>
void deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

template <class T>
Graph<T>::~Graph() {
    deleteMatrix(W, vertexSet.size());
    deleteMatrix(P, vertexSet.size());
}
/*** destructor ***/

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    vector<T> res;
    Vertex<T> pred = *findVertex(dest); //pred = dest
    if(!pred.getVisited()) return res;
    res.push_back(pred.getInfo());
    while(pred.getInfo() != origin){
        pred = *(pred.getPath());
        res.push_back(pred.getInfo());
    }
    //reverse vector
    reverse(res.begin(), res.end());

    return res;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, int capac, int dura, int resCap) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addAdj(v2, capac, dura, resCap);
    return true;
}

/**
 * Analyzes an edge in single source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */
template<class T>
inline bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
    if (v->getDist() + weight < w->getDist()) {
        w->setDist(v->getDist() + weight);
        w->setPath(v);
        return true;
    }
    else
        return false;
}

template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origem) {
    for(Vertex<T> * vert : vertexSet) {
        vert->setDist(INT32_MAX);
        vert->setPath(nullptr);
        vert->setVisited(false);
    }
    auto s = findVertex(origem);
    s->setDist(0);
    s->setVisited(true);
    s->setCap(INT32_MAX);
    return s;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T& origem) {
    auto first = initSingleSource(origem);
    queue<Vertex<T>* > q;
    q.push(first);

    while(!q.empty()) {
        Vertex<int> * v = q.front();
        q.pop();
        for(Edge<T> e: v->getAdj()) {
            if (relax(v, e.getDest(), 1)) {
                q.push(e.getDest());
                e.getDest()->setVisited(true);
            }
        }
    }
}

#endif //DA_P2_GRAPH_H