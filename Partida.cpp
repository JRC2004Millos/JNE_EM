#include "Partida.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <random>

using namespace std;

vector <string> separar(string,char);

Partida::Partida()
{

}

void Partida::agregarJugador(string n, string c, int i)
{
    Jugador * j = new Jugador (n,c,i);
    this->jugadores.push_back(*j);
}

vector <Jugador> Partida::getJugadores()
{
    return this->jugadores;
}

void Partida::setContinentes(vector<Continente>c)
{
    this->continentes = c;
}

bool Partida::verificarContinentes()
{
    int i = 0;
    for(Continente c : continentes)
    {
        if(c.getContador() == c.getCantiPaises())
            i++;
    }
    if(i == continentes.size())
        return true;
    return false;
}

int Partida::pedirContinente(string nombre)
{
    int continente;
    do
    {
        mostrarContinentes();
        cout<<endl<<nombre<< ", digite el número del continente que desea escoger: ";
        cin>>continente;
        if(continente<1 || continente>6)
            cout<<endl<<"Ingresó un valor inválido, inténtelo de nuevo"<<endl;
    }
    while(continente<1 || continente>6);
    return continente;
}

int Partida::pedirPais(string nombre, Continente c)
{
    int pais;
    bool encontrado = false;
    do
    {
        c.mostrarPaises();
        cout<<endl<<nombre<< ", digite el número del país que desea escoger: ";
        cin>>pais;
        if(pais == 0)
            c = continentes[pedirContinente(nombre) - 1];
        else if(c.buscarPais(pais) == "error" || !c.paisOcupado(pais))
            cout<<endl<<"El país no fue encontrado o está ocupado, inténtelo de nuevo"<<endl;
        else
            encontrado = true;
    }
    while(!encontrado);
    return pais;
}

void Partida::escogerTerritorio()
{
    int c, p;
    for(Jugador &j : jugadores)
    {
        c = pedirContinente(j.getNombre()) - 1;
        p = pedirPais(j.getNombre(), continentes[c]);
        string territorio = continentes[c].buscarPais(p);
        j.agregarTerritorio(territorio);
        j.sumarInfanteria(1);
        continentes[c].marcarOcupado(p, j.getNombre());
    }
}

void Partida::asignarTerritorios()
{
    cout << endl <<"¡Es hora de escoger sus territorios!" << endl;
    continentes = leerContinentes();
    while(!verificarContinentes())
    {
        escogerTerritorio();
    }
    for(Jugador &j : jugadores)
    {
        j.mostrarTerritorios();
    }
}

Continente Partida::buscarContinente(int n)
{
    for(Continente c : continentes)
    {
        if(n == c.getNumero())
            return c;
    }
    Continente * c = new Continente ();
    return *c;
}

vector<Continente> Partida::leerContinentes()
{
    fstream archivo;
    string leer, token;
    vector<string> cadenas, vecinos;
    vector <Continente> lista;
    int i = 0;
    archivo.open("territorios.txt");
    if (!archivo)
        cout <<  "No se pudo abrir el archivo." << endl;
    else
    {
        getline(archivo,leer);
        while(leer != "FIN")
        {
            i++;
            if(leer != "#")
            {
                Continente c;
                getline(archivo,leer);
                c.setNombre(leer);
                c.setNumero(i);
                c.setContador(0);
                getline(archivo,leer);
                getline(archivo,leer);
                while(leer != "#")
                {
                    Pais p;
                    cadenas = separar(leer, '-');
                    p.setNumero(stoi(cadenas[0]));
                    p.setNombre(cadenas[1]);
                    p.setPropietario("libre");
                    getline(archivo,leer);
                    vecinos = separar(leer, '/');
                    for(int i = 0; i < vecinos.size(); i++)
                        p.agregarPaisVecino(vecinos[i]);
                    getline(archivo,leer);
                    c.agregarPais(p);
                }
                getline(archivo,leer);
                lista.push_back(c);
            }
            if(archivo.eof())
                break;
        }
    }
    return lista;
}

void Partida::mostrarContinentes()
{
    for(Continente c : continentes)
    {
        cout<<endl<<c.getNumero()<<". "<<c.getNombre()<<endl;
    }
}

int Partida::buscarJugador(string nombre)
{
    int i = 0;
    for(Jugador j : jugadores)
    {
        if(nombre == j.getNombre())
            return i;
        i++;
    }
    return -1;
}

void Partida::ubicarEjercito(int pos)
{
    int nuevasTropas = 0;
    nuevasTropas = jugadores[pos].contarTerritorios()/3;
    nuevasTropas += tropasAdicionales(jugadores[pos].getNombre());
    jugadores[pos].sumarInfanteria(nuevasTropas);
}

int Partida::tropasAdicionales (string nombre)
{
    for(Continente c : continentes)
    {
        string continente = c.verificarContinente(nombre);
        if(continente != "nada")
        {
            if(continente == "Australia" || continente == "America del Sur")
                return 2;
            else if(continente == "Asia")
                return 7;
            else if(continente == "Africa")
                return 3;
            else if(continente=="America del norte"||continente=="Europa")
                return 5;
        }
    }
    return 0;
}

int Partida::pedirTropas(int pos)
{
    int trop, actuales;
    do
    {
        cout << endl << "Cuantas tropas desea agregar: ";
        cin >> trop;
        actuales = jugadores[pos].getInfanteria();
        if(trop <= jugadores[pos].getInfanteria())
            jugadores[pos].restarInfanteria(trop);
        else
            cout<<endl<<"Ingresó más tropas de las que tiene, inténtelo de nuevo"<<endl;
    }
    while(trop > actuales);
    return trop;
}

string Partida::pedirPais(int pos)
{
    string pais;
    bool fallo = false, acierto = false;
    do
    {
        cin >> pais;
        if(jugadores[pos].buscarTerritorio(pais) == "error")
        {
            fallo = true;
            cout<<endl<<"No posee este territorio"<<endl;
        }
    }
    while(fallo);
    return pais;
}

void Partida::agregarTropasTerr(int pos)
{
    char seguir;
    int trop;
    string pais;
    do
    {
        cout<<endl<<"Tiene "<<jugadores[pos].getInfanteria()<<" tropas para agregar"<<endl;
        jugadores[pos].ToTerritorios();
        cout << endl << "Digite el nombre del pais al que le desea agregar tropas: ";
        pais = pedirPais(pos);
        vector <int> k = getPosicionesPais(pais);
        cout<<endl<<pais<<" tiene "<<continentes[k[0]].getTropas(k[1])<<" tropas"<<endl;
        trop = pedirTropas(pos);
        continentes[k[0]].sumarTropas(k[1], trop);
        cout<<endl<<pais<<" quedó con "<<continentes[k[0]].getTropas(k[1])<<" tropas"<<endl;
        cout << endl << "Desea agregar mas tropas: si = s, no = n" << endl;
        cin>>seguir;
        cout<<endl<<"Le quedaron "<<jugadores[pos].getInfanteria()<<" tropas para agregar"<<endl;
    }
    while(jugadores[pos].getInfanteria() > 0 && seguir == 's');
}

void Partida::atacar(int pos)
{
    string pais,atacar;
    bool seguir = false;
    vector <int> i, j;
    jugadores[pos].mostrarTerritorios();
    do
    {
        cout<<endl<<"Digite el nombre del país desde el cual desea atacar: ";
        pais = pedirPais(pos);
        i = getPosicionesPais(pais);
        if(continentes[i[0]].getTropas(i[1]) < 2)
            cout<<endl<<"No puede atacar desde un país que tiene solo una tropa"<<endl;
    }
    while(continentes[i[0]].getTropas(i[1]) < 2);
    buscarPaisesVecinos(pais);
    do
    {
        j = paisAAtacar(pais);
        if(continentes[j[0]].verificarTerritorio(j[1], jugadores[pos].getNombre()))
            cout<<endl<<"Usted posee este territorio, no lo puede atacar"<<endl;
        else
            seguir = true;
    }
    while(!seguir);
    batalla(i, j);
}

vector<int> Partida::getPosicionesPais(string pais)
{
    vector<Pais>paises;
    vector<int>pos;
    for(int i = 0; i<continentes.size(); i++)
    {
        paises = continentes[i].getPaises();
        for(int j=0; j<paises.size(); j++)
        {
            if(pais == paises[j].getNombre())
            {
                pos.push_back(i);
                pos.push_back(j);
            }
        }
    }
    return pos;
}

vector <int> Partida::paisAAtacar(string pais)
{
    string atacar;
    vector <Pais> paises;
    vector <int> pos;
    bool encontrado = false;
    do
    {
        cout<<endl<<"Digite el nombre del país a atacar: ";
        cin>>atacar;
        pos = getPosicionesPais(atacar);
        paises = continentes[pos[0]].getPaises();
        if(atacar == paises[pos[1]].getNombre())
            encontrado = true;
        else
            cout<<endl<<"No se encontró este país, inténtelo de nuevo"<<endl;
    }
    while(!encontrado);
    return pos;
}

void Partida::buscarPaisesVecinos(string pais)
{
    vector <Pais> paises;
    for(Continente &c : continentes)
    {
        paises = c.getPaises();
        for(Pais &p : paises)
        {
            if(pais == p.getNombre())
                p.mostrarPaisesVecinos();
        }
    }
}

void Partida::batalla(vector <int> ata, vector <int> def)
{
    //ata Atacante
    //def Defensor
    char seguir;
    int fin = 0;
    vector <Pais> territoriosdef = continentes[def[0]].getPaises();
    vector <Pais> territoriosata = continentes[ata[0]].getPaises();
    do
    {
        cout<<endl<<"Tropas en "<<territoriosata[ata[1]].getNombre() <<": "<<territoriosata[ata[1]].getTropas()<<endl;
        cout<<endl<<"Tropas en "<<territoriosdef[def[1]].getNombre() <<": "<<territoriosdef[def[1]].getTropas()<<endl;
        vector<int>atacante(3);
        int totatac = 0;
        vector<int>defensor(2);
        int totdefen = 0;
        //Tirar los dados
        //Dados rojos
        cout << endl << "Dados del atacante: " << endl;
        srand(time(0));
        for(int i = 0; i < 3; i++)
        {
            atacante[i] = (1+rand() % 6);
            cout << "[" << atacante[i] << "]";
            totatac = totatac + atacante[i];
        }
        cout << endl;
        //Dados blancos
        cout << endl << "Dados del defensor: " << endl;
        srand(time(0));
        for(int i = 0; i < 2; i++)
        {
            defensor[i] = (1+rand() % 6);
            cout << "[" << defensor[i] << "]";
            totdefen = totdefen + defensor[i];
        }
        int aux = atacante[0];
        for(int h = 0; h < atacante.size(); h++)
        {
            if(atacante[h] < aux)
            {
                aux = atacante[h];
            }
        }
        totatac = totatac - aux;

        //Comparar resultados para ver quien gano
        //Gana el atacante
        if(totatac > totdefen)
        {
            int trop;
            cout << endl << "Gana el atacante!" << endl;
            territoriosdef[def[1]].restarTropas(1);
        }
        //Gana el defensor
        else if(totatac < totdefen)
        {
            cout << endl << "Gana el defensor!" << endl;
            territoriosata[ata[1]].restarTropas(1);
        }
        //Empate, gana el defensor
        else if(totatac == totdefen)
        {
            cout << endl << "El resultado fue un empate, gana el defensor!" << endl;
            territoriosata[ata[1]].restarTropas(1);
        }

        //Comparacion para ver si se acabo la partida
        if(territoriosdef[def[1]].getTropas() == 0)
        {
            cout << endl << "Defensor se quedo sin tropas, atacante gana la batalla" << endl;
            fin = 1;
            string propiet;
            propiet = territoriosata[ata[1]].getPropietario();
            territoriosdef[def[1]].setPropietario(propiet);

            cout<<endl<<territoriosdef[def[1]].getPropietario()<<endl;

            int tropas;
            tropas = verificarTropas(territoriosata[ata[1]].getTropas() - 1, territoriosata[ata[1]].getNombre());

            cout<<endl<<"Tropas = "<<tropas<<endl;

            territoriosata[ata[1]].restarTropas(tropas);
            territoriosdef[def[1]].sumarTropas(tropas);
        }
        else if(territoriosata[ata[1]].getTropas() == 1)
        {
            cout << endl << "Al atacante solo le queda una tropa, fin de la batalla" << endl;
            fin = 1;
        }

        cout<<endl<<"Tropas en "<<territoriosata[ata[1]].getNombre() <<": "<<territoriosata[ata[1]].getTropas()<<endl;
        cout<<endl<<"Tropas en "<<territoriosdef[def[1]].getNombre() <<": "<<territoriosdef[def[1]].getTropas()<<endl;

        continentes[ata[0]].setPaises(territoriosata);
        continentes[def[0]].setPaises(territoriosdef);

        cout << endl << "Desea seguir atacando, si = s o no = n" << endl;
        cin>>seguir;
    }
    while(seguir == 's' && fin != 1 );
}

void Partida::turno(int pos)
{
    ubicarEjercito(pos);
    agregarTropasTerr(pos);
    atacar(pos);
    fortalecer(pos);
}

void Partida::fortalecer(int pos)
{
    int enviar;
    jugadores[pos].mostrarTerritorios();
    cout<<endl<<"Digite el nombre del país del cual desea movilizar tropas: ";
    string pais = pedirPais(pos);
    vector <int> i = getPosicionesPais(pais);
    buscarPaisesVecinos(pais);
    string vecino = pedirPais(pos);
    vector <int> j = getPosicionesPais(vecino);
    enviar = verificarTropas(continentes[i[0]].getTropas(i[1]), continentes[i[0]].buscarPais(i[1]));
    continentes[j[0]].sumarTropas(j[1], enviar);
    continentes[i[0]].restarTropas(i[1], enviar);
}

int Partida::verificarTropas(int tropas, string pais)
{
    int enviar;
    do
    {
        cout<<endl<<"Puede enviar hasta "<<tropas<<" tropas desde "<<pais<<", ¿cuántas desea enviar? ";
        cin>>enviar;
        if(enviar > tropas)
            cout<<endl<<"Está enviando más tropas de las que puede, inténtelo de nuevo"<<endl;
    }
    while(enviar > tropas);
    return enviar;
}

vector<string> separar(string cadena, char separador)
{
    int posInicial = 0;
    int posEncontrada = 0;
    string separado;
    vector<string> resultado;

    while(posEncontrada >= 0)
    {
        posEncontrada = cadena.find(separador, posInicial);
        separado = cadena.substr(posInicial, posEncontrada - posInicial);
        posInicial = posEncontrada + 1;
        resultado.push_back(separado);
    }

    return resultado;
}
