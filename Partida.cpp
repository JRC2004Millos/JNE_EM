#include "Partida.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

vector <string> separar(string,char);

Partida::Partida(){
  
}

void Partida::agregarJugador(string n, string c, int i){
  Jugador * j = new Jugador (n,c,i);
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

bool Partida::verificarContinentes(){
  int i = 0;
  for(Continente c : continentes){
    if(c.getContador() == c.getCantiPaises())
      i++;
  }
  if(i == continentes.size())
    return true;
  return false;
}

int Partida::pedirContinente(string nombre){
  int continente;
  do{
    mostrarContinentes();
    cout<<endl<<nombre<< ", digite el número del continente que desea escoger: ";
    cin>>continente;
    if(continente<1 || continente>6)
      cout<<endl<<"Ingresó un valor inválido, inténtelo de nuevo"<<endl;
  }while(continente<1 || continente>6);
  return continente;
}

int Partida::pedirPais(string nombre, Continente c){
  int pais;
  bool encontrado = false;
  do{
    c.mostrarPaises();
    cout<<endl<<nombre<< ", digite el número del país que desea escoger: ";
    cin>>pais;
    if(pais == 0)
      c = continentes[pedirContinente(nombre) - 1];
    else if(c.buscarPais(pais) == "error" || !c.paisOcupado(pais))
      cout<<endl<<"El país no fue encontrado o está ocupado, inténtelo de nuevo"<<endl;
    else
      encontrado = true;
  }while(!encontrado);
  return pais;
}

void Partida::escogerTerritorio(){
  int c, p;
  for(Jugador &j : jugadores){
    c = pedirContinente(j.getNombre()) - 1;
    p = pedirPais(j.getNombre(), continentes[c]);
    string territorio = continentes[c].buscarPais(p);        
    j.agregarTerritorio(territorio);
    continentes[c].marcarOcupado(p, j.getNombre());
  }
}

void Partida::asignarTerritorios(){
  cout << endl <<"¡Es hora de escoger sus territorios!" << endl;
  continentes = leerContinentes();
  while(!verificarContinentes()){    
    escogerTerritorio();
  }
  for(Jugador &j : jugadores){
    j.mostrarTerritorios();
  }
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
      cout <<  "No se pudo abrir el archivo." << endl;
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

int Partida::buscarJugador(string nombre){
  int i = 0;
  for(Jugador j : jugadores){
    if(nombre == j.getNombre())
      return i;
    i++;
  }
  return -1;
}

void Partida::ubicarEjercito(Jugador j){
    int nuevasTropas = 0;
    nuevasTropas = j.contarTerritorios()/3;
    nuevasTropas += tropasAdicionales(j.getNombre());
    j.setInfanteria(nuevasTropas);
}

int Partida::tropasAdicionales (string nombre){
  for(Continente c : continentes){
      string continente = c.verificarContinente(nombre);
      if(continente != "nada"){
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

void Partida::agregarTropasTerr(Jugador j){
  char seguir;
  int trop;
  string pais;
  
 do{
    j.ToTerritorios();
   cout << endl << "Dijite el nombre del pais al que le desea agregar tropas: ";
   cin >> pais;
   cout << endl << "Cuantas tropas desea agregar: ";
   cin >> trop;
  
    for(int i = 0;j.getTerritorios().size();i++){
       continentes[i].cambiarTropas(pais, trop);
     }
   cout << endl << "Desea agregar mas tropas: si = s, no = n" << endl;
   cin>>seguir;
       
   } while(j.getInfanteria() != 0 || seguir == 'n');
} 

void Partida:: atacar(){
  string pai;
  int at;
  
  cout << endl << "Desde que pais desea atacar:" << endl; 
  cin>> pai;
  cout << endl << "A que pais quiere atacar: "<< endl;
  //America del sur
  if (pai == "argentina"){
    cout << endl << "Puede atacar a 1. brasil o 2. peru" << endl;
    cin>>at;
  }
   if (pai == "peru"){
    cout << endl << "Puede atacar a 1. brasil o 2. argentina o 3. venezuela" << endl;
    cin >>at;
  }
   if (pai == "venezuela"){
    cout << endl << "Puede atacar a 1. brasil o 2. peru o 3. america central" << endl;
    cin >>at;
  }
   if (pai == "brazil"){
    cout << endl << "Puede atacar a 1. argentina o 2. peru o 3. venezuela o 4. africa oriental" << endl;
    cin>>at;
  }
  
  //America del norte
  if(pai == "alaska"){
    cout << endl << "Puede atacar a 1. alberta o 2. territorio oroccidental" <<endl;
    cin >>at;
  }
  if(pai == "territorio noroccidental"){
    cout << endl << "Puede atacar a 1. alaska o 2. alberta o 3. ontaro o 4. groenlandia" <<endl;
    cin >>at;
  }
if(pai == "alberta"){
    cout << endl << "Puede atacar a 1. territorio noroccidental  o  2. estados unidos occidentales o  3. ontaro  o  4. estados unidos orientales" <<endl;
    cin >>at;
  }
  if(pai == "estados unidos occidentales"){
    cout << endl << "Puede atacar a 1. ontaro  o  2. estados unidos orientales o  3. alberta" <<endl;
    cin >>at;
  }
  if(pai == "estados unidos occidentales"){
    cout << endl << "Puede atacar a 1. ontaro  o  2. estados unidos orientales o  3. alberta" <<endl;
    cin >>at;
  }
  if(pai == "estados unidos occidentales"){
    cout << endl << "Puede atacar a 1. estados unidos orientales  o  2. estados unidos occidentales o  3. venezuela" <<endl;
    cin >>at;
  }
  //Australia
  if(pai == "australia oriental"){
    cout << endl << "Puede atacar a 1. indonesia  o  2. nueva guinea o  3. australia occidental" <<endl;
    cin >>at;
  }
  if(pai == "australia occidental"){
    cout << endl << "Puede atacar a 1. indonesia  o  2. nueva guinea o  3. australia oriental" <<endl;
    cin >>at;
  }
  if(pai == "nueva guinea"){
    cout << endl << "Puede atacar a 1. australia oriental  o  2. indonesia o  3. australia occidental" <<endl;
    cin >>at;
  }
  if(pai == "indonesia"){
    cout << endl << "Puede atacar a 1. australia occidental  o  2. nueva guinea o  3. australia oriental" <<endl;
    cin >>at;
  }

  //Europa
  if(pai == "gran bretaña"){
    cout << endl << "Puede atacar a 1. islandia o 2. europa del norte o 3. escandinavia o 4. europa occidental" <<endl;
    cin >>at;
  }
  if(pai == "islandia"){
    cout << endl << "Puede atacar a 1. gran bretaña o 2. escandinavia o 3. groenlandia" <<endl;
    cin >>at;
  }
  if(pai == "europa del norte"){
    cout << endl << "Puede atacar a 1. gran bretaña o 2. europa occidental o 3. escandinavia o 4. europa del sur o 5. ucrania" <<endl;
    cin >>at;
  }
  if(pai == "escandinavia"){
    cout << endl << "Puede atacar a 1. gran bretaña o 2. islandia o 3. europa del norte o 4. ucrania" <<endl;
    cin >>at;
  }
  if(pai == "europa del sur"){
    cout << endl << "Puede atacar a 1. europa del norte o 2. ucrania o 3. europa occidental o 4. egipto o 5. africa del norte o 6. medio oriente" <<endl;
    cin >>at;
  }
  if(pai == "ucrania"){
    cout << endl << "Puede atacar a 1. europa del norte o 2. escandinavia o 3. europa del sur o 4. afghanistan o 5. medio oriente o 6. ural" <<endl;
    cin >>at;
  }
  if(pai == "europa occidental"){
    cout << endl << "Puede atacar a 1. gran bretaña o 2. europa del norte o 3. europa del sur o 4. africa del norte" <<endl;
    cin >>at;
  }

  //Asia
  if(pai == "afghanistan"){
    cout << endl << "Puede atacar a 1. ural  o 2. china  o 3. india  o 4. medio oriente o 5. ucrania" <<endl;
    cin >>at;
  }
if(pai == "china"){
    cout << endl << "Puede atacar a 1. mongolia o 2. siam o 3. india o 4. afghanistan o 5. ural o 6. siberia" <<endl;
    cin >>at;
  }
  if(pai == "india"){
    cout << endl << "Puede atacar a 1. china o 2. afghanistan o 3. medio oriente  o 4. siam" <<endl;
    cin >>at;
  }
  if(pai == "irkutsk"){
    cout << endl << "Puede atacar a 1. mongolia o 2. siberia  o 3. yakutsk  o 4. kamchatka" <<endl;
    cin >>at;
  }
  if(pai == "japon"){
    cout << endl << "Puede atacar a 1. siam o 2. mongolia" <<endl;
    cin >>at;
  }
  if(pai == "kamchatka"){
    cout << endl << "Puede atacar a 1. yakutsk o 2. irkutsk o 3. siam o 4. japon o 5. alaska" <<endl;
    cin >>at;
  }
  if(pai == "medio oriente"){
    cout << endl << "Puede atacar a 1. afghanistan o 2. india  o 3. ucrania  o 4. egipto" <<endl;
    cin >>at;
  }
  if(pai == "mongolia"){
    cout << endl << "Puede atacar a 1. china o 2. siberia o 3. irkutsk o 4. japon" <<endl;
    cin >>at;
  }
  if(pai == "siam"){
    cout << endl << "Puede atacar a 1. china o 2. india o 3. indonesia" <<endl;
    cin >>at;
  }
  if(pai == "siberia"){
    cout << endl << "Puede atacar a 1. ural o 2. china o 3. mongolia o 4. irkutsk 5. yakutsk" <<endl;
    cin >>at;
  }
  if(pai == "ural"){
    cout << endl << "Puede atacar a 1. ucrania o 2. afghanistan o 3. china o 4. siberia" <<endl;
    cin >>at;
  }
  if(pai == "yakutsk"){
    cout << endl << "Puede atacar a 1. irkutsk o 2. kamchatka o 3. siberia" <<endl;
    cin >>at;
  }
  
  
  //Africa
  if(pai == "congo"){
    cout << endl << "Puede atacar a 1. africa del norte o 2.  africa oriental o 3. africa del sur" <<endl;
    cin >>at;
  }
  if(pai == "africa oriental"){
    cout << endl << "Puede atacar a 1. congo o 2. egipto o 3. madagascar o 4. africa del sur" <<endl;
    cin >>at;
  }
  if(pai == "egipto"){
    cout << endl << "Puede atacar a 1. africa oriental o 2. africa del norte o 3. europa del sur o 4. medio oriente" <<endl;
    cin >>at;
  }  
  if(pai == "madagascar"){
    cout << endl << "Puede atacar a 1. africa orientalo 2. africa sur " <<endl;
    cin >>at;
  }
  if(pai == "africa del norte"){
    cout << endl << "Puede atacar a 1. brasil o 2. europa occidental o 3. europa del sur o 4. egipto o 5 congo" <<endl;
    cin >>at;
  }
  if(pai == "africa del sur"){
    cout << endl << "Puede atacar a 1. congo o 2. africa oriental o 3. madagascar" <<endl;
    cin >>at;
  }
}

void Partida::turno(int pos){
  ubicarEjercito(jugadores[pos]);
  agregarTropasTerr(jugadores[pos]);
}

int Partida::Dado(){
    srand(time(NULL));
    int min = 1, max = 6;
    int num = min + rand() % (max - min + 1);
    cout << num << endl;
    return num;
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
