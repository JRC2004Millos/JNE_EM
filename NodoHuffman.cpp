#include "NodoHuffman.h"

// Constructor por defecto
template<class T>
NodoHuffman<T>::NodoHuffman() : dato(T()) {

}

// Constructor con de referencia (dato, frecuencia)
template<class T>
NodoHuffman<T>::NodoHuffman(T dato, int freq) {

}

// Destructor
template<class T>
NodoHuffman<T>::~NodoHuffman() {
    delete this -> hijoIzq;
    delete this -> hijoDer;
}

// Obtener el símbolo del nodo
template<class T>
T NodoHuffman<T>::obtenerDato() {
    return this -> dato;
}

// Obtener la frecuencia del símbolo
template<class T>
int NodoHuffman<T>::obtenerFrecuencia() {
    return this -> frecuencia;
}

// Fijar el símbolo del nodo
template<class T>
void NodoHuffman<T>::fijarDato(T val) {
    this -> dato = val;
}

// Obtener el hijo izquierdo
template<class T>
NodoHuffman<T>* NodoHuffman<T>::obtenerHijoIzq() {
    return this -> hijoIzq;
}

// Obtener el hijo derecho
template<class T>
NodoHuffman<T>* NodoHuffman<T>::obtenerHijoDer() {
    return this -> hijoDer;
}

// Fijar el hijo izquierdo
template<class T>
void NodoHuffman<T>::fijarHijoIzq(NodoHuffman<T>* izq) {
    this -> hijoIzq = izq;
}

// Fijar el hijo derecho
template<class T>
void NodoHuffman<T>::fijarHijoDer(NodoHuffman<T>* der) {
    this -> hijoDer = der;
}

// Verificar si es un nodo hoja
template<class T>
bool NodoHuffman<T>::esHoja() {
    return (hijoIzq == nullptr && hijoDer == nullptr);
}