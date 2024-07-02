#include <iostream>
#include <fstream>
#include <cstdlib>
#include "json.hpp"


using json = nlohmann::json;
using namespace std;

#include "./cabeceras/arbolBinario.h"
#include "./cabeceras/listaCircularDoble.h"
#include "./cabeceras/arbolB.h"
#include "./cabeceras/TablaHash.h"
#include "./cabeceras/GrafoDirigido.h"
#include "./cabeceras/matrizDispersa.h"

arbolBinario aBinario;
circularDoble cirDoble;
BTree arbolB(3);
TablaHash tHash(18);
GrafoDirigido grafo(100);
MatrizDispersa matriz;

void cargaMatriz(){
    ifstream inputFile("./entradas/aviones.json");
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo!" << endl;
        return;
    }

    json j;
    inputFile >> j;

    for (const auto& item : j) {
        string vuelo= item["vuelo"];
        string ciudadDestino = item["ciudad_destino"];

        ifstream inputFile2("./entradas/pilotos.json");

        if (!inputFile2.is_open()) {
            cerr << "No se pudo abrir el archivo!" << endl;
            return;
        }

        json k;
        inputFile2 >> k;

        for (const auto& item : k) {
            
            string nId = item["numero_de_id"];
            string vuelo2 = item["vuelo"];
        if(vuelo==vuelo2){
            matriz.insert(vuelo,ciudadDestino,nId);
        }
     }
        inputFile2.close();

    }
    
    cout<<"Matriz llena con exito."<<endl;
    inputFile.close();
}

char** split(const string &str, char delimiter, int &numTokens) {
    // Contar el número de tokens
    numTokens = 1;
    for (char ch : str) {
        if (ch == delimiter) {
            numTokens++;
        }
    }

    // Reservar memoria para el arreglo de punteros
    char** tokens = new char*[numTokens];
    
    size_t start = 0;
    size_t end = str.find(delimiter);
    int index = 0;

    while (end != string::npos) {
        string token = str.substr(start, end - start);
        tokens[index] = new char[token.size() + 1]; // Reservar memoria para cada token
        strcpy(tokens[index], token.c_str()); // Copiar el token al arreglo
        index++;
        start = end + 1;
        end = str.find(delimiter, start);
    }

    // Copiar el último segmento
    string token = str.substr(start);
    tokens[index] = new char[token.size() + 1];
    strcpy(tokens[index], token.c_str());

    return tokens;
}

void cAviones(){
    cout<<"*******************Carga de aviones*******************"<<endl;

    ifstream inputFile("./entradas/aviones.json");
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo!" << endl;
        return;
    }

    json j;
    inputFile >> j;

    for (const auto& item : j) {
        string vuelo= item["vuelo"];
        string nRegistro = item["numero_de_registro"];
        string modelo = item["modelo"];
        int capacidad = item["capacidad"];
        string aerolinea = item["aerolinea"];
        string ciudadDestino = item["ciudad_destino"];
        string estado = item["estado"];

        if(item["estado"]=="Disponible"){
            arbolB.insert(nRegistro);
        }else if(item["estado"]=="Mantenimiento"){
            cirDoble.insert(vuelo,nRegistro,modelo,capacidad,aerolinea,ciudadDestino,estado);
        }else{
            cout<<"El estado no es valido"<<endl;
        }
        grafo.agregarVertice(ciudadDestino);
    }
    
    cout<<"Carga de Aviones realizada con exito"<<endl;
    inputFile.close();

    cargaMatriz();
    return;
}

void cPilotos(){
    cout<<"*******************Carga de pilotos*******************"<<endl;
    ifstream inputFile("./entradas/pilotos.json");
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo!" << endl;
        return;
    }

    json j;
    inputFile >> j;

    for (const auto& item : j) {
        string nombre= item["nombre"];
        string nacionalidad = item["nacionalidad"];
        string nId = item["numero_de_id"];
        string vuelo = item["vuelo"];
        int hVuelo = item["horas_de_vuelo"];
        string tLicencia = item["tipo_de_licencia"];

        aBinario.insert(nombre,nacionalidad,nId,vuelo,hVuelo,tLicencia);
        tHash.Insertar(nombre,nacionalidad,nId,vuelo,hVuelo,tLicencia);
        //cout<<nId<<endl;
    }
    
    cout<<"Carga de Pilotos realizada con exito"<<endl;
    inputFile.close();
    return; 
}

void cRutas(){
    cout<<"*******************Carga de rutas*******************"<<endl;
    ifstream inputFile("./entradas/rutas.txt");
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo!" << endl;
        return;
    }

    string linea;
    while (getline(inputFile, linea)) { // Leer línea por línea
        linea.pop_back();
        int nt=0;
        char** resultado = split(linea, '/', nt);
        
        int peso = atoi(resultado[2]);
        grafo.agregarArista(resultado[0],resultado[1],peso);
    }

    inputFile.close();
    cout<<"Carga de rutas realizada con exito"<<endl;
    return;
}

void cMovimientos(){
    cout<<"*******************Carga de movimientos*******************"<<endl;
    ifstream inputFile("./entradas/movimientos.txt");
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo!" << endl;
        return;
    }
    string linea;
    while (getline(inputFile, linea)) {
        if (linea.find("MantenimientoAviones,Ingreso,") != string::npos) {
            // Encontrar la posición del número de avión
            size_t pos = linea.find_last_of(',') + 1;
            string avion = linea.substr(pos, linea.length() - pos - 1);

            cirDoble.insert(avion);
            cout<<"Ingreso de "<<avion<<" a lista de mantenimiento"<<endl;
            arbolB.remove(avion);
            cout<<"Egreso de "<<avion<<" de arbol de disponibles"<<endl;

        } else if (linea.find("MantenimientoAviones,Salida,") != string::npos) {
            // Encontrar la posición del número de avión
            size_t pos = linea.find_last_of(',') + 1;
            string avion = linea.substr(pos, linea.length() - pos - 1);

            arbolB.insert(avion);
            cout<<"Ingreso de "<<avion<<" a arbol de disponibles"<<endl;
            cirDoble.remove(avion);
            cout<<"Egreso de "<<avion<<" de lista de mantenimiento"<<endl;

        } else if (linea.find("DarDeBaja(") != string::npos) {
            // Encontrar la posición del número de avión
            size_t pos1 = linea.find('(') + 1;
            size_t pos2 = linea.find(')');
            string piloto = linea.substr(pos1, pos2 - pos1);

            //cout<<piloto<<endl;
            Nodo * eliminado = tHash.eliminar(piloto);
            if(eliminado){
                cout<<"eliminado "<<piloto<<" de tabla Hash"<<endl;
                aBinario.remove(eliminado->hVuelo);
                cout<<"eliminado "<<piloto<<" de arbol binario"<<endl;
                matriz.remove(eliminado->vuelo,eliminado->getDato());
                cout<<"eliminado "<<piloto<<" de matriz dispersa"<<endl;
            }else{
                cout<<"No se encontro el registro para "<<piloto<<endl;
            }
            
        }
    }

    //cout<<"Carga de movimientos realizada con exito"<<endl;
    inputFile.close();
    return;
}

void consultaHVuelo(){
    int opcion;
    cout<<"*******************Consulta horas de vuelo*******************"<<endl;
    cout<<"Ingrese una opcion:"<<endl;
    cout<<"1. Preorden"<<endl;
    cout<<"2. Inorden"<<endl;
    cout<<"3. Posorden"<<endl;
    cin>>opcion;

    switch (opcion)
    {
    case 1:
        cout<<"---------------------------------------------------------------"<<endl;
        cout<<"PreOrden: "<<endl;
        aBinario.preOrder(aBinario.getRoot());
        cout<<endl;
        cout<<"---------------------------------------------------------------"<<endl;
        break;
    case 2:
        cout<<"---------------------------------------------------------------"<<endl;
        cout<<"InOrden: "<<endl;
        aBinario.inOrder(aBinario.getRoot());
        cout<<endl;
        cout<<"---------------------------------------------------------------"<<endl;
        break;
    case 3:
        //cout<<"*******************Consulta horas de vuelo*******************"<<endl;
        cout<<"---------------------------------------------------------------"<<endl;
        cout<<"PosOrden: "<<endl;
        aBinario.posOrder(aBinario.getRoot());
        cout<<endl;
        cout<<"---------------------------------------------------------------"<<endl;
        break;
    default:
        cout<<"Opcion invalida"<<endl;
        break;
    }
    return;
}

void recomendarRuta(){
    string origen,destino;
    cout<<"*******************Recomendar ruta*******************"<<endl;
    cout<<"Ingrese el origen: ";
    cin>>origen;
    cout<<"\n Ingrese el destino: ";
    cin>>destino;
    grafo.mostrarRutaMasCorta(origen,destino);
    return;
}

void reportes(){
    cout<<"*******************Visualizar reportes*******************"<<endl;
    aBinario.generateDotFile("dot/horasVuelo.dot");
    cout<<"Reporte horas de vuelo creado."<<endl;

    tHash.generaReporte("dot/tablaPilotos.dot");
    cout<<"Reporte tabla de pilotos creado."<<endl;

    grafo.generarDot("dot/RutasDeVuelo.dot");
    cout<<"Reporte rutas disponibles creado."<<endl;

    cirDoble.generateDotFile("dot/avionesMantenimiento.dot");
    cout<<"Reporte aviones en mantenimiento creado."<<endl;

    arbolB.generateDotFile("dot/avionesDisponibles.dot");
    cout<<"Reporte aviones disponibles creado."<<endl;

    matriz.generateDot("dot/tablaDeVuelos.dot");
    cout<<"Reporte tabla de vuelos creado."<<endl;
    return;
}

void menu(){
    
    while(true){
        int opcion;
        cout<<"----------SISTEMA DE GESTION DE AEROPUERTO----------"<<endl;
        cout<<"*******************Menu principal*******************"<<endl;
        cout<<"1. Carga de aviones"<<endl;
        cout<<"2. Carga de pilotos"<<endl;
        cout<<"3. Carga de rutas"<<endl;
        cout<<"4. Carga de movimientos"<<endl;
        cout<<"5. Consulta de horas de vuelo"<<endl;
        cout<<"6. Recomendar ruta"<<endl;
        cout<<"7. Visualizar reportes"<<endl;
        cout<<"8. salir"<<endl;
        cout<<"****************************************************"<<endl;
        cout<<"SELECCIONE UNA OPCION: "<<endl;
        cin>>opcion;

        switch (opcion) {
            case 1: 
                cAviones();
                break;
            case 2: 
                cPilotos();
                break;
            case 3: 
                cRutas();
                break;
            case 4: 
                cMovimientos();
                break;
            case 5: 
                consultaHVuelo();
                break;
            case 6: 
                recomendarRuta();
                break;
            case 7: 
                reportes();
                break;
            case 8: 
                return;
                break;
            default:
                cout<<"Opcion invalida"<<endl;
        }
    }
}

int main()
{
    //cargaMatriz();
    menu();
    return 0;
}

/*
g++ -o main main.cpp
./main.exe

*/