#include "Partida.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#define BOLD_MAGENTA "\033[1;35m"
#define WHITE   "\033[37m"
#define CYAN        "\033[36m"

using namespace std;

vector <string> separar(string,char);

Partida::Partida(){
  
}

void Partida::agregarJugador(string n, string c){
  Jugador * j = new Jugador (n,c);
  this->jugadores.push_back(*j);
}

void Partida::getJugadores(){
  for(Jugador j : jugadores){
    cout<<endl<<j.getNombre();
  }
}

void Partida::setContinentes(vector<Continente>c){
  this->continentes = c;
}

void Partida::asignarTerritorios(){
  cout << endl << CYAN <<"¡Es hora de escoger sus territorios!" << WHITE << endl;
  continentes = leerContinentes();
  int continente, pais;
  bool encontrado;
  while(!continentes.empty()){
    encontrado = false;
    for(Jugador j : jugadores){
      do{
        do{
          mostrarContinentes();
          cout<<endl<<j.getNombre()<< CYAN << ", escoja un continente: " << WHITE;
          cin>>continente;
          if(continente<1 || continente>6)
            cout<<endl<< BOLD_MAGENTA <<"El continente que ingresó no está disponible, inténtelo de nuevo"<< WHITE << endl;
        }while(continente<1 || continente>6);
        for(Continente c : continentes){
          if(continente == c.getNumero()){
            c.mostrarPaises();
            cout<<endl<<j.getNombre()<< CYAN << ", escoja un país: " << WHITE;
            cin>>pais;
            if(c.buscarPais(pais) != "error"){
              encontrado = true;
              j.agregarTerritorio(c.buscarPais(pais));
              vector<Pais> paises = c.borrarPais(pais);
              c.setPaises(paises);
            }
          }
        }
        if(!encontrado)
          cout<<endl<< BOLD_MAGENTA <<"El país que ingresó no está disponible, inténtelo de nuevo"<< WHITE << endl;
      }while(!encontrado);
    }
  }
  //continentes = leerContinentes();
}

Continente Partida::buscarContinente(int n){
  for(Continente c : continentes){
    if(n == c.getNumero())
      return c;
  }
  Continente * c = new Continente ();
  return *c;
}

vector<Continente> Partida::leerContinentes(){
  fstream archivo;
  string leer, token;
  vector<string> cadenas;
  vector <Continente> lista;
  int i = 0;
  archivo.open("territorios.txt");
  if (!archivo)
      cout << BOLD_MAGENTA <<  "No se pudo abrir el archivo." << WHITE << endl;
  else{
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

void Partida::mostrarContinentes(){
  for(Continente c : continentes){
    cout<<endl<<c.getNumero()<<". "<<c.getNombre()<<endl;
  }
}

vector<string> separar(string cadena, char separador){
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

string Partida::buscarJugador(string nombre){
  for(Jugador j : jugadores){
    if(nombre == j.getNombre())
      return nombre;
  }
  return "error";
}

void Partida::ubicarEjercito(){
  for(Jugador j : jugadores){
    int nuevasTropas = 0;
    nuevasTropas = j.contarTerritorios()/3;
  }
}