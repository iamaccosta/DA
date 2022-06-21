#include "Graph.h"

#include <iostream>
#include <vector>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


    /**
     * Auxiliary function to add an outgoing edge to a vertex (this),
     * with a given destination vertex (d) and edge weight (w).
     */
    template <class T>
    void Vertex<T>::addAdj(Vertex<T> *d, T capac, T dura) {
        adj.push_back(Edge<T>(this, d, capac, dura));
    }

    template <class T>
    vector<Edge<T>> Vertex<T>::getAdj() {
        return adj;
    }
};