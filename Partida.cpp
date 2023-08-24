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
    void inicializar();
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
    string pedirPais(int);
    void atacar(int);
    void buscarPaisesVecinos(string);
    vector<int> paisAAtacar(string);
    vector<int> getPosicionesPais(string);
    void batalla(vector <int>,vector <int>);
    void fortalecer(int);
    int verificarTropas(int, string);

};
#endif // PARTIDA_H
