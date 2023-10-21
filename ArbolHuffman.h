#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "NodoHuffman.h"
#include <unordered_map>
#include <string>
#include <vector>

class ArbolHuffman {
public:
    NodoHuffman* construirArbol(const std::unordered_map<char, int>& mapaFrecuencia);
    std::string codificarMensaje(NodoHuffman* raiz, const std::string& mensaje);
    std::string decodificarMensaje(NodoHuffman* raiz, const std::string& mensajeCodificado);
    std::vector<NodoHuffman*> obtenerNodosDelArbol(NodoHuffman* raiz);
    void obtenerNodosDelArbolAux(NodoHuffman* nodo, std::vector<NodoHuffman*>& nodos);

private:
    void codificarMensajeAux(NodoHuffman* nodo, std::string codigo, std::unordered_map<char, std::string>& mapaCodificacion);
};

#endif // ARBOLHUFFMAN_H
