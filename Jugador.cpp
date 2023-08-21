#include "Jugador.h"

using namespace std;

Jugador::Jugador(string n, string c, int i, int a, int ca){
  this->nombre = n;
  this->color = c;
  this->infanteria = i;
  this->artilleria = a;
  this->caballeria = ca;
}

Jugador::Jugador(string n, string c){
  this->nombre = n;
  this->color = c;
}

void Jugador::agregarTerritorio(string t){
  territorios.push_back(t);
}

int Jugador::contarTerritorios(){
  return this->territorios.size();
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
  this->infanteria = tropas_j;
}