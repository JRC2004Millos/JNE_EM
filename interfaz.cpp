#include <iostream>
#include <string.h>
#include <fstream>
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"
#define MAGENTA "\033[35m"

using namespace std;

void ayuda();
bool inicializar(bool);
bool inicializarArchivo(bool,string);
void turno(bool,string);
void conquista_barata(bool);
void guardar(bool,string,fstream&);
void guardar_comprimido(bool,string,fstream&);
void costo_conquista(bool);
string getNombreArchivo(string);
int getId(string);

int main() {
  int seleccion;
  string comando, separado;
  bool inicializado = false;
  fstream txt, bin;
  do{
    cout<<endl<<"$";
    getline(cin,comando);
    
    if(comando=="inicializar"){
      inicializado = inicializar(inicializado);
    }
    else if(comando.find("inicializar")==0){
      inicializado = inicializarArchivo(inicializado,comando);    
    }
    else if(comando=="ayuda"){
      ayuda(); 
    }
    else if(comando=="conquista_mas_barata"){
      conquista_barata(inicializado);
    }  
    else if(comando.find("turno")==0){
      turno(inicializado, comando);
    }
    else if(comando.find("guardar")==0){
      guardar(inicializado, comando, txt);
    }
    else if(comando.find("guarda_comprimido")==0){
      guardar_comprimido(inicializado, comando, bin);
    }
    else if(comando=="costo_conquista"){
      costo_conquista(inicializado);
    }
    else if(comando=="salir"){
      return 0;
    }
    else{
      cout<<endl<<"Esta partida no ha sido inicializada correctamente."<<endl;
    }
  }while(comando != "salir");
}

void ayuda(){
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

bool inicializar(bool b){
  if(b){
    cout<<endl<<"El juego ya ha sido inicializado."<<endl;
  }
  else{
    b = true;
    cout<<endl<<"El juego se ha inicializado correctamente."<<endl;
  }
  return b;
}

bool inicializarArchivo(bool b, string s){
  if(b){
    cout<<endl<<"El juego ya ha sido inicializado."<<endl;
  }
  else{
    b = true;
    string nombreArchivo = getNombreArchivo(s);
    cout<<endl<<"'"<<nombreArchivo<<"'"<<" no contiene información válida para inicializar el juego."<<endl;
  }
  return b;
}

void turno(bool b, string s){
  if(b){
    int id = getId(s);
    cout<<endl<<"El turno del jugador " << id << " ha terminado."<<endl;
  }
  else{
    cout<<endl<<"Esta partida no ha sido inicializada correctamente."<<endl;

  }
}

void conquista_barata(bool juego){
  if(juego==false)
  {
    cout<<endl<<"El juego no ha sido inicializado correctamente"<<endl;
  }
  else{
    cout<<endl<<"Jugador no válido"<<endl;
  }
}

void costo_conquista(bool b){
  if(b){
    cout<<endl<<"Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar<n>unidades de ejército."<<endl;
  }
  else{
    cout<<endl<<"Esta partida no ha sido inicializada correctamente."<<endl;
  }
}

void guardar(bool b, string s, fstream& txt){
  if(b){
    string nombreArchivo = getNombreArchivo(s) + ".txt";
    txt.open(nombreArchivo, ios::out);
    if(!txt)
    {
      cout<<endl<<"La partida no ha sido guardada correctamente."<<endl;
    }
    else
    {
      cout<<endl<<"La partida ha sido guardada correctamente en '" << nombreArchivo << "'"<<endl;
    }
    txt.close();
  }
  else{
    cout<<endl<<"Esta partida no ha sido inicializada correctamente."<<endl;
  }
}

void guardar_comprimido(bool b, string s, fstream& bin){
  if(b){
    string nombreArchivo = getNombreArchivo(s) + ".dat";
    bin.open(nombreArchivo,ios::binary |ios::out);
    if(!bin)
    {
      cout<<endl<<"La partida no ha sido codificada ni guardada correctamente."<<endl;
    }
    else{
      cout<<endl<<"La partida ha sido codificada y guardada correctamente en '" << nombreArchivo << "'"<<endl;
      bin.close();      
    }    
  }
  else{
    cout<<endl<<"Esta partida no ha sido inicializada correctamente."<<endl;
  }  
}

int getId(string x){
  size_t pos = x.find(" ");
  string aux = x.substr(pos + 1);
  int id=stoi(aux);
  return id;
}

string getNombreArchivo(string x){
  size_t pos = x.find(" ");
  string aux = x.substr(pos + 1);
  return aux;
}