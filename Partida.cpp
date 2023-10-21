#include "Partida.h"

#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <random>

vector <string> split(string,char);

Partida::Partida()
{ 
    this->cantidadIntercambios = 0;
}

void Partida::agregarJugador(string n, string c, int i)
{
    vector <Ejercito> e;
    Ejercito in = Ejercito("Infanteria", c, i);
    Ejercito ca = Ejercito("Caballeria", c);
    Ejercito ar = Ejercito("Artilleria", c);
    e.push_back(in);
    e.push_back(ca);
    e.push_back(ar);
    Jugador * j = new Jugador (n,c,e);
    this->jugadores.push_back(*j);
}

void Partida::agregarJugador(Jugador j)
{
    this->jugadores.push_back(j);
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
        else if(c.buscarPais(pais).getNombre() == Pais().getNombre() || !c.paisOcupado(pais))
            cout<<endl<<"El país no fue encontrado o está ocupado, inténtelo de nuevo"<<endl;
        else
            encontrado = true;
    }while(!encontrado);
    return pais;
}

void Partida::escogerTerritorio()
{
    int c, p;
    for(Jugador &j : jugadores)
    {
        c = pedirContinente(j.getNombre()) - 1;
        p = pedirPais(j.getNombre(), continentes[c]);
        Pais territorio = continentes[c].buscarPais(p);
        j.agregarTerritorio(territorio);
        j.restarInfanteria(1);
        continentes[c].marcarOcupado(p, j.getNombre());
    }
}

void Partida::asignarTerritorios()
{
    cout << endl <<"¡Es hora de escoger sus territorios!" << endl;
    continentes = leerContinentes();
    while(!verificarContinentes())
        escogerTerritorio();
    while(!verTropas())
        asignarUltimasTropas();
    for(Jugador &j : jugadores)
        j.mostrarTerritorios();
}

void Partida::asignarUltimasTropas()
{
    string territorio;
    vector <int> pos;
    int i=0;
    for(Jugador &j : this->jugadores)
    {
        string mensaje = "Digite el numero de un territorio para colocar una tropa: ";
        territorio = pedirPaisPorNumero(i, mensaje);
        pos = getPosicionesPais(territorio);
        continentes[pos[0]].sumarTropas(pos[1], 1);
        j.restarInfanteria(1);
        continentes[pos[0]].getPaisTropas(pos[1]);
        cout<<endl<<"Le quedan "<<j.getInfanteria()<<" tropas"<<endl;
        i++;
    }
}

bool Partida::verTropas()
{
    int i = 0;
    for(Jugador &j : this->jugadores)
    {
        if(j.getInfanteria() == 0)
            i++;
    }
    if(i == jugadores.size())
        return true;
    return false;
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
                    cadenas = split(leer, '-');
                    p.setNumero(stoi(cadenas[0]));
                    p.setNombre(cadenas[1]);
                    p.setPropietario("libre");
                    getline(archivo,leer);
                    vecinos = split(leer, '/');
                    for(int i = 0; i < vecinos.size(); i++)
                        p.agregarPaisVecino(vecinos[i]);
                    Tarjeta t;
                    int num = rand() % 3 + 1;
                    switch (num)
                    {
                        case 1:
                            t.setEjercito("Infanteria");
                            break;
                        case 2:
                            t.setEjercito("Caballeria");
                        case 3:
                            t.setEjercito("Artilleria");
                    }
                    t.setIdContinente(i);
                    t.setIdPais(stoi(cadenas[0]));
                    p.setTarjeta(t);
                    c.agregarPais(p);
                    getline(archivo,leer);
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
    for(Continente &c : continentes)
    {
        cout<<endl<<c.getNumero()<<". "<<c.getNombre()<<endl;
    }
}

int Partida::buscarJugador(string nombre)
{
    int i = 0;
    for(Jugador &j : jugadores)
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

string Partida::pedirPaisPorNumero(int pos, string mensaje)
{
    int pais;
    string territorio;
    bool fallo = false, acierto = false;
    vector <Pais> paises = jugadores[pos].getTerritorios();  
    do{  
        for(int i = 0; i < paises.size(); i++)
            cout << endl << i + 1 << ". " << paises[i].getNombre() << " - Tropas: " << paises[i].getTropas();  
        cout << endl << endl << mensaje << endl;
        cin >> pais;
        if(pais > paises.size() || pais < 1){
            fallo = true;
            cout<<endl<<"No posee este territorio"<<endl;
        }
        else{
            territorio = paises[pais-1].getNombre();
            fallo = false;
        }
    }
    while(fallo);
    return territorio;
}

void Partida::agregarTropasTerr(int pos)
{
    char seguir;
    int trop;
    string pais;
    cout << endl << "---------- PLANEAR ----------" << endl;
    do
    {
        cout<<endl<<"Tiene "<<jugadores[pos].getInfanteria()<<" tropas para agregar"<<endl;
        string mensaje = "Digite el número del pais al que le desea agregar tropas: ";
        pais = pedirPaisPorNumero(pos, mensaje);
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
    string pais;
    bool seguir = false;
    vector <int> i, j;
    char continuar;
    do{
        seguir = false;
        cout << endl << "---------- ATACAR ----------" << endl;
        do
        {
            string mensaje = "Digite el numero del país desde el cual desea atacar: ";
            pais = pedirPaisPorNumero(pos, mensaje);
            i = getPosicionesPais(pais);
            if(continentes[i[0]].getTropas(i[1]) < 2)
                cout<<endl<<"No puede atacar desde un país que tiene solo una tropa"<<endl;
        }
        while(continentes[i[0]].getTropas(i[1]) < 2);
        do
        {
            j = paisAAtacar(i[0], i[1]);
            if(continentes[j[0]].verificarTerritorio(j[1], jugadores[pos].getNombre()))
                cout<<endl<<"Usted posee este territorio, no lo puede atacar"<<endl;
            else
                seguir = true;
        }
        while(!seguir);
        continuar = batalla(i, j);
    }while(continuar == 's');
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

vector <int> Partida::paisAAtacar(int c, int p)
{
    int atacar;
    string pais;
    vector <Pais> paises;
    vector <string> vecinos = buscarPaisesVecinos(c, p);
    vector <int> pos;
    bool encontrado = false;
    do
    {
        for(int i = 0; i < vecinos.size(); i++)
            cout << endl << i + 1 << ". " << vecinos[i];
        cout << endl << endl << "Digite el numero del país a atacar: ";
        cin >> atacar;
        pais = vecinos[atacar-1];
        pos = getPosicionesPais(pais);
        paises = continentes[pos[0]].getPaises();
        if(pais == paises[pos[1]].getNombre()){
            encontrado = true;
        }
        else
            cout<<endl<<"No se encontró este país, inténtelo de nuevo"<<endl;
    }
    while(!encontrado);
    return pos;
}

vector <string> Partida::buscarPaisesVecinos(int c, int p)
{
    return this->continentes[c].mostrarVecinos(p);
}

char Partida::batalla(vector <int> ata, vector <int> def)
{
    //ata Atacantea
    //def Defensor
    char seguir;
    int fin = 0;
    do
    {
        continentes[ata[0]].getPaisTropas(ata[1]);
        continentes[def[0]].getPaisTropas(def[1]);

        vector <int> atacante;
        vector <int> defensor;

        //Tirar los dados
        //Dados rojos
        cout << endl << "Dados del atacante: " << endl;
        srand(time(NULL));
        for(int i = 0; i<3; i++)
        {   
            atacante.push_back(lanzarDado());
            cout<<"["<<atacante[i]<<"]";
        }
        cout<<endl;

        //Suma el total de los dados del atacante
        //y encuentra el menor para restarlo
        int totalAtacante = 0;
        int menorAtacante = atacante[0];
        for(int i = 0; i < atacante.size(); i++){
            totalAtacante += atacante[i];
            if(menorAtacante > atacante[i])
                menorAtacante = atacante[i];
        }
        totalAtacante -= menorAtacante;

        //Dados blancos
        cout << endl << "Dados del defensor: " << endl;
        for(int i = 0; i<2; i++)
        {  
            defensor.push_back(lanzarDado());
            cout<<"["<<defensor[i]<<"]";
        }
        cout<<endl;

        //Suma el total de los dados del defensor
        int totalDefensor = 0;
        for(int i = 0; i < defensor.size(); i++)
            totalDefensor += defensor[i];

        //Comparar resultados para ver quien gano
        //Gana el atacante
        if(totalAtacante > totalDefensor)
        {
            cout << endl << "Gana el atacante!" << endl;
            continentes[def[0]].restarTropas(def[1], 1);
        }
        //Gana el defensor
        else if(totalAtacante < totalDefensor)
        {
            cout << endl << "Gana el defensor!" << endl;
            continentes[ata[0]].restarTropas(ata[1], 1);
        }
        //Empate, gana el defensor
        else if(totalAtacante == totalDefensor)
        {
            cout << endl << "El resultado fue un empate, gana el defensor!" << endl;
            continentes[ata[0]].restarTropas(ata[1], 1);
        }

        //Comparacion para ver si se acabo la partida
        if(continentes[def[0]].getTropas(def[1]) == 0)
        {
            cout << endl << "Defensor se quedo sin tropas, atacante gana la batalla" << endl;
            int posD = buscarJugador(continentes[def[0]].obtenerPropietario(def[1]));
            
            jugadores[posD].eliminarTerritorio(continentes[def[0]].buscarPais(def[1]+1).getNombre());

            continentes[def[0]].cambiarPropietario(def[1], continentes[ata[0]].obtenerPropietario(ata[1]));

            int posA = buscarJugador(continentes[ata[0]].obtenerPropietario(ata[1]));
            
            jugadores[posA].agregarTarjeta(continentes[def[0]].buscarTarjeta(def[1]));

            jugadores[posA].agregarTerritorio(continentes[def[0]].buscarPais(def[1]+1));

            int tropas;

            tropas = verificarTropas(continentes[ata[0]].getTropas(ata[1]) - 1, continentes[ata[0]].buscarPais(ata[1]+1).getNombre());

            continentes[ata[0]].restarTropas(ata[1], tropas);
            continentes[def[0]].sumarTropas(def[1], tropas);

            continentes[ata[0]].getPaisTropas(ata[1]);
            continentes[def[0]].getPaisTropas(def[1]);

            cout << endl << "Desea seguir atacando, si = s o no = n" << endl;
            cin >> seguir;
            return seguir;
        }
        else if(continentes[ata[0]].getTropas(ata[1]) == 1)
        {
            cout << endl << "Al atacante solo le queda una tropa, fin de la batalla" << endl;
            fin = 1;
        }

        continentes[ata[0]].getPaisTropas(ata[1]);
        continentes[def[0]].getPaisTropas(def[1]);

        cout << endl << "Desea seguir atacando, si = s o no = n" << endl;
        cin>>seguir;
    }
    while(seguir == 's' && fin != 1 );

    return 'n';
}

int Partida::lanzarDado () {
    return rand() % 6 + 1; // Número aleatorio entre 1 y 6
}

void Partida::turno(int pos)
{
    vector <Tarjeta> tarjetas = jugadores[pos].getTarjetas();
    int inf = 0, cab = 0, art = 0;
    if(tarjetas.size() >= 3){
        //Si todos son el mismo ejercito
        for(int i = 0; i < tarjetas.size(); i++){
            if(tarjetas[i].getEjercito() == "Infanteria")
                inf++;
            else if(tarjetas[i].getEjercito() == "Caballeria")
                cab++;
            else if(tarjetas[i].getEjercito() == "Artilleria")
                art++;
        }

        if(inf >= 3){
            jugadores[pos].sumarInfanteria(intercambiarCartas());
            jugadores[pos].eliminarTarjetas("Infanteria");
        }
        else if(cab >= 3){
            jugadores[pos].sumarInfanteria(intercambiarCartas());
            jugadores[pos].eliminarTarjetas("Caballeria");
        }
        else if(art >= 3){
            jugadores[pos].sumarInfanteria(intercambiarCartas());
            jugadores[pos].eliminarTarjetas("Artilleria");
        }
        else if(inf >= 1 && cab >= 1 && art >= 1){
            jugadores[pos].sumarInfanteria(intercambiarCartas());
            jugadores[pos].eliminarTarjetas("Todos");
        }
        
    }
    ubicarEjercito(pos);
    agregarTropasTerr(pos);
    atacar(pos);
    fortalecer(pos);
}

int Partida::intercambiarCartas()
{
    this->cantidadIntercambios++;
    if(this->cantidadIntercambios < 6){
        switch (this->cantidadIntercambios)
        {
            case 1:
                return 4;
            case 2:
                return 6;
            case 3:
                return 8;
            case 4:
                return 10;
            case 5:
                return 12;
            case 6:
                return 15;
        }
    }
    else{
        return (this->cantidadIntercambios - 6) * 5 + 15;
    }
}

void Partida::fortalecer(int pos)
{
    int enviar, veci;
    bool fallo;
    cout << endl << "---------- FORTALECER ----------" << endl;
    string mensaje = "Digite el numero del pais del cual desea movilizar tropas: ";
    string pais = pedirPaisPorNumero(pos, mensaje);
    vector <int> i = getPosicionesPais(pais);
    continentes[i[0]].getPaisTropas(i[1]);
    vector <string> vecinos = buscarPaisesVecinos(i[0], i[1]);
    string vecino;
    do{
        fallo = false;
        for(int i = 0; i < vecinos.size(); i++)
            cout << endl << i + 1 << ". " << vecinos[i];
        cout << endl;
        cout << endl << "Digite el numero del pais al cual desea movilizar tropas: ";
        cin >> veci;
        if(veci < 1 || veci > vecinos.size())
            cout << endl << "Numero invalido, intentelo de nuevo" << endl;
        else{
            vecino = vecinos[veci-1];
            vector <int> j = getPosicionesPais(vecino);
            if(continentes[j[0]].verificarTerritorio(j[1], continentes[i[0]].obtenerPropietario(i[1]))){
                continentes[j[0]].getPaisTropas(j[1]);
                enviar = verificarTropas(continentes[i[0]].getTropas(i[1])-1, continentes[i[0]].buscarPais(i[1]+1).getNombre());
                continentes[j[0]].sumarTropas(j[1], enviar);
                continentes[i[0]].restarTropas(i[1], enviar);
                continentes[j[0]].getPaisTropas(j[1]);
                continentes[i[0]].getPaisTropas(i[1]);
                fallo = true;
            }
            else
                cout << endl << "No posee este territorio, intentelo de nuevo" << endl;
        }
    }while(veci < 1 || veci > vecinos.size() || !fallo);
}

int Partida::verificarTropas(int tropas, string pais)
{
    int enviar;
    do
    {
        cout<<endl<<"Puede enviar hasta "<<tropas<<" tropas desde "<<pais<<", ¿cuantas desea enviar? ";
        cin>>enviar;
        if(enviar > tropas)
            cout<<endl<<"Esta enviando mas tropas de las que puede, intentelo de nuevo"<<endl;
    }
    while(enviar > tropas);
    return enviar;
}

string Partida::archivoTexto()
{
    string texto = "";

    //DATOS DE LOS JUGADORES
    texto += "Jugadores\n";
    for(Jugador j : this->jugadores){
        vector <Tarjeta> tarjetas = j.getTarjetas();
        vector <Pais> territorios = j.getTerritorios();
        vector <Ejercito> ejercitos = j.getEjercitos();
        texto += j.getNombre() + "/" + j.getColor() + "/";
        for(int i = 0; i < tarjetas.size(); i++){
            texto += to_string(tarjetas[i].getIdContinente()) + "-" + to_string(tarjetas[i].getIdPais()) + "-" + tarjetas[i].getEjercito();
            if(i < tarjetas.size() - 1){
                texto += "#";
            }
        }
        texto += "/";
        for(int i = 0; i < ejercitos.size(); i++){
            texto += to_string(ejercitos[i].getCantidad()) + "-" + ejercitos[i].getTipo() + "-" + ejercitos[i].getColor();
            if(i < ejercitos.size() - 1){
                texto += "#";
            }
        }
        texto += "/";
        for(int i = 0; i < territorios.size(); i++){
            texto += territorios[i].getNombre() + "-" + to_string(territorios[i].getNumero());
            if(i < territorios.size() - 1){
                texto += "#";
            }
        }
        texto += "\n";
    }

    texto += "#\n";

    //DATOS DE LOS CONTINENTES/PAISES
    texto += "Continentes\n";
    for(Continente c : continentes){
        texto += to_string(c.getNumero()) + "/";
        vector <Pais> paises = c.getPaises();
        for(int i = 0; i < paises.size(); i++){
            texto += to_string(paises[i].getNumero()) + "-" + paises[i].getPropietario() + "-" + to_string(paises[i].getTropas());
            if(i < paises.size() - 1){
                texto += "#";
            }
        }
        texto += "\n";
    }

    texto += "#\nFIN";

    return texto;
}

queue <string> Partida::leerTxt(string fileName)
{
    string leer;
    ifstream file;
    queue <string> cola;
    file.open(fileName);
    if(!file)
        cout << endl << "'" << fileName << "'" << " no contiene información válida para inicializar el juego." << endl;
    else{
        this->continentes = leerContinentes();
        getline(file, leer);
        while(leer != "FIN"){
            if(leer == "Turnos"){
                getline(file, leer);
                while(leer != "#"){
                    cola.push(leer);
                    getline(file, leer);
                }
            }
            else if(leer == "Jugadores"){
                getline(file, leer);
                while(leer != "#"){
                    vector <string> cadenas = split(leer, '/');
                    Jugador j;
                    j.setNombre(cadenas[0]);
                    j.setColor(cadenas[1]);                 
                    if(cadenas[2] != ""){
                        vector <string> tarjetas = split(cadenas[2], '#');
                        vector <Tarjeta> listaTarjetas;
                        for(int i = 0; i < tarjetas.size(); i++){
                            vector <string> tarjeta = split(tarjetas[i], '-');
                            Tarjeta t;
                            t.setIdContinente(stoi(tarjeta[0]));
                            t.setIdPais(stoi(tarjeta[1]));
                            t.setEjercito(tarjeta[2]);
                            listaTarjetas.push_back(t);
                        }
                        j.setTarjetas(listaTarjetas);
                    }        
                    vector <string> ejercitos = split(cadenas[3], '#');
                    vector <Ejercito> listaEjercitos;
                    for(int i = 0; i < ejercitos.size(); i++){
                        vector <string> ejercito = split(ejercitos[i], '-');
                        Ejercito e;
                        e.setCantidad(stoi(ejercito[0]));
                        e.setTipo(ejercito[1]);
                        e.setColor(ejercito[2]);
                        listaEjercitos.push_back(e);
                    }
                    j.setEjercitos(listaEjercitos);
                    vector <string> territorios = split(cadenas[4], '#');
                    vector <Pais> paises;
                    for(int i = 0; i < territorios.size(); i++){
                        vector < string> territorio = split(territorios[i], '-');
                        Pais p;
                        p.setNombre(territorio[0]);
                        p.setNumero(stoi(territorio[1]));
                        p.setPropietario(cadenas[0]);
                        paises.push_back(p);
                    }
                    j.setTerritorios(paises);
                    this->jugadores.push_back(j);
                    getline(file, leer);
                }
            }
            else if(leer == "Continentes"){
                getline(file, leer);
                while(leer != "#"){
                    vector <string> cadenas = split(leer, '/');
                    int posC = stoi(cadenas[0]) - 1;
                    vector <string> paises = split(cadenas[1], '#');
                    for(int i = 0; i < paises.size(); i++){
                        vector <string> datos = split(paises[i], '-');
                        int posP = stoi(datos[0]) - 1;
                        this->continentes[posC].cambiarPropietario(posP, datos[1]);
                        this->continentes[posC].setTropas(posP, stoi(datos[2])); 
                    }
                    getline(file, leer);
                }
            }
            getline(file, leer);
        }
    }

    return cola;
}

void Partida::setJugadores(vector <Jugador> jugadores)
{
    this->jugadores = jugadores;
}

vector<string> split(string cadena, char separador)
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
