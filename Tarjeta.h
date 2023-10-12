#ifndef TARJETA_H
#define TARJETA_H

#include <iostream>

using namespace std;

class Tarjeta
{
    private:
        int idContinente;
        int idPais;
        string ejercito;
    public:
        Tarjeta();

        int getIdContinente();
        int getIdPais();
        string getEjercito();

        void setIdContinente(int);
        void setIdPais(int);
        void setEjercito(string);
};

#endif