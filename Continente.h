#include <iostream>
#include <vector>

#include "Pais.h"

using namespace std;

class Continente
{
private:
    int numero;
    int contador;
    string nombre;
    vector <Pais> paises;
public:
    Continente();

    bool verificarTerritorio(int, string);
    void agregarPais(Pais);
    Pais buscarPais(int);
    vector <Pais> borrarPais(int);
    void mostrarPaises();
    bool paisOcupado(int);
    string verificarContinente(string);
    bool verificarPaises();
    void sumarTropas(int, int);
    void restarTropas(int, int);
    void setTropas(int, int);
    string obtenerPropietario(int);
    void marcarOcupado(int, string);
    vector<string> mostrarVecinos(int);
    void getPaisTropas(int);
    void cambiarPropietario(int, string);
    Tarjeta buscarTarjeta(int);

    int getCantiPaises();
    void setContador(int);
    int getContador();
    int getNumero();
    void setNumero(int);
    void setNombre(string);
    string getNombre();
    vector <Pais> getPaises();
    void setPaises(vector <Pais>);
    int getTropas(int);

    string toString();
};
