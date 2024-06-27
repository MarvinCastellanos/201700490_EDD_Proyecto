#include <iostream>
#include <fstream>
#include "json.hpp"


using json = nlohmann::json;
using namespace std;

#include "./cabeceras/arbolBinario.h"
#include "./cabeceras/listaCircularDoble.h"

arbolBinario aBinario;
circularDoble cirDoble;

void cAviones(){
    cout<<"Carga de aviones"<<endl;

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
            cout<<"Disponibles";
        }else if(item["estado"]=="Mantenimiento"){
            cirDoble.insert(vuelo,nRegistro,modelo,capacidad,aerolinea,ciudadDestino,estado);
        }else{
            cout<<"El estado no es valido"<<endl;
        }

       //cout<<aerolinea<<endl;
    }
    cirDoble.remove("N10003");
    cirDoble.generateDotFile("dot/avionesMantenimiento.dot");
    return;
}

void cPilotos(){
    cout<<"Carga de pilotos"<<endl;
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

        cout<<nId<<endl;
    }

    /*cout<<"Preorder: "<<endl;
    aBinario.preOrder(aBinario.getRoot());
    cout<<endl;
    cout<<endl;
    cout<<"Inorder: "<<endl;
    aBinario.inOrder(aBinario.getRoot());
    cout<<endl;
    cout<<endl;
    cout<<"Posorder: "<<endl;
    aBinario.posOrder(aBinario.getRoot());
    cout<<endl;*/
    aBinario.generateDotFile("dot/horasVuelo.dot");
    return; 
}

void cRutas(){
    cout<<"Carga de rutas"<<endl;
    return;
}

void cMovimientos(){
    cout<<"Carga de movimientos"<<endl;
    return;
}

void consultaHVuelo(){
    cout<<"Consulta horas de vuelo"<<endl;
    return;
}

void recomendarRuta(){
    cout<<"Recomendar ruta"<<endl;
    return;
}

void reportes(){
    cout<<"Visualizar reportes"<<endl;
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
    menu();
    return 0;
}

/*
g++ -o main main.cpp
./main.exe

*/