#include <iostream>
#include <fstream>

struct NodeCircular {
    //int data;
    string vuelo;
    string nRegistro;
    string modelo;
    int capacidad;
    string aerolinea;
    string ciudadDestino;
    string estado;

    NodeCircular* next;
    NodeCircular* prev;
    NodeCircular(string vuelo,string nRegistro, string modelo, int capacidad, string aerolinea, string ciudadDestino, string estado) : capacidad(capacidad), vuelo(vuelo),nRegistro(nRegistro),modelo(modelo), aerolinea(aerolinea),ciudadDestino(ciudadDestino),estado(estado), next(nullptr), prev(nullptr) {}
};
