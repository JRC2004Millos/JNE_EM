//
// Created by talkysafe143 on 13/11/23.
//

#include "Graph.h"
#include "Nodo.cpp"

template<class T>
Graph<T>::Graph()
{
    vertices = vector<Nodo<T>>();
}


template< class T >
vector<Nodo<T>> Graph<T>::getVertices() {
    return this->vertices;
}

template< class T >
void Graph<T>::setVertices(vector<Nodo<T>> nuevo){
    this->vertices = nuevo;
}

template< class T >
void Graph<T>::Dijkstra(int S, vector<long double> &dist, vector<int>&parent) {

    for (int i = 0; i < dist.size(); i++) {
        dist[i] = 1e17;
        parent[i] = -1;
    }

    priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int>>> pq;
    dist[S] = 0;
    pq.push(make_pair(0, S));
    while (!pq.empty()) {
        pair<int, int> V = pq.top(); pq.pop();
        int dist_V = V.first;
        int vertex_V = V.second;
        if (dist_V > dist[vertex_V]) continue;

        for (pair<int, int> arc: this->vertices[vertex_V].getAdj()) {
            int to = arc.first;
            int len = arc.second;

            if (dist[vertex_V] + len < dist[to]) {
                dist[to] = dist[vertex_V] + len;
                parent[to] = vertex_V;
                pq.push(make_pair(dist[to], to));
            }
        }
    }
}

template< class T >
void Graph<T>::ReverseDijkstra(int S, int E, vector<int> &dist, vector<int>&parent, vector<bool> &visited) {

    for (int i = 0; i < dist.size(); i++) {
        dist[i] = 0;
        parent[i] = -1;
    }

    priority_queue<pair<int, int>> pq;
    dist[S] = 0;
    pq.push(make_pair(0, S));
    visited[S] = true;
    while (!pq.empty()) {
        pair<int, int> V = pq.top(); pq.pop();
        int dist_V = V.first;
        int vertex_V = V.second;
        if (vertex_V == E) continue;
        if (dist_V < dist[vertex_V]) continue;
        visited[vertex_V] = true;
        for (pair<int, int> arc: this->vertices[vertex_V].getAdj()) {
            int to = arc.first;
            int len = arc.second;
            if (visited[to] && to != E) continue;
            if (dist[vertex_V] + len > dist[to]) {
                dist[to] = dist[vertex_V] + len;
                parent[to] = vertex_V;
                pq.push(make_pair(dist[to], to));
            }
        }
    }
}

template<class T>
void Graph<T>::longestPath(int start, vector<int> &dist, vector<int> &parent, vector<bool> &visited, int currSum, int prev) {
    if (visited[start]) return;

    visited[start] = true;

    if (dist[start] < currSum) {
        dist[start] = currSum;
        parent[start] = prev;
    }

    for (pair<int, int> v: this->vertices[start].getAdj()) {
        this->longestPath(v.first, dist, parent, visited, currSum + v.second, start);
    }

    visited[start] = false;
}

template<class T>
void Graph<T>::FloydWarshall(vector<vector<int>> &dist, vector< vector<int> > &parent) {
    int n = (int)this->vertices.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = 1e8;

            if (i == j) parent[i][j] = i;
            else parent[i][j] = -1;
        }
        for (pair<int, int> v: this->vertices[i].getAdj()) {
            dist[i][v.first] = v.second;
            parent[i][v.first] = i;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = k;
                }
            }
        }
    }
}

template<class T>
void Graph<T>::removeArc(int u, int v) {
    this->vertices[u].deleteVertexAdj(v);
}

template<class T>
void Graph<T>::addArc(int u, int v, int cost) {
    this->vertices[u].addVertexAdj(v, cost);
}

template<class T>
void Graph<T>::addVertex(T info) {
    Nodo<T> nuevo;
    nuevo.setInfo(info);
    this->vertices.push_back(nuevo);
}


template<class T>
void Graph<T>::deleteArcs() {
    for (Nodo<T> &vertex: this->vertices) vertex.clearAdj();
}

template<class T>
void Graph<T>::generateGraphTxt(int n, int m) {
    ofstream file("graph.txt");
    file << n << " " << m << endl;
    for (int i = 0; i < n; i++) {
        for (pair<int, int> v: this->vertices[i].getAdj()) {
            file << i << " " << v.first << endl;
        }
    }
    file.close();
}