#ifndef PARTIDA_H
#define PARTIDA_H

#include "Jugador.h"
#include "Continente.h"

#include <queue>
#include <vector>

using namespace std;

class Partida
{
private:
    vector<Jugador> jugadores;
    vector<Continente> continentes;
    int cantidadIntercambios;
public:
    Partida();
    void turno(int);
    void agregarJugador(string,string,int);
    void agregarJugador(Jugador);
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
    string pedirPaisPorNumero(int, string);
    void atacar(int);
    vector<string> buscarPaisesVecinos(int, int);
    vector<int> paisAAtacar(int, int);
    vector<int> getPosicionesPais(string);
    char batalla(vector <int>,vector <int>);
    void fortalecer(int);
    int verificarTropas(int, string);
    bool verTropas();
    int lanzarDado();
    void asignarUltimasTropas();
    int intercambiarCartas();
    string archivoTexto();
    queue<string> leerTxt(string);
    bool verificarGanador(string);
    vector<Pais> obtenerTerritorios();

    void setJugadores(vector<Jugador>);
};
#endif // PARTIDA_H
