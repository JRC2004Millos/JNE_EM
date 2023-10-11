#ifndef PARTIDA_H
#define PARTIDA_H

#include "Jugador.h"
#include "Continente.h"

using namespace std;

class Partida
{
private:
    vector<Jugador> jugadores;
    vector<Continente> continentes;
public:
    Partida();
    void turno(int);
    void agregarJugador(string,string,int);
    vector <Jugador> getJugadores();
    void setContinentes(vector<Continente>);
    void asignarTerritorios();
    void mostrarContinentes();
    bool verificarContinentes();
    void escogerTerritorio();
    int pedirContinente(string);
    int pedirPais(string, Continente);
    Continente buscarContinente(int);
    vector<Continente> leerContinentes();
    int buscarJugador(string);
    void ubicarEjercito(int);
    int tropasAdicionales(string);
    void agregarTropasTerr(int);
    int pedirTropas(int);
    string pedirPais(int, string);
    void atacar(int);
    void buscarPaisesVecinos(int, int);
    vector<int> paisAAtacar(string);
    vector<int> getPosicionesPais(string);
    char batalla(vector <int>,vector <int>);
    void fortalecer(int);
    int verificarTropas(int, string);
    bool verTropas();
    int lanzarDado();
    void asignarUltimasTropas();
    string pedirTerritorio(int);

};
#endif // PARTIDA_H
