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
  void agregarJugador(string,string,int);
  void getJugadores();
  void setContinentes(vector<Continente>);
  void asignarTerritorios();
  void mostrarContinentes();
  bool verificarContinentes();
  void escogerTerritorio();
  int pedirContinente(string);
  int pedirPais(string, Continente);
  Continente buscarContinente(int);
  vector<Continente> leerContinentes();
  string buscarJugador(string);
  void ubicarEjercito(Jugador);
  int tropasAdicionales(string);
  void turno(int);
  void agregarTropasTerr(Jugador);
  void atacar();
  int Dado();
};
#endif // PARTIDA_H
