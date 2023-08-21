#include "Continente.h"

Continente::Continente(){
  
}

void Continente::agregarPais(Pais p){
  this->paises.push_back(p);
}

string Continente::buscarPais(int t){
  for(Pais p : paises){
    if(t == p.getNumero())
      return p.getNombre();
  }
  return "error";
}

vector <Pais> Continente::borrarPais(int pais){
  for(auto it = paises.begin(); it != paises.end(); ++it){
    if(pais == it->getNumero())
      paises.erase(it);
  }
  return paises;
}

void Continente::mostrarPaises(){
  for(Pais p : paises){
    cout<<endl<<p.getNumero()<<". "<<p.getNombre()<<endl;
  }
}

string Continente::paisOcupado(int numero, string jugador){
  for(Pais p : paises){
    if(p.getNumero() == numero && p.getPropietario() != "libre"){
      p.setPropietario(jugador);
      return p.getPropietario();
    }
  }
  return "libre";
}

//GETTERS Y SETTERS

vector <Pais> Continente::getPaises(){
  return this->paises;
}

void Continente::setPaises(vector<Pais>paises){
  this->paises = paises;
}

int Continente::getNumero(){
  return this->numero;
}

void Continente::setNumero(int n){
  this->numero = n;
}

void Continente::setNombre(string n){
  this->nombre = n;
}

string Continente::getNombre(){
  return this->nombre;
}

//toString

string Continente::toString(){
  string cadena = this->nombre;
  for(Pais p : this->paises){
    cadena += "\n" + p.getNombre();
  }
  return cadena;
}