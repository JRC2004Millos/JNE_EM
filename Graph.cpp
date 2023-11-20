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