#include "ArbolHuffman.h"
#include "ComparadorNodos.h"
#include <iostream>
#include <sstream>
#include <queue>

NodoHuffman* ArbolHuffman::construirArbol(const std::unordered_map<char, int>& mapaFrecuencia) {
    std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, ComparadorNodos> monticuloMinimo;

    // Crear nodos hoja para cada carácter y agregarlos al montículo de prioridad
    for (const auto& entrada : mapaFrecuencia) {
        NodoHuffman* nodo = new NodoHuffman(entrada.first, entrada.second);
        monticuloMinimo.push(nodo);
    }

    // Construir el árbol combinando nodos hasta que quede solo un nodo raíz
    while (monticuloMinimo.size() > 1) {
        NodoHuffman* izquierda = monticuloMinimo.top();
        monticuloMinimo.pop();

        NodoHuffman* derecha = monticuloMinimo.top();
        monticuloMinimo.pop();

        NodoHuffman* nodoCombinado = new NodoHuffman('\0', izquierda->frecuencia + derecha->frecuencia);
        nodoCombinado->izquierda = izquierda;
        nodoCombinado->derecha = derecha;

        monticuloMinimo.push(nodoCombinado);
    }

    return monticuloMinimo.top();
}


std::string ArbolHuffman::codificarMensaje(NodoHuffman* raiz, const std::string& mensaje) {
    std::unordered_map<char, std::string> mapaCodificacion;  // Mapa para almacenar la codificación de cada carácter
    codificarMensajeAux(raiz, "", mapaCodificacion);  // Llamada a la función auxiliar de codificación

   std::string mensajeCodificado;
    // Imprimir la codificación del mensaje
    for (char c : mensaje) {
      
       mensajeCodificado += mapaCodificacion[c] + " ";
    }

  return mensajeCodificado;
}

void ArbolHuffman::codificarMensajeAux(NodoHuffman* nodo, std::string codigo, std::unordered_map<char, std::string>& mapaCodificacion) {
  if (nodo == nullptr) {
      return;
  }

  // Si es un nodo hoja, almacenamos su codificación
  if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
      mapaCodificacion[nodo->dato] = codigo;
  }

  // Llamadas recursivas para el hijo izquierdo y derecho
  codificarMensajeAux(nodo->izquierda, codigo + "0", mapaCodificacion);
  codificarMensajeAux(nodo->derecha, codigo + "1", mapaCodificacion);
}
std::stringstream mensajeDecodificado;

std::string ArbolHuffman::decodificarMensaje(NodoHuffman* raiz, const std::string& mensaje) {
    NodoHuffman* nodoActual = raiz;
    
    std::string decodificado = "";
  
    for (char bit : mensaje) {
        if (bit == '0') {
            nodoActual = nodoActual->izquierda;
        } else if (bit == '1') {
            nodoActual = nodoActual->derecha;
        }

        // Solo imprimir si es un nodo hoja
        if (nodoActual->izquierda == nullptr && nodoActual->derecha == nullptr) {
            decodificado += nodoActual->dato;
            nodoActual = raiz;  // Reiniciar para decodificar el próximo carácter
        }
    }

    // Asegurarse de imprimir el último carácter si es un nodo hoja
    if (nodoActual != raiz && nodoActual->izquierda == nullptr && nodoActual->derecha == nullptr) {
        decodificado += nodoActual->dato;
    }

    decodificado += '\n';
    return decodificado;
}

std::vector<NodoHuffman*> ArbolHuffman::obtenerNodosDelArbol(NodoHuffman* raiz) {
    std::vector<NodoHuffman*> nodos;
    obtenerNodosDelArbolAux(raiz, nodos);
    return nodos;
}

// Función auxiliar para realizar el recorrido in-order y almacenar los nodos en el vector
void ArbolHuffman::obtenerNodosDelArbolAux(NodoHuffman* nodo, std::vector<NodoHuffman*>& nodos) {
    if (nodo == nullptr) 
        return;
    
    // Llamada recursiva al hijo izquierdo
    obtenerNodosDelArbolAux(nodo->izquierda, nodos);

    // Almacenar el nodo actual en el vector
    nodos.push_back(nodo);

    // Llamada recursiva al hijo derecho
    obtenerNodosDelArbolAux(nodo->derecha, nodos);
}