#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

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

        /*if(item["estado"]=="Disponible"){
            avionesDisponibles.insertar(item["vuelo"],item["numero_de_registro"],item["modelo"],item["fabricante"],item["ano_fabricacion"],item["capacidad"],item["peso_max_despegue"],item["aerolinea"],item["estado"]);
        }else if(item["estado"]=="Mantenimiento"){
            avionesMantenimiento.insertar(item["vuelo"],item["numero_de_registro"],item["modelo"],item["fabricante"],item["ano_fabricacion"],item["capacidad"],item["peso_max_despegue"],item["aerolinea"],item["estado"]);
        }else{
            cout<<"El estado no es valido"<<endl;
        }*/

       cout<<aerolinea<<endl;
    }
    return;
}

void cPilotos(){
    cout<<"Carga de pilotos"<<endl;
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