#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <vector>

using namespace std;

class Jugador{
private:
  vector<string> territorios;
  string nombre;
  string color;
  int infanteria;
  int artilleria;
  int caballeria;

public:
  Jugador(string,string);
  Jugador(string,string,int);
  void agregarTerritorio(string);
  int contarTerritorios();
  //getters y setters
  vector<string> getTerritorios();
  void setTerritorios(vector<string>);

  string getNombre();
  void setNombre(string);

  string getColor();
  void setColor(string);

  int getInfanteria();
  void setInfanteria(int);

  int getArtilleria();
  void setArtilleria(int);

  int getCaballeria();
  int setCaballeria(int);

};

#endif //JUGADOR_H