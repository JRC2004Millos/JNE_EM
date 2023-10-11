#include "Jugador.h"

Jugador::Jugador(string n, string c, vector<Ejercito> t)
{
    this->nombre = n;
    this->color = c;
    this->tropas = t;
}

void Jugador::agregarTerritorio(string t)
{
    this->territorios.push_back(t);
}

int Jugador::contarTerritorios()
{
    return this->territorios.size();
}

void Jugador::eliminarTerritorio(string terr)
{
    for(int i=0; i<territorios.size(); i++)
    {
        if(terr == territorios[i])
            territorios.erase(territorios.begin() + i);
    }
}

void Jugador::mostrarTerritorios()
{
    cout<<endl<<"Territorios del jugador "<<this->nombre<<":"<<endl;
    for(string &t : this->territorios)
    {
        cout<<endl<<t;
    }
    cout<<endl;
}

vector<string> Jugador:: getTerritorios()
{
    return territorios;
}

void Jugador:: setTerritorios(vector<string> territorios)
{
    this->territorios = territorios;
}

string Jugador::buscarTerritorio(string t)
{
    for(int i=0; i<territorios.size(); i++)
    {
        if(t == territorios[i])
            return territorios[i];
    }
    return "error";
}

void Jugador::agregarTarjeta(Tarjeta tarjeta)
{
    this->tarjetas.push_back(tarjeta);
}

string Jugador::getNombre()
{
    return this->nombre;
}

void Jugador::setNombre(string nombre)
{
    this->nombre = nombre;
}

string Jugador::getColor()
{
    return color;
}

void Jugador::setColor(string color)
{
    this->color = color;
}

void Jugador::restarInfanteria(int n)
{
    this->tropas[0].modificarCantidad(n, '-');
}

void Jugador::sumarInfanteria(int n)
{
    this->tropas[0].modificarCantidad(n, '+');
}

int Jugador::getInfanteria()
{
    return this->tropas[0].getCantidad();
}

void Jugador::setInfanteria(int infanteria)
{
    this->tropas[0].setCantidad(infanteria);
}

int Jugador::getArtilleria()
{
    return this->tropas[2].getCantidad();
}

void Jugador::setArtilleria(int artilleria)
{
    this->tropas[2].setCantidad(artilleria);
}

int Jugador::getCaballeria()
{
    return this->tropas[1].getCantidad();
}

void Jugador::setCaballeria(int caballeria)
{
    this->tropas[1].getCantidad();
}

vector<Tarjeta> Jugador::getTarjetas()
{
    return this->tarjetas;
}

void Jugador::ToTerritorios()
{
    for(int i=0; i<territorios.size(); i++)
    {
        cout<<endl<<i+1<<". "<<territorios[i];
    }
}
