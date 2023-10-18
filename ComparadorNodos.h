#include "NodoHuffman.h"
class ComparadorNodos {
public:
    bool operator()(NodoHuffman* nodo1, NodoHuffman* nodo2) {
        return nodo1->frecuencia > nodo2->frecuencia;
    }
};
