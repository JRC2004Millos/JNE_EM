#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H
#include <queue>
#include <iostream>
#include <unordered_map>

#include "NodoHuffman.h"

// Definición del comparador personalizado
template <class T>
struct ComparadorFrecuencia {
    bool operator()(NodoHuffman<T>* nodo1, NodoHuffman<T>* nodo2) const {
        // Comparar los nodos basados en sus frecuencias
        return nodo1->obtenerFrecuencia() > nodo2->obtenerFrecuencia();
    }
};

template <class T>
class ArbolHuffman {
    protected:
        NodoHuffman<T> *raiz;
    public:
        ArbolHuffman();
        ~ArbolHuffman();
        void liberarArbol(NodoHuffman<T>* nodo);
        bool esVacio();
        void insertar(T simbolo, int frecuencia); // Inserta un símbolo con su frecuencia
        std::string codificarDatos(const std::string& datos);
        void asignarCodigosHuffman(NodoHuffman<T>* nodo, const std::string& codigoActual, std::unordered_map<T, std::string>& codigos);
        std::string decodificarDatos(const std::string& codigo);
        void mostrarCodigos(NodoHuffman<T>* nodo, std::string codigoActual);
        void mostrarCodigos();
        void inOrden(NodoHuffman<T>* nodo);
        void verificarArbol();
};

#include "ArbolHuffman.h"
#endif