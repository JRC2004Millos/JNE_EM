#ifndef PAIS_H
#define PAIS_H

#include <vector>

#include "Tarjeta.h"

class Pais
{
    private:
        string nombre;
        int numero;
        string propietario;
        int tropas;
        vector <string> paisesVecinos;
        Tarjeta tarjeta;
    public:
        Pais();

        void agregarPaisVecino(string);
        vector<string> mostrarPaisesVecinos();

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
        void setTarjeta(Tarjeta);
        Tarjeta getTarjeta();
};

#endif