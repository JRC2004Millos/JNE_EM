#include <iostream>
#include <locale>
#include <string.h>
#include <fstream>
#include <list>
#include <queue>
#include <map>

#include "ArbolHuffman.h"
#include "Partida.h"

using namespace std;

void comandos();
void ayuda();
bool inicializar(bool);
void leerJugadores();
bool inicializarArchivo(bool,string);
void turno(bool,string);
void conquista_barata(bool);
void guardar(bool,string,fstream&);
void guardar_comprimido(bool,string,fstream&);
void costo_conquista(bool);
void llenarColores(list<string>*);
string asignarColor(int, list<string> *);
string getNombreArchivo(string);
string getId(string);
int asignarInfanteria(int);
queue <Jugador> pedirColaJugadores();
vector <string> separar(string,char);
void leerTxt(string);
void leerBin(string);
void ConteoDeVariables(string);

int cantJugadores = 0;

queue <Jugador> colaJugadores;

Partida * partida = new Partida();

int main()
{
    setlocale(LC_ALL, "");
    comandos();
}

void comandos()
{
    int seleccion;
    string comando, separado;
    bool inicializado = false;
    fstream txt, bin;
    do
    {
        cout<<endl<<"$";
        getline(cin, comando, '\n');

        if(comando=="inicializar")
            inicializado = inicializar(inicializado);
        else if(comando.find("inicializar")==0)
            inicializado = inicializarArchivo(inicializado,comando);
        else if(comando=="ayuda")
            ayuda();
        else if(comando=="conquista_mas_barata")
            conquista_barata(inicializado);
        else if(comando.find("turno")==0)
            turno(inicializado, comando);
        else if(comando.find("guardar")==0)
            guardar(inicializado, comando, txt);
        else if(comando.find("guarda_comprimido")==0)
            guardar_comprimido(inicializado, comando, bin);
        else if(comando=="costo_conquista")
            costo_conquista(inicializado);
        else if(comando=="salir")
            cout<<endl<<"Cerrando el juego...";
        else if(comando=="" || comando=="\n")
            cout<<endl;
        else
            cout<<endl<<"Se ingresó un comando erróneo."<<endl;
    }
    while(comando != "salir");
}

void ayuda()
{
    cout << endl << " » CONFIGURACIÓN DEL JUEGO « " << endl;
    cout <<endl << "--- inicializar --- \n" << " ▻ Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas" << endl;
    cout <<endl << "--- turno <id_jugador> --- \n" << " ▻ Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y forticar)." << endl;
    cout << endl << " » ALMACENAMIENTO DE PARTIDAS « " << endl;
    cout <<endl << "--- salir --- \n" << " ▻ Termina la ejecución de la aplicación." << endl;
    cout <<endl << "--- guardar <nombre_archivo> --- \n" << " ▻ El estado actual del juego es guardado en un archivo de texto." << endl;
    cout <<endl << "--- guardar_comprimido <nombre_archivo> --- \n" << " ▻ El estado actual del juego es guardado en un archivo binario." << endl;
    cout <<endl << "--- inicializar <nombre_archivo> --- \n" << " ▻ Inicializa el juego con los datos contenidos en el archivo identicado por <nombre_archivo>." << endl;
    cout << endl << " » ESTRATEGIAS DE JUEGO « " << endl;
    cout <<endl << "--- costo_conquista <territorio> --- \n" << " ▻ Se calcula el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario. " << endl;
    cout <<endl << "--- conquista_mas_barata --- \n" << " ▻ De todos los territorios posibles, calcular aquel que pueda implicar un menor número de unidades de ejército perdidas" << endl;
}

bool inicializar(bool b)
{
    if(b)
        cout<<endl << "El juego ya ha sido inicializado."<< endl;
    else
    {
        b = true;
        leerJugadores();
        partida->asignarTerritorios();
        cout<<endl << "El juego se ha inicializado correctamente."<< endl;
        colaJugadores = pedirColaJugadores();
    }
    return b;
}

void leerJugadores()
{
    string nombre, color;
    list <string> * colores = new list<string> ();
    llenarColores(colores);
    do
    {
        cout<<endl<< "Ingrese la cantidad de jugadores (3-6): ";
        cin>>cantJugadores;
        if(cantJugadores<3 || cantJugadores>6)
        {
            cout <<endl << "Ingresó un valor inválido, inténtelo de nuevo"<< endl;
        }
    }
    while(cantJugadores<3 || cantJugadores>6);
    for(int i=0; i<cantJugadores; i++)
    {
        cout<< endl << "Ingrese el nombre o identificador del jugador "<< i+1<<": ";
        cin>>nombre;
        color = asignarColor(cantJugadores, colores);
        int tropas = asignarInfanteria(cantJugadores);
        cout<<endl<<"TROPAS PARA ESTE JUEGO: "<<tropas<<endl;
        partida -> agregarJugador(nombre, color, tropas);
    }
}

int asignarInfanteria(int cantJugadores)
{
    if(cantJugadores == 3)
        return 35;

    else if(cantJugadores == 4)
        return 30;

    else if(cantJugadores == 5)
        return 25;

    else if(cantJugadores == 6)
        return 20;
    else
        return 0;
}

void llenarColores(list <string> *colores)
{
    colores->push_back("amarillo");
    colores->push_back("azul");
    colores->push_back("rojo");
    colores->push_back("verde");
    colores->push_back("gris");
    colores->push_back("negro");
}

string asignarColor(int cantJug, list<string> * colores)
{
    string col;
    bool encontrado = false;
    cout << endl << "Los colores disponibles son: " <<endl;
    for(string color : *colores)
        cout << endl << color;
    do
    {
        cout << endl << "\nEscoga el color: ";
        cin >> col;
        for(string color : *colores)
        {
            if(col == color)
                encontrado = true;
        }
        if(!encontrado)
            cout << endl << "Ingresó un color erróneo, inténtelo de nuevo";
    }
    while(!encontrado);
    auto it = colores->begin();
    while (it != colores->end())
    {
        if (*it == col)
        {
            it = colores->erase(it); // Elimina el color de la lista
            return col; // Retorna el color elegido
        }
        else
            ++it;
    }
    return col;
}

bool inicializarArchivo(bool b, string s)
{
    if(b)
    {
        cout<<endl<< "El juego ya ha sido inicializado."<<endl;
    }
    else
    {
        b = true;
        string nombreArchivo = getNombreArchivo(s);
        vector <string> archivo = separar(nombreArchivo, '.');
        if(archivo[1] == "txt")
            leerTxt(nombreArchivo);
        else if(archivo[1] == "bin" || archivo[1] == "dat")
            leerBin(nombreArchivo);

        cout<<endl<< "'"<<nombreArchivo<<"'"<<" no contiene información válida para inicializar el juego."<< endl;
    }
    return b;
}

void leerTxt(string fileName)
{
    string leer;
    ifstream file;
    file.open(fileName);
    if(!file)
        cout << endl << "'" << fileName << "'" << " no contiene información válida para inicializar el juego." << endl;
    else{
        getline(file, leer);
        while(leer != "FIN"){
            if(leer != "#"){
                vector <string> cadenas = separar(leer, '/');
                Jugador j;
                j.setNombre(cadenas[0]);
                j.setColor(cadenas[1]);
                vector <string> tarjetas = separar(cadenas[2], '#');
                vector <Tarjeta> listaTarjetas;
                for(int i = 0; i < tarjetas.size(); i++){
                    vector <string> tarjeta = separar(tarjetas[i], '-');
                    Tarjeta t;
                    t.setIdContinente(stoi(tarjeta[0]));
                    t.setIdPais(stoi(tarjeta[1]));
                    t.setEjercito(tarjeta[2]);
                    listaTarjetas.push_back(t);
                }
                j.setTarjetas(listaTarjetas);
                vector <string> ejercitos = separar(cadenas[3], '#');
                vector <Ejercito> listaEjercitos;
                for(int i = 0; i < ejercitos.size(); i++){
                    vector <string> ejercito = separar(ejercitos[i], '-');
                    Ejercito e;
                    e.setCantidad(stoi(ejercito[0]));
                    e.setTipo(ejercito[1]);
                    e.setColor(ejercito[2]);
                    listaEjercitos.push_back(e);
                }
                j.setEjercitos(listaEjercitos);
                vector <string> territorios = separar(cadenas[4], '#');
                j.setTerritorios(territorios);
            }
            getline(file, leer);
        }
    }
}

void leerBin(string fileName){

}

queue <Jugador> pedirColaJugadores()
{
    queue <Jugador> cola;
    vector <Jugador> jugadores = partida->getJugadores();
    for(Jugador j : jugadores)
        cola.push(j);
    return cola;
}

void turno(bool b, string s)
{
    if(b)
    {
        string id = getId(s);
        int pos = partida->buscarJugador(id);
        Jugador proxJugador = colaJugadores.front();

        if(pos < 0)
            cout<<endl<<"No existe este jugador"<<endl;
        else if(proxJugador.getNombre() != id)
            cout<<endl<<"No es el turno de este jugador"<<endl;
        else
        {
            partida->turno(pos);
            colaJugadores.pop();
            colaJugadores.push(proxJugador);
        }
        cout<<endl << "El turno del jugador " << id << " ha terminado."<< endl;
    }
    else
        cout<<endl << "Esta partida no ha sido inicializada correctamente." << endl;
}

void conquista_barata(bool juego)
{
    if(juego==false)
        cout<<endl<< "El juego no ha sido inicializado correctamente" << endl;
    else
        cout<<endl << "Jugador no válido"<< endl;
}

void costo_conquista(bool b)
{
    if(b)
    {
        cout<<endl<< "Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar<n>unidades de ejército."<< endl;
    }
    else
    {
        cout<<endl<< "Esta partida no ha sido inicializada correctamente."<< endl;
    }
}

void guardar(bool b, string s, fstream& txt)
{
    if(b)
    {
        string nombreArchivo = getNombreArchivo(s) + ".txt";
        txt.open(nombreArchivo, ios::out);
        if(!txt)
        {
            cout<<endl<< "La partida no ha sido guardada correctamente." << endl;
        }
        else
        {
            txt << partida->archivoTexto();
            cout<<endl <<"La partida ha sido guardada correctamente en '" << nombreArchivo << "'"<< endl;
        }
        txt.close();
    }
    else
    {
        cout<<endl<<"Esta partida no ha sido inicializada correctamente."<< endl;
    }
}

void guardar_comprimido(bool b, string s, fstream& bin)
{
    if(b)
    {
        string nombreArchivo = getNombreArchivo(s) + ".dat";
        bin.open(nombreArchivo,ios::binary |ios::out);
        if(!bin)
        {
            cout<<endl<<"La partida no ha sido codificada ni guardada correctamente."<<endl;
        }
        else
        {
            


            cout<<endl<<"La partida ha sido codificada y guardada correctamente en '" << nombreArchivo << "'"<< endl;
            bin.close();
        }
    }
    else
    {
        cout<<endl<<"Esta partida no ha sido inicializada correctamente."<<endl;
    }
}

string getId(string x)
{
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    string id = aux;
    return id;
}

string getNombreArchivo(string x)
{
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    return aux;
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

void ConteoDeVariables(string Archivo){

   ifstream file(Archivo);

    if (!file) {
        cout << "No se pudo abrir el archivo: " << Archivo << endl;
        exit;
    }

    map<char, int> charCount;
    char character;

    while (file.get(character)) {
        charCount[character]++;
    }

    file.close();
    //ArbolHuffman <char> arbol = ArbolHuffman <char>();
    for (const auto& pair : charCount) {
        char character = pair.first;
        int count = pair.second;
        //arbol.insertar(character,count);

        if (count > 1)
        { // Solo mostrar caracteres que se repiten más de una vez
            cout << "'" << character << "': " << count << " veces" << endl;
        }
  }
}