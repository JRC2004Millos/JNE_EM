#include "Tarjeta.h"

Tarjeta::Tarjeta(){}

int Tarjeta::getIdContinente(){
    return this->idContinente;
}

int Tarjeta::getIdPais(){
    return this->idPais;
}

string Tarjeta::getEjercito(){
    return this->ejercito;
}

void Tarjeta::setIdContinente(int IdContinente) {
    this->idContinente = IdContinente;
}

void Tarjeta::setIdPais(int IdPais) {
    this->idPais = IdPais;
}

void Tarjeta::setEjercito(string ejercito) {
    this->ejercito = ejercito;
}