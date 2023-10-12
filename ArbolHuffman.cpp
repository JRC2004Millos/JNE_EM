#include "ArbolHuffman.h"
#include "NodoHuffman.h"


// Constructor por defecto
template<class T>
ArbolHuffman<T>::ArbolHuffman() : raiz(nullptr) {}

// Destructor
template<class T>
ArbolHuffman<T>::~ArbolHuffman() {
    liberarArbol(raiz);
}

// Función para liberar la memoria de los nodos del árbol de forma recursiva
template<class T>
void ArbolHuffman<T>::liberarArbol(NodoHuffman<T>* nodo) {
    if (nodo == nullptr) {
        return;
    }

    // Liberar los hijos izquierdo y derecho
    liberarArbol(nodo->obtenerHijoIzq());
    liberarArbol(nodo->obtenerHijoDer());

    // Eliminar el nodo actual
    delete nodo;
}

// Comprueba si el árbol está vacío
template<class T>
bool ArbolHuffman<T>::esVacio() {
    return (raiz == nullptr);
}

// Inserta un símbolo con su frecuencia en el árbol
template<class T>
void ArbolHuffman<T>::insertar(T simbolo, int frecuencia) {
    // Crear un nuevo nodo con el símbolo y frecuencia
    NodoHuffman<T>* nuevoNodo = new NodoHuffman<T>(simbolo, frecuencia);

    // Si el árbol está vacío, el nuevo nodo se convierte en la raíz
    if (raiz == nullptr) {
        raiz = nuevoNodo;
        return;
    }

    // Agregar el nuevo nodo a la cola de prioridad (heap)
    std::priority_queue<NodoHuffman<T>, std::vector<NodoHuffman<T>>, ComparadorFrecuencia<T>> colaPrioridad;
    colaPrioridad.push(raiz); // Agregar la raíz existente

    // Construir el árbol de Huffman fusionando nodos de menor frecuencia
    while (!colaPrioridad.empty()) {
        // Extraer los dos nodos de menor frecuencia de la cola de prioridad
        NodoHuffman<T>* nodo1 = colaPrioridad.top();
        colaPrioridad.pop();

        // Crear un nuevo nodo interno con frecuencia combinada
        int frecuenciaCombinada = nodo1->obtenerFrecuencia() + frecuencia;
        NodoHuffman<T>* nuevoNodoInterno = new NodoHuffman<T>(T(), frecuenciaCombinada);

        // Establecer los nodos existentes como hijos del nuevo nodo interno
        nuevoNodoInterno->fijarHijoIzq(nodo1);
        nuevoNodoInterno->fijarHijoDer(nuevoNodo);

        // El nuevo nodo interno se convierte en el nuevo nodo raíz
        raiz = nuevoNodoInterno;
        return;
    }
}

// Implementa la lógica de codificación de datos
template<class T>
std::string ArbolHuffman<T>::codificarDatos(const std::string& datos) {
    // Verificar que el árbol no esté vacío
    if (raiz == nullptr) {
        return "El árbol de Huffman está vacío. No se puede codificar.\n";
    }

    std::unordered_map<T, std::string> codigos;

    // Asignar códigos Huffman a los símbolos del árbol
    asignarCodigosHuffman(raiz, "", codigos);

    // Codificar la secuencia de datos utilizando los códigos Huffman
    std::string datosCodificados;
    for (const T& simbolo : datos) {
        if (codigos.find(simbolo) != codigos.end()) {
            datosCodificados += codigos[simbolo];
        } else {
            std::cerr << "Símbolo desconocido en los datos: " << simbolo << std::endl;
        }
    }

    return datosCodificados;
}

// Función recursiva para asignar códigos Huffman a los símbolos del árbol
template<class T>
void ArbolHuffman<T>::asignarCodigosHuffman(NodoHuffman<T>* nodo, const std::string& codigoActual, std::unordered_map<T, std::string>& codigos) {
    if (nodo == nullptr) {
        return;
    }

    // Si el nodo es una hoja, asignar el código Huffman al símbolo
    if (nodo->esHoja()) {
        codigos[nodo->obtenerDato()] = codigoActual;
    }

    // Recorrer el árbol recursivamente, agregando '0' para el hijo izquierdo y '1' para el hijo derecho
    asignarCodigosHuffman(nodo->obtenerHijoIzq(), codigoActual + '0', codigos);
    asignarCodigosHuffman(nodo->obtenerHijoDer(), codigoActual + '1', codigos);
}

// Implementa la lógica de decodificación de datos
template<class T>
std::string ArbolHuffman<T>::decodificarDatos(const std::string& codigo) {
    NodoHuffman<T>* nodoActual = raiz; // Comenzar desde la raíz
    std::string decodificacion;

    for (char bit : codigo) {
        if (bit == '0') {
            // Mover hacia el hijo izquierdo para '0'
            nodoActual = nodoActual->obtenerHijoIzq();
        } else if (bit == '1') {
            // Mover hacia el hijo derecho para '1'
            nodoActual = nodoActual->obtenerHijoDer();
        }

        if (nodoActual->esHoja()) {
            // Si llegamos a una hoja, hemos encontrado un símbolo decodificado
            decodificacion += nodoActual->obtenerDato();
            nodoActual = raiz; // Volver a la raíz para continuar decodificando
        }
    }

    // Asegurarse de manejar correctamente cualquier bit adicional
    // que no forme parte de un símbolo codificado completo
    if (nodoActual != raiz) {
        return "Error: Secuencia de decodificación incompleta.\n";
    }
    return decodificacion;
}


template<class T>
void ArbolHuffman<T>::inOrden(NodoHuffman<T>* nodo) {
    if (nodo == nullptr) {
        return;
    }

    if (nodo->obtenerHijoIzq() != nullptr) {
        inOrden(nodo->obtenerHijoIzq());
    }

    if (nodo->esHoja()){
        std::cout << "Simbolo: " << nodo->obtenerDato() << ", Frecuencia: " << nodo->obtenerFrecuencia() << std::endl;
    }

    if (nodo->obtenerHijoDer() != nullptr) {
        inOrden(nodo->obtenerHijoDer());
    }
}

// Función pública para realizar el recorrido en orden
template<class T>
void ArbolHuffman<T>::verificarArbol() {
    inOrden(raiz);
}
