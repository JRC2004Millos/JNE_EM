#include "Continente.h"

Continente::Continente()
{

}

void Continente::agregarPais(Pais p)
{
    this->paises.push_back(p);
}

string Continente::buscarPais(int t)
{
    for(Pais p : this->paises)
    {
        if(t == p.getNumero())
            return p.getNombre();
    }
    return "error";
}

bool Continente::verificarTerritorio(int n, string jugador)
{
    if(paises[n].getPropietario() == jugador)
        return true;
    return false;
}

vector<Pais> Continente::obtenerDisponibles()
{
    vector <Pais> disponibles;
    for(Pais p : this->paises)
    {
        if(p.getPropietario() == "libre")
            disponibles.push_back(p);
    }
    return disponibles;
}

vector <Pais> Continente::borrarPais(int pais)
{
    for(auto it = paises.begin(); it != paises.end(); ++it)
    {
        if(pais == it->getNumero())
            paises.erase(it);
    }
    return paises;
}

void Continente::cambiarPropietario(int n, string nom)
{
    this->paises[n].setPropietario(nom);
}

void Continente::mostrarPaises()
{
    cout<<endl<<this->nombre<<endl;
    cout<<endl<<"0. volver a continentes"<<endl;
    for(Pais p : paises)
    {
        cout<<endl<<p.getNumero()<<". "<<p.getNombre()<<endl<<p.getPropietario()<<endl;
    }
}

string Continente::obtenerPropietario(int n)
{
    return this->paises[n].getPropietario();
}

void Continente::mostrarVecinos(int n)
{
    this->paises[n].mostrarPaisesVecinos();
}

string Continente::verificarContinente(string nombre)
{
    int i = 0;
    for(Pais p : this->paises)
        if(p.getPropietario() == nombre)
            i++;
    if(i == paises.size())
        return this->nombre;
    else
        return "nada";
}

bool Continente::verificarPaises()
{
    int i = 0;
    for(Pais p : this->paises)
    {
        if(p.getPropietario() != "libre")
            i++;
    }
    if(paises.size() == i)
        return true;
    return false;
}

void Continente::marcarOcupado(int n, string nombre)
{
    this->paises[n-1].setPropietario(nombre);
    this->paises[n-1].setTropas(1);
    this->contador++;
}

bool Continente::paisOcupado(int numero)
{
    if(paises[numero-1].getPropietario() == "libre")
        return true;
    return false;
}

Tarjeta Continente::buscarTarjeta(int n)
{
    return this->paises[n].getTarjeta();
}

void Continente::sumarTropas(int p, int trop)
{
    this->paises[p].sumarTropas(trop);
}

void Continente::restarTropas(int p, int trop)
{
    this->paises[p].restarTropas(trop);
}
//GETTERS Y SETTERS

int Continente::getTropas(int n)
{
    return this->paises[n].getTropas();
}

void Continente::getPaisTropas(int n)
{
    cout<<endl<<"Tropas en "<<paises[n].getNombre()<<": "<<paises[n].getTropas()<<endl;
}

int Continente::getCantiPaises()
{
    return this->paises.size();
}

vector <Pais> Continente::getPaises()
{
    return this->paises;
}

void Continente::setPaises(vector<Pais>p)
{
    this->paises = p;
}

int Continente::getNumero()
{
    return this->numero;
}

void Continente::setNumero(int n)
{
    this->numero = n;
}

void Continente::setNombre(string n)
{
    this->nombre = n;
}

string Continente::getNombre()
{
    return this->nombre;
}

void Continente::setContador(int n)
{
    this->contador = n;
}

int Continente::getContador()
{
    return this->contador;
}

//toString

string Continente::toString()
{
    string cadena = this->nombre;
    for(Pais p : this->paises)
    {
        cadena += "\n" + p.getNombre();
    }
    return cadena;
}
