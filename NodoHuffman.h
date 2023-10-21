#ifndef NODOHUFFMAN_H
#define NODOHUFFMAN_H



class NodoHuffman {
public:
    char dato;
    int frecuencia;
    int ascii;
    NodoHuffman* izquierda;
    NodoHuffman* derecha;

    NodoHuffman(char d, int f);
};

#endif // NODOHUFFMAN_H
