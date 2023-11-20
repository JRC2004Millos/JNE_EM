#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
#include "Nodo.h"
using namespace std;

template < class T >
class Graph {
public:
    vector< Nodo<T> > vertices;
    Graph();
    
    vector<Nodo<T>> getVertices();
    void setVertices(vector<Nodo<T>> nuevo);
    void addVertex(T info);
    void addArc(int u, int v, int cost);
    void removeArc(int u, int v);
    void deleteArcs();
};

#endif //GRAPH_H
