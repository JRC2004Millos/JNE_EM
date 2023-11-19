#ifndef NODO_H
#define NODO_H

#include <bits/stdc++.h>

using namespace std;

template < class T >
class Nodo {
public:
    T info;
    vector< pair<int, int> > adj;
    Nodo();

    // Getters & Setters
    T getInfo();
    void setInfo(T nuevo);
    void setAdj(vector< pair<int, int> > nuevo);
    vector< pair<int, int> > getAdj();

    void updateCostAdj(int v, int cost);
    void addVertexAdj(int v, int cost);
    void deleteVertexAdj(int v);
    void clearAdj();
};



#endif //NODO_H
