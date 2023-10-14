#include "Jugador.h"

Jugador::Jugador(){}

Jugador::Jugador(string n, string c, vector<Ejercito> t)
{
    this->nombre = n;
    this->color = c;
    this->tropas = t;
}

void Jugador::agregarTerritorio(Pais p)
{
    this->territorios.push_back(p);
}

int Jugador::contarTerritorios()
{
    return this->territorios.size();
}

void Jugador::eliminarTerritorio(string terr)
{
    for(auto it = territorios.begin(); it != territorios.end(); ++it){
        if(terr == it->getNombre())
            territorios.erase(it);
    }
}

void Jugador::mostrarTerritorios()
{
    cout<<endl<<"Territorios del jugador "<<this->nombre<<":"<<endl;
    for(auto it = territorios.begin(); it != territorios.end(); ++it){
        cout << endl << it->getNumero() << ". " << it->getNombre();
    }
    cout<<endl;
}

vector<Pais> Jugador:: getTerritorios()
{
    return territorios;
}

void Jugador:: setTerritorios(vector<Pais> territorios)
{
    this->territorios = territorios;
}

int Jugador::buscarTerritorio(int t)
{
    for(auto it = territorios.begin(); it != territorios.end(); ++it){
        if(t == it->getNumero())
            return it->getNumero();
    }
    return -1;
}

void Jugador::agregarTarjeta(Tarjeta tarjeta)
{
    this->tarjetas.push_back(tarjeta);
}

void Jugador::eliminarTarjetas(string eliminar)
{
    bool inf = false;
    bool art = false;
    bool cab = false;
    if(eliminar == "Todos"){
        for(auto it = this->tarjetas.begin(); it != this->tarjetas.end(); ++it){
            if(it->getEjercito() == "Infanteria" && !inf){
                inf = true;
                this->tarjetas.erase(it);
            } 
            else if(it->getEjercito() == "Caballeria" && !inf){
                cab = true;
                this->tarjetas.erase(it);
            } 
            else if(it->getEjercito() == "Artilleria" && !inf){
                art = true;
                this->tarjetas.erase(it);
            }  
        }
    }
    else{
        int n = 0;
        for(auto it = this->tarjetas.begin(); n < 3; ++it){
            if(eliminar == it->getEjercito()){
                this->tarjetas.erase(it);
                n++;
            }
        }
    }
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

vector<Ejercito> Jugador::getEjercitos()
{
    return this->tropas;
}

void Jugador::setEjercitos(vector <Ejercito> ejercitos)
{
    this->tropas = ejercitos;
}

vector<Tarjeta> Jugador::getTarjetas()
{
    return this->tarjetas;
}

void Jugador::setTarjetas(vector <Tarjeta> tarjetas)
{
    this->tarjetas = tarjetas;
}
