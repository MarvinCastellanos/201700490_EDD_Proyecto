#include <iostream>
using namespace std;

class Nodo
{
private:
    /* data */
    //string dato;
    Nodo *anterior;
    Nodo *siguiente;
public:
    string nombre;
    string nacionalidad;
    string dato;//nId
    string vuelo;
    int hVuelo;
    string tLicencia;

    Nodo(string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia);
    Nodo *getSiguiente();
    Nodo *getAnterior();
    void setSiguiente(Nodo *siguiente);
    void setAnterior(Nodo *anterior);
    string getDato();
    void setDato(int dato);
    ~Nodo();
};

Nodo::Nodo(string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia)
{
    this->nombre = nombre;
    this->nacionalidad = nacionalidad;
    this->dato = nId;
    this->vuelo = vuelo;
    this->hVuelo = hVuelo;
    this->tLicencia = tLicencia;

    this->anterior = nullptr;
    this->siguiente = nullptr;
}

Nodo* Nodo::getSiguiente(){
    return this->siguiente;
}

Nodo* Nodo::getAnterior(){
    return this->anterior;
}

void Nodo::setSiguiente(Nodo *siguiente){
    this->siguiente = siguiente;
}

void Nodo::setAnterior(Nodo *anterior){
    this->anterior = anterior;
}

string Nodo::getDato(){
    return this->dato;
}

Nodo::~Nodo()
{
}
