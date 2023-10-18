#ifndef NODOHUFFMAN_H
#define NODOHUFFMAN_H

class NodoHuffman {
public:
    char dato;
    int frecuencia;
    NodoHuffman* izquierda;
    NodoHuffman* derecha;

    NodoHuffman(char d, int f);
};

#endif // NODOHUFFMAN_H
