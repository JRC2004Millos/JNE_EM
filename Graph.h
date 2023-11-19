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
    void Dijkstra(int S, vector<long double> &dist, vector<int>&parent);
    void addVertex(T info);
    void addArc(int u, int v, int cost);
    void removeArc(int u, int v);
    void deleteArcs();
    void FloydWarshall(vector<vector<int>> &dist, vector< vector<int> > &parent);
    void ReverseDijkstra(int S, int E, vector<int> &dist, vector<int>&parent, vector<bool> &visited);
    void longestPath(int start, vector<int> &dist, vector<int> &parent, vector<bool> &visited, int currSum, int prev);
    void generateGraphTxt(int n, int m);
};

#endif //GRAPH_H
