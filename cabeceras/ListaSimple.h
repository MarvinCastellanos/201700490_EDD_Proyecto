#include <iostream>
using namespace std;
#include "NodoLista.h"

class ListaSimple
{
private:
    Nodo *primero, *ultimo;
public:
    ListaSimple(/* args */);
    bool estaVacia();
    void insertarFinal(string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia);
    void eliminarInicio();
    void eliminarFinal();
    void visualizarLista();
    Nodo * eliminar(string nId);
    string getDatos();
    ~ListaSimple();
};

ListaSimple::ListaSimple(/* args */)
{
    primero = ultimo = nullptr;
}

bool ListaSimple::estaVacia()
{
    return (primero == nullptr) && (ultimo == nullptr);
}

Nodo * ListaSimple::eliminar(string nId){
    Nodo * aux = primero;
    if(primero->getDato()==nId){
        primero = primero->getSiguiente();
        primero->setAnterior(nullptr);
        return aux;
    }
    while(aux){
        if(aux->getSiguiente()->getDato()==nId){
            Nodo *aux2 = aux->getSiguiente();

            //aux2->getSiguiente()->setAnterior(aux);
            aux->setSiguiente(aux2->getSiguiente());
            aux2->setSiguiente(nullptr);
            aux2->setAnterior(nullptr);
            return aux2;
        }
        aux=aux->getSiguiente();
    }
    return nullptr;
}

void ListaSimple::insertarFinal(string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia)
{
    Nodo *nuevo = new Nodo(nombre,nacionalidad,nId,vuelo,hVuelo,tLicencia);
    if (ListaSimple::estaVacia())
    {
        /* code */
        primero = ultimo = nuevo;
    }
    else
    {
        ultimo->setSiguiente(nuevo); //Se enlaza el último nodo al nuevo
        ultimo = nuevo; //Se verfica que el nodo creado sea el último
    }
}

void ListaSimple::eliminarInicio()
{
    if (ListaSimple::estaVacia())
    {
        /* code */
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        if (primero == ultimo)
        {
            /* code */
            delete primero;
            primero = ultimo = nullptr;
        }
        else
        {
            Nodo *segundo = primero->getSiguiente();
            delete primero;
            primero = segundo;
        }   
    } 
}

void ListaSimple::eliminarFinal()
{
    if (ListaSimple::estaVacia())
    {
        cout << "La lista esta vacia" << endl;
    }
    else{
        Nodo* temporal = primero;
        if (primero == ultimo)
        {
            /* code */
            delete primero;
            primero = ultimo = nullptr;
        }
        else{
            while (temporal != nullptr)
            {
                /* code */
                if (temporal->getSiguiente() == ultimo) //Si el siguiente de temporal es el último, entonces temporal es el antepenultimo
                {
                    /* code */
                    delete ultimo;
                    temporal->setSiguiente(nullptr);
                    ultimo = temporal;
                }
                temporal = temporal->getSiguiente(); //Recorriendo la lista
            }
            
        }
        
    }
    
}

void ListaSimple::visualizarLista()
{
    if (ListaSimple::estaVacia())
    {
        /* code */
        cout << "La lista esta vacia" << endl;
    }
    else
    {
        string nodoDato;
        Nodo *actual = primero;
        while (actual != nullptr)
        {
            /* code */
            nodoDato = actual->getDato();
            //cout << nodoDato << endl;
            cout << nodoDato << (actual->getSiguiente() != nullptr ? " -> ": "\n");
            actual = actual->getSiguiente();
        }
        
    }
    
}

string ListaSimple::getDatos(){
    if (ListaSimple::estaVacia()){
        return "";
    }
    else{
        string nodoDato;
        string data="";
        Nodo *actual = primero;
        while (actual != nullptr)
        {
            nodoDato = actual->getDato();
            //cout << nodoDato << endl;
            data=data+nodoDato;
            data=data+(actual->getSiguiente() != nullptr ? " -> ": "");
            actual = actual->getSiguiente();
        }
        return data;
    }
}

ListaSimple::~ListaSimple()
{
}
