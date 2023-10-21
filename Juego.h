#include "Partida.h"

#include <list>
#include <queue>
#include <bitset>

class Juego{
    private:
    int cantJugadores;
    Partida partida;
    queue <string> colaJugadores;
    public:
        Juego();
        void comandos();
        bool guardar_comprimido(bool, string);
        void ayuda();
        bool inicializar(bool);
        void leerJugadores();
        bool inicializarArchivo(bool,string);
        void turno(bool,string);
        void conquista_barata(bool);
        void guardar(bool,string,fstream&);
        void costo_conquista(bool);
        void llenarColores(list<string>*);
        string asignarColor(int, list<string> *);
        string getNombreArchivo(string);
        string getId(string);
        int asignarInfanteria(int);
        queue <string> pedirColaJugadores();
        vector <string> separar(string,char);
        void leerTxt(string);
        void leerBin(string);
        bitset<8> stringToBitset(string);
        string quitarEspacios(string);
};