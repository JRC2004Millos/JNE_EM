#include "Pais.h"

using namespace std;

Pais::Pais()
{

}

void Pais::agregarPaisVecino(string pais)
{
    this->paisesVecinos.push_back(pais);
}

void Pais::mostrarPaisesVecinos()
{
    cout<<endl<<"Fronteras de: "<<this->nombre<<endl;
    for(int i = 0; i < this -> paisesVecinos.size(); i++)
        cout <<endl << this->paisesVecinos[i];
    cout<<endl;
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