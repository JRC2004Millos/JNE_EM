#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <string>

#include "ArbolHuffman.h"
#include "Partida.h"
#include "Juego.h"

using namespace std;

Juego::Juego(){}

void Juego::comandos()
{
    int seleccion;
    string comando, separado;
    bool inicializado = false;
    fstream txt;
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
        else if(comando.find("guardar_comprimido")==0)
            guardar_comprimido(inicializado, comando);
        else if(comando.find("guarda")==0)
            guardar(inicializado, comando, txt);
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

void Juego::ayuda()
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

bool Juego::inicializar(bool b)
{
    if(b)
        cout<<endl << "El juego ya ha sido inicializado."<< endl;
    else
    {
        b = true;
        leerJugadores();
        partida.asignarTerritorios();
        cout<<endl << "El juego se ha inicializado correctamente."<< endl;
        colaJugadores = pedirColaJugadores();
    }
    return b;
}

void Juego::leerJugadores()
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
        partida.agregarJugador(nombre, color, tropas);
    }
}

int Juego::asignarInfanteria(int cantJugadores)
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

void Juego::llenarColores(list <string> *colores)
{
    colores->push_back("amarillo");
    colores->push_back("azul");
    colores->push_back("rojo");
    colores->push_back("verde");
    colores->push_back("gris");
    colores->push_back("negro");
}

string Juego::asignarColor(int cantJug, list<string> * colores)
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

bool Juego::inicializarArchivo(bool b, string s)
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
        if(archivo[1] == "txt"){
            colaJugadores = partida.leerTxt(nombreArchivo);
            cout << endl << "El siguiente turno es para " << colaJugadores.front() << endl;
        }
        else if(archivo[1] == "bin")
            leerBin(nombreArchivo);
    }
    return b;
}

void Juego::leerTxt(string fileName)
{
    colaJugadores = partida.leerTxt(fileName);
}

void Juego::leerBin(string fileName)
{
    vector <string> archivo = separar(fileName, '.');
    string mapFile = "mapa" + archivo[0] + ".txt";
    ifstream archivoLectura(mapFile);
    
    if(archivoLectura.is_open()){
        unordered_map<char, int> mapaLeido;
        string leer;
        getline(archivoLectura, leer);
        while(!archivoLectura.eof()){   
            vector <string> cadenas = separar(leer, '&');
            char* punteroChar = new char[cadenas[0].size() + 1]; 
            strcpy(punteroChar, cadenas[0].c_str());
            char caracter = *punteroChar;
            int frecuencia = stoi(cadenas[1]);
            if(caracter == '|')
                mapaLeido['\n'] = frecuencia;
            else
                mapaLeido[caracter] = frecuencia;
            getline(archivoLectura, leer);
        }   
        archivoLectura.close();

        ArbolHuffman arbol;
        NodoHuffman* raiz = arbol.construirArbol(mapaLeido);

        ifstream file(fileName, ios::binary);
        string linea;

        if(file.is_open()){
            while(getline(file, linea)){
                cout << arbol.decodificarMensaje(raiz, linea);
            }
            file.close();
        }
        else
            cout << endl << fileName << " no contiene información válida para inicializar el juego." << endl;
        //En este punto, suponiendo que el archivo se lee bien, se debe llamar a la función
        //partida.leerTxt(fileName);
        //así, se leen los datos de la partida decodificada al igual que con la de txt
    }
    else
        cout << endl << mapFile << " no contiene información válida para inicializar el juego." << endl;
}

queue <string> Juego::pedirColaJugadores()
{
    queue <string> cola;
    vector <Jugador> jugadores = partida.getJugadores();
    for(Jugador j : jugadores)
        cola.push(j.getNombre());
    return cola;
}

void Juego::turno(bool b, string s)
{
    if(b)
    {
        string id = getId(s);
        int pos = partida.buscarJugador(id);
        string proxJugador = colaJugadores.front();

        if(pos < 0)
            cout<<endl<<"No existe este jugador"<<endl;
        else if(proxJugador != id)
            cout<<endl<<"No es el turno de este jugador"<<endl;
        else
        {
            partida.turno(pos);
            colaJugadores.pop();
            colaJugadores.push(proxJugador);
        }
        cout<<endl << "El turno del jugador " << id << " ha terminado."<< endl;
    }
    else
        cout<<endl << "Esta partida no ha sido inicializada correctamente." << endl;
}

void Juego::conquista_barata(bool juego)
{
    if(juego==false)
        cout<<endl<< "El juego no ha sido inicializado correctamente" << endl;
    else
        cout<<endl << "Jugador no válido"<< endl;
}

void Juego::costo_conquista(bool b)
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

void Juego::guardar(bool b, string s, fstream& txt)
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
            queue <string> colaAux = colaJugadores;
            txt << "Turnos" << endl;
            while(!colaJugadores.empty()){
                txt << colaJugadores.front() << endl;
                colaJugadores.pop();
            }
            txt << "#" << endl;
            colaJugadores = colaAux;
            txt << partida.archivoTexto();
            cout<<endl <<"La partida ha sido guardada correctamente."<< endl;
        }
        txt.close();
    }
    else
    {
        cout<<endl<<"Esta partida no ha sido inicializada correctamente."<< endl;
    }
}

bool Juego::guardar_comprimido(bool b, string s)
{
    if(b)
    {
        string nombreArchivo = getNombreArchivo(s);

        string leer = nombreArchivo + ".txt";

        nombreArchivo += ".bin";

        unordered_map<char, int> mapaFrecuencia;

        fstream txt;

        guardar(b, s, txt);

        ifstream archivo(leer);
        if (!archivo.is_open()) {
            cerr << "La partida no ha sido codificada ni guardada correctamente." << endl;
            return false;
        }

        string mapFile = "mapa" + leer;
        ofstream mapTxt(mapFile);

        if(mapTxt.is_open()){
            char caracter;
            while (archivo.get(caracter)) {
                if (mapaFrecuencia.find(caracter) != mapaFrecuencia.end())
                    mapaFrecuencia[caracter]++;              
                else 
                    mapaFrecuencia[caracter] = 1;
            }
            for (const auto &par : mapaFrecuencia) {
                char clave = par.first;
                int valor = par.second;
                if(clave == '\n')
                    mapTxt << "|" << "&" << valor << endl;
                else
                    mapTxt << clave << "&" << valor << endl;
            }

        }
        else{
            cout << endl << "La partida no ha sido codificada ni guardada correctamente." << endl;
            return false;
        }
        mapTxt.close();     
        archivo.close();

        ArbolHuffman arbolHuffman;
        NodoHuffman* raiz = arbolHuffman.construirArbol(mapaFrecuencia);

        //vector <NodoHuffman*> nodos = arbolHuffman.obtenerNodosDelArbol(raiz);

        ofstream Binarchivo(nombreArchivo, ios::binary | ios::out);

        // Leer el mensaje desde un archivo
        archivo.open(leer);
        if (!archivo.is_open()) {
            cerr << "La partida no ha sido codificada ni guardada correctamente." << endl;
            return false;
        }

        string mensaje, mensajecodificado, mensajeFinal = "";
        while(!archivo.eof()){
            getline(archivo, mensaje);

            mensajecodificado = arbolHuffman.codificarMensaje(raiz, mensaje);
            mensajeFinal += mensajecodificado + "\n";

            cout << endl << arbolHuffman.decodificarMensaje(raiz, mensajecodificado);
        }
        archivo.close();

        if (Binarchivo.is_open()) {
            Binarchivo.write(mensajeFinal.c_str(), mensajeFinal.size());
            cout << "La partida ha sido codificada y guardada correctamente." << endl;
            return true;
        } else
            cerr << "La partida no ha sido codificada ni guardada correctamente." << endl;
        Binarchivo.close();
        return false;
    }
    else
        cout<<endl<<"Esta partida no ha sido inicializada correctamente."<<endl;
        return false;
    
    /*if(b)
    {
        string nombreArchivo = getNombreArchivo(s);

        string leer = nombreArchivo + ".txt";

        nombreArchivo += ".bin";

        unordered_map<char, int> mapaFrecuencia;

        fstream txt;

        guardar(b, s, txt);

        ifstream archivo(leer);
        if (!archivo.is_open()) {
            cerr << "La partida no ha sido codificada ni guardada correctamente." << endl;
            return false;
        }    
        else{
            char caracter;
            while (archivo.get(caracter)) {
                if (mapaFrecuencia.find(caracter) != mapaFrecuencia.end())
                    mapaFrecuencia[caracter]++;              
                else 
                    mapaFrecuencia[caracter] = 1;
            }
        }   
        archivo.close();

        ArbolHuffman arbolHuffman;
        NodoHuffman* raiz = arbolHuffman.construirArbol(mapaFrecuencia);

        ofstream Binarchivo(nombreArchivo, ios::binary | ios::out);

        if (Binarchivo.is_open()) {
            short n = mapaFrecuencia.size();
            Binarchivo.write(reinterpret_cast<char*>(&n), sizeof(n));

            for(const auto& par : mapaFrecuencia){
                char ci = par.first;
                Binarchivo.put(static_cast<unsigned char>(ci));

                long long fi = par.second;
                Binarchivo.write(reinterpret_cast<char*>(&fi), sizeof(fi));
            }

            long long w = raiz->frecuencia;
            Binarchivo.write(reinterpret_cast<char*>(&w), sizeof(w));

            // Leer el mensaje desde un archivo
            archivo.open(leer);
            if (!archivo.is_open()) {
                cerr << "La partida no ha sido codificada ni guardada correctamente." << endl;
                return false;
            }

            string mensaje, mensajecodificado, mensajeFinal = "";
            while(!archivo.eof()){
                getline(archivo, mensaje);

                mensajecodificado = arbolHuffman.codificarMensaje(raiz, mensaje);
                mensajeFinal += mensajecodificado + "\n";

                arbolHuffman.decodificarMensaje(raiz, mensajecodificado);
            }
            Binarchivo.write(mensajeFinal.c_str(), mensajeFinal.size());
            string decodificado = arbolHuffman.decodificarMensaje(raiz, mensajeFinal);
            cout << endl << decodificado << endl;
            archivo.close();
            
            cout << "La partida ha sido codificada y guardada correctamente." << endl;
            return true;
        } else
            cerr << "La partida no ha sido codificada ni guardada correctamente." << endl;
        Binarchivo.close();
        return false;
    }
    else
        cout<<endl<<"Esta partida no ha sido inicializada correctamente."<<endl;
        return false;
*/}

bitset<8> Juego::stringToBitset(string binaryString) {
    // Asegurarse de que la cadena sea múltiplo de 8 agregando ceros si es necesario.
    string paddedString = binaryString;
    while (paddedString.length() % 8 != 0) {
        paddedString = "0" + paddedString;
    }

    vector<bitset<8>> bitSegments;
    for (size_t i = 0; i < paddedString.length(); i += 8) {
        string segment = paddedString.substr(i, 8);
        bitSegments.push_back(bitset<8>(segment));
        cout << "Segmento " << i / 8 + 1 << ": " << bitSegments.back() << endl;
    }

    bitset<8> result(0);
    for (const auto& segment : bitSegments) {
        result <<= 8;
        result |= segment;
    }

    return result;
}

string Juego::quitarEspacios(string cadena) {
    vector<string>separacion = separar(cadena, ' ');
    string resultado = "";
    for(int i = 0; i < separacion.size(); i++)
        resultado += separacion[i];
    return resultado;
}

string Juego::getId(string x)
{
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    string id = aux;
    return id;
}

string Juego::getNombreArchivo(string x)
{
    size_t pos = x.find(" ");
    string aux = x.substr(pos + 1);
    return aux;
}

vector<string> Juego::separar(string cadena, char separador)
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