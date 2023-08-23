#include "Jugador.h"

using namespace std;

Jugador::Jugador(string n, string c, int i, int a, int ca){
  this->nombre = n;
  this->color = c;
  this->infanteria = i;
  this->artilleria = a;
  this->caballeria = ca;
}

Jugador::Jugador(string n, string c, int i){
  this->nombre = n;
  this->color = c;
  this->infanteria = i;
}

void Jugador::agregarTerritorio(string t){
  this->territorios.push_back(t);
}

int Jugador::contarTerritorios(){
  return this->territorios.size();
}

void Jugador::mostrarTerritorios(){
  cout<<endl<<"Territorios del jugador "<<this->nombre<<":"<<endl;
  for(int i = 0; i < this->territorios.size(); i++){
    cout<<endl<<this->territorios[i];
  }
  cout<<endl;
}

vector<string> Jugador:: getTerritorios(){
  return territorios;
}
void Jugador:: setTerritorios(vector<string> territorios){
  this->territorios = territorios;
}


string Jugador::getNombre(){
  return this->nombre;
}
void Jugador::setNombre(string nombre){
  this->nombre = nombre;
}


string Jugador::getColor(){
  return color;
}
 void Jugador::setColor(string color){
    this->color = color;
 }


int Jugador::getInfanteria(){
  return infanteria;
}
void Jugador::setInfanteria(int infanteria){
  this->infanteria = infanteria;
}


int Jugador::getArtilleria(){
  return artilleria;
}
void Jugador::setArtilleria(int artilleria){
  this->artilleria = artilleria;
}


int Jugador::getCaballeria(){
  return caballeria;
}
void Jugador::setCaballeria(int caballeria){
  this->caballeria = caballeria;
}
void Jugador::ToTerritorios(){
  for(int i=0;i<territorios.size();i++)
    {
      cout<<endl<<i+1<<". "<<territorios[i];
    }
}
