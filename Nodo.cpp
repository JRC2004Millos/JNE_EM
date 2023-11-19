//
// Created by talkysafe143 on 13/11/23.
//

#include "Nodo.h"

template<class T>
void Nodo<T>::deleteVertexAdj(int v) {
    auto itDelete = this->adj.begin();
    for (pair<int, int> &neigh: this->adj) {
        if (neigh.first == v) {
            this->adj.erase(itDelete);
            break;
        }
        itDelete++;
    }
}

template<class T>
void Nodo<T>::addVertexAdj(int v, int cost) {
    this->adj.push_back(make_pair(v, cost));
}

template<class T>
void Nodo<T>::updateCostAdj(int v, int cost) {
    for (pair<int, int> &neigh: this->adj) {
        if (neigh.first == v) {
            neigh.second = cost;
            break;
        }
    }
}

template<class T>
vector<pair<int, int> > Nodo<T>::getAdj() {
    return this->adj;
}

template<class T>
void Nodo<T>::setAdj(vector<pair<int, int>> nuevo) {
    this->adj = nuevo;
}

template<class T>
void Nodo<T>::setInfo(T nuevo) {
    this->info = nuevo;
}

template<class T>
T Nodo<T>::getInfo() {
    return this->info;
}

template<class T>
void Nodo<T>::clearAdj() {
    this->adj.clear();
}

template<class T>
Nodo<T>::Nodo() {
    this->info = T();
    this->adj = vector<pair<int, int>>();
}