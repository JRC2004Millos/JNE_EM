#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include "Partida.h"

#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define GRAY    "\033[90m"
#define BOLD_MAGENTA "\033[1;35m"

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
int getId(string);

Partida * partida = new Partida();

int main()
{
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
        else
            cout<<endl<<"Se ingresó un comando erróneo."<<endl;
    }
    while(comando != "salir");
}

void ayuda()
{
    cout << endl << MAGENTA << " » CONFIGURACIÓN DEL JUEGO « " << endl;
    cout <<endl << BLUE << "--- inicializar --- \n" << WHITE << " ▻ Realiza las operaciones necesarias para inicializar el juego, de acuerdo a las instrucciones entregadas" << endl;
    cout <<endl << BLUE << "--- turno <id_jugador> --- \n" << WHITE << " ▻ Realiza las operaciones descritas dentro del turno de un jugador (obtener nuevas unidades, atacar y forticar)." << endl;
    cout << endl << MAGENTA << " » ALMACENAMIENTO DE PARTIDAS « " << endl;
    cout <<endl << BLUE << "--- salir --- \n" << WHITE<< " ▻ Termina la ejecución de la aplicación." << endl;
    cout <<endl << BLUE << "--- guardar <nombre_archivo> --- \n" << WHITE << " ▻ El estado actual del juego es guardado en un archivo de texto." << endl;
    cout <<endl << BLUE << "--- guardar_comprimido <nombre_archivo> --- \n" << WHITE << " ▻ El estado actual del juego es guardado en un archivo binario." << endl;
    cout <<endl << BLUE << "--- inicializar <nombre_archivo> --- \n" << WHITE << " ▻ Inicializa el juego con los datos contenidos en el archivo identicado por <nombre_archivo>." << endl;
    cout << endl << MAGENTA << " » ESTRATEGIAS DE JUEGO « " << endl;
    cout <<endl << BLUE << "--- costo_conquista <territorio> --- \n" << WHITE << " ▻ Se calcula el costo y la secuencia de territorios a ser conquistados para lograr controlar el territorio dado por el usuario. " << endl;
    cout <<endl << BLUE << "--- conquista_mas_barata --- \n" << WHITE << " ▻ De todos los territorios posibles, calcular aquel que pueda implicar un menor número de unidades de ejército perdidas" << endl;
}

bool inicializar(bool b)
{
    if(b)
        cout<<endl << CYAN <<"El juego ya ha sido inicializado."<< WHITE <<endl;
    else
    {
        b = true;
        leerJugadores();
        partida->asignarTerritorios();
        
        cout<<endl << CYAN <<"El juego se ha inicializado correctamente."<< WHITE << endl;
    }
    return b;
}

void leerJugadores(){
  string nombre, color;
        int cantJugadores = 0;
        list <string> * colores = new list<string> ();
        llenarColores(colores);
        do
        {
            cout<<endl<< CYAN <<"Ingrese la cantidad de jugadores (2-6): " << WHITE;
            cin>>cantJugadores;
            if(cantJugadores<2 || cantJugadores>6)
            {
                cout <<endl << BOLD_MAGENTA << "Ingresó un valor inválido, inténtelo de nuevo"<< WHITE << endl;
            }
        }
        while(cantJugadores<2 || cantJugadores>6);
        for(int i=0; i<cantJugadores; i++)
        {
            cout<< endl <<CYAN << "Ingrese el nombre o identificador del jugador "<< WHITE<<i+1<<": ";
            cin>>nombre;
            color = asignarColor(cantJugadores, colores);
            partida->agregarJugador(nombre,color);
        }
}

void llenarColores(list <string> *colores){
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
    cout << endl << CYAN << "Los colores disponibles son: " << WHITE <<endl;
    for(string color : *colores)
        cout << endl << color;
    do{
      cout << endl << CYAN << "\nEscoga el color: " << WHITE;
      cin >> col;
      for(string color : *colores){
        if(col == color)
          encontrado = true;
      }
      if(!encontrado)
        cout << endl << BOLD_MAGENTA<< "Ingresó un color erróneo, inténtelo de nuevo"<< WHITE;
    }while(!encontrado);
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
        cout<<endl<< BOLD_MAGENTA << "El juego ya ha sido inicializado."<<WHITE<< endl;
    }
    else
    {
        b = true;
        string nombreArchivo = getNombreArchivo(s);
        cout<<endl<< BOLD_MAGENTA<<"'"<<nombreArchivo<<"'"<<" no contiene información válida para inicializar el juego."<< WHITE<<endl;
    }
    return b;
}

void turno(bool b, string s)
{
  b=true;
    if(b)
    {
      int id = getId(s);
      if(partida->buscarJugador(s)=="error")
        cout<<endl<<"No existe este jugador"<<endl;
      else{
        partida->ubicarEjercito();
      }
        cout<<endl << CYAN <<"El turno del jugador " << id << " ha terminado."<< WHITE << endl;
    }
    else
    {
        cout<<endl << BOLD_MAGENTA <<"Esta partida no ha sido inicializada correctamente."<< WHITE << endl;

    }
  
    
}

void conquista_barata(bool juego)
{
    if(juego==false)
    {
        cout<<endl<< BOLD_MAGENTA <<"El juego no ha sido inicializado correctamente"<<WHITE << endl;
    }
    else
    {
        cout<<endl << BOLD_MAGENTA <<"Jugador no válido"<< WHITE << endl;
    }
}

void costo_conquista(bool b)
{
    if(b)
    {
        cout<<endl<< CYAN <<"Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar<n>unidades de ejército."<< WHITE << endl;
    }
    else
    {
        cout<<endl<< BOLD_MAGENTA <<"Esta partida no ha sido inicializada correctamente."<< WHITE << endl;
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
            cout<<endl<< BOLD_MAGENTA <<"La partida no ha sido guardada correctamente."<< WHITE << endl;
        }
        else
        {
            cout<<endl << CYAN <<"La partida ha sido guardada correctamente en '" << nombreArchivo << "'"<< WHITE << endl;
        }
        txt.close();
    }
    else
    {
        cout<<endl<< BOLD_MAGENTA <<"Esta partida no ha sido inicializada correctamente."<< WHITE << endl;
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
            cout<<endl<< BOLD_MAGENTA <<"La partida no ha sido codificada ni guardada correctamente."<< WHITE << endl;
        }
        else
        {
            cout<<endl<< CYAN <<"La partida ha sido codificada y guardada correctamente en '" << nombreArchivo << "'"<< WHITE << endl;
            bin.close();
        }
    }
    else
    {
        cout<<endl << BOLD_MAGENTA <<"Esta partida no ha sido inicializada correctamente."<< WHITE << endl;
    }
}

int getId(string x)
{
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    int id=stoi(aux);
    return id;
}

string getNombreArchivo(string x)
{
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    return aux;
}
