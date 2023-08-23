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
  Jugador(string,string, int, int, int);
  Jugador(string,string,int);
  void agregarTerritorio(string);
  int contarTerritorios();
  //getters y setters
  void mostrarTerritorios();
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
  void setCaballeria(int);

  void ToTerritorios();

};

#endif //JUGADOR_H
