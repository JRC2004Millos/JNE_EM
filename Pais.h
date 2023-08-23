#include <iostream>

using namespace std;

class Pais{
private:
  string nombre;
  int numero;
  string propietario;
  int tropas;
public:
  Pais();
  Pais(string,int);
  Pais(string,int,int);
  void setNombre(string);
  string getNombre();
  void setNumero(int);
  int getNumero();
  void setPropietario(string);
  string getPropietario();
  void setTropas(int);
  int getTropas();
};
