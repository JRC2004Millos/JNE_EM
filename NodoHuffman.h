#ifndef NODOHUFFMAN_H
#define NODOHUFFMAN_H

template <class T>
class NodoHuffman {
    protected:
        T dato;                 
        int frecuencia;         
        NodoHuffman<T>* hijoIzq;
        NodoHuffman<T>* hijoDer;
    public:
        NodoHuffman();
        NodoHuffman(T val, int freq);
        ~NodoHuffman();
        T obtenerDato();
        int obtenerFrecuencia();
        void fijarDato(T val);
        NodoHuffman<T>* obtenerHijoIzq();
        NodoHuffman<T>* obtenerHijoDer();
        void fijarHijoIzq(NodoHuffman<T>* izq);
        void fijarHijoDer(NodoHuffman<T>* der);
        bool esHoja();
};

#include "NodoHuffman.h"
#endif



