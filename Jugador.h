#include "Tarjeta.h"
#include "Ejercito.h"

#include <vector>

class Jugador
{
private:
    vector<string> territorios;
    vector<Ejercito> tropas;
    vector<Tarjeta> tarjetas;
    string nombre;
    string color;

public:
    Jugador();
    Jugador(string,string,vector<Ejercito>);
    void agregarTerritorio(string);
    int contarTerritorios();
    string buscarTerritorio(string);
    void eliminarTerritorio(string);
    void agregarTarjeta(Tarjeta);
    void eliminarTarjetas(string);

    //getters y setters
    void mostrarTerritorios();
    vector<string> getTerritorios();
    void setTerritorios(vector<string>);

    string getNombre();
    void setNombre(string);

    string getColor();
    void setColor(string);

    void restarInfanteria(int);
    void sumarInfanteria(int);
    int getInfanteria();
    void setInfanteria(int);

    int getArtilleria();
    void setArtilleria(int);

    int getCaballeria();
    void setCaballeria(int);

    vector<Ejercito> getEjercitos();
    void setEjercitos(vector<Ejercito>);

    vector<Tarjeta> getTarjetas();
    void setTarjetas(vector<Tarjeta>);

    void ToTerritorios();
};
