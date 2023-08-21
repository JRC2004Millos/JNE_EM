#ifndef PARTIDA_H
#define PARTIDA_H

#include "Jugador.h"
#include "Continente.h"

using namespace std;

class Partida{
private: 
  vector<Jugador> jugadores;
  vector<Continente> continentes;
public:
  Partida();
  void inicializar();
  void turno();
  void agregarJugador(string,string);
  void getJugadores();
  void setContinentes(vector<Continente>);
  void asignarTerritorios();
  void mostrarContinentes();
  Continente buscarContinente(int);
  vector<Continente> leerContinentes();
  string buscarJugador(string);
  void ubicarEjercito();
};
#endif // PARTIDA_H