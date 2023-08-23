#include "Continente.h"

Continente::Continente(){
  
}

void Continente::agregarPais(Pais p){
  this->paises.push_back(p);
}

string Continente::buscarPais(int t){
  string pais;
  for(Pais p : paises){
    if(t == p.getNumero())
      pais = p.getNombre();
      return pais;
  }
  return "error";
}

vector<Pais> Continente::obtenerDisponibles(){
  vector <Pais> disponibles;
  for(Pais p : paises){
    if(p.getPropietario() == "libre")
      disponibles.push_back(p);
  }
  return disponibles;
}

vector <Pais> Continente::borrarPais(int pais){
  for(auto it = paises.begin(); it != paises.end(); ++it){
    if(pais == it->getNumero())
      paises.erase(it);
  }
  return paises;
}

void Continente::mostrarPaises(){
  cout<<endl<<this->nombre<<endl;
  cout<<endl<<"0. volver a continentes"<<endl;
  for(Pais p : paises){
    cout<<endl<<p.getNumero()<<". "<<p.getNombre()<<endl<<p.getPropietario()<<endl;
  }
}

string Continente::verificarContinente(string nombre){
  int i = 0;
  for(Pais p : paises)
    if(p.getPropietario() == nombre)
      i++;
  if(i == paises.size())
    return this->nombre;
  else
    return "nada";
}

bool Continente::verificarPaises(){
  int i = 0;
  for(Pais p : paises){
    if(p.getPropietario() != "libre")
      i++;
  }
  if(paises.size() == i)
    return true;
  return false;
}

void Continente::marcarOcupado(int n, string nombre){
  paises[n-1].setPropietario(nombre);
  this->contador++;
}

bool Continente::paisOcupado(int numero){
  if(paises[numero-1].getPropietario() == "libre")
    return true;
  return false;
}

void Continente::cambiarTropas(string pais, int trop){
  for(Pais p : paises){
    if(pais== p.getNombre())
      p.setTropas(trop);
  }  
}
//GETTERS Y SETTERS

int Continente::getCantiPaises(){
  return this->paises.size();
}

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

void Continente::setContador(int n){
  this->contador = n;
}

int Continente::getContador(){
  return this->contador;
}

//toString

string Continente::toString(){
  string cadena = this->nombre;
  for(Pais p : this->paises){
    cadena += "\n" + p.getNombre();
  }
  return cadena;
}
