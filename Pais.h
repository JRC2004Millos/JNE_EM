#include <iostream>
#include <vector>

using namespace std;

class Pais
{
private:
    string nombre;
    int numero;
    string propietario;
    int tropas;
    vector <string> paisesVecinos;
public:
    Pais();
    Pais(string,int);
    Pais(string,int,int);

    void agregarPaisVecino(string);
    void mostrarPaisesVecinos();

    void setNombre(string);
    string getNombre();
    void setNumero(int);
    int getNumero();
    void setPropietario(string);
    string getPropietario();
    void sumarTropas(int);
    void restarTropas(int);
    void setTropas(int);
    int getTropas();

};
