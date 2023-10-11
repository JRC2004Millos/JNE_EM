#include "Ejercito.h"

Ejercito::Ejercito(){}

Ejercito::Ejercito(string tipo, string color){
    this->tipo = tipo;
    this->color = color;
    this->cantidad = 0;
}

Ejercito::Ejercito(string tipo, string color, int cantidad){
    this->tipo = tipo;
    this->color = color;
    this->cantidad = cantidad;
}

void Ejercito::modificarCantidad(int cantidad, char op){
    if(op == '+'){
        this->cantidad += cantidad;
    }
    else if(op == '-'){
        this->cantidad -= cantidad;
    }
    else{
        cout << endl << "Opcion invalida" << endl;
    }
}

void Ejercito::setTipo(string tipo) {
    this->tipo = tipo;
}

void Ejercito::setColor(string color) {
    this->color = color;
}

void Ejercito::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

string Ejercito::getTipo() {
    return this->tipo;
}

string Ejercito::getColor() {
    return this->color;
}

int Ejercito::getCantidad() {
    return this->cantidad;
}