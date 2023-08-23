#include <iostream>
#include <vector>
#include "Pais.h"

using namespace std;

class Continente{
private:
  int numero;
  int contador;
  string nombre;
  vector <Pais> paises;
public:
  Continente();
  Continente(string);

  void llenarListaPaises();
  void agregarPais(Pais);
  string buscarPais(int);
  vector <Pais> borrarPais(int);
  void mostrarPaises();
  bool paisOcupado(int);
  string verificarContinente(string);
  bool verificarPaises();
  void cambiarTropas(string, int);
  vector<Pais> obtenerDisponibles();
  void marcarOcupado(int,string);

  int getCantiPaises();
  void setContador(int);
  int getContador();
  int getNumero();
  void setNumero(int);
  void setNombre(string);
  string getNombre();
  vector <Pais> getPaises();
  void setPaises(vector <Pais>);

  string toString();
};
