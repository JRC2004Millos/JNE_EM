#include "Tarjeta.h"

class Jugador
{
private:
    vector<string> territorios;
    vector<Ejercito> tropas;
    vector<Tarjeta> tarjetas;
    string nombre;
    string color;

public:
    Jugador(string,string,vector<Ejercito>);
    void agregarTerritorio(string);
    int contarTerritorios();
    string buscarTerritorio(string);
    void eliminarTerritorio(string);
    void agregarTarjeta(Tarjeta);

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

    vector<Tarjeta> getTarjetas();

    void ToTerritorios();
};
