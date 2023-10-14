#include "Pais.h"

using namespace std;

Pais::Pais()
{
    this->nombre = "vacio";
}

void Pais::agregarPaisVecino(string pais)
{
    this->paisesVecinos.push_back(pais);
}

vector <string> Pais::mostrarPaisesVecinos()
{
    vector <string> vecinos;
    for(int i = 0; i < this -> paisesVecinos.size(); i++)
        vecinos.push_back(this->paisesVecinos[i]);
    return vecinos;
}

void Pais::setNombre(string n)
{
    this->nombre = n;
}

string Pais::getNombre()
{
    return this->nombre;
}

void Pais::setNumero(int n)
{
    this->numero = n;
}

int Pais::getNumero()
{
    return this->numero;
}

void Pais::setPropietario(string p)
{
    this->propietario = p;
}

string Pais::getPropietario()
{
    return this->propietario;
}

void Pais::setTropas(int t)
{
    this->tropas = t;
}

int Pais::getTropas()
{
    return this->tropas;
}

void Pais::sumarTropas(int n)
{
    this->tropas += n;
}

void Pais::restarTropas(int n)
{
    this->tropas -= n;
}

void Pais::setTarjeta(Tarjeta t)
{
    this->tarjeta = t;
}

Tarjeta Pais::getTarjeta()
{
    return this->tarjeta;
}