#include <iostream>
#include <vector>
#include "Pais.h"

using namespace std;

class Continente{
private:
  int numero;
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
  string paisOcupado(int,string);

  int getNumero();
  void setNumero(int);
  void setNombre(string);
  string getNombre();
  vector <Pais> getPaises();
  void setPaises(vector <Pais>);

  string toString();
};