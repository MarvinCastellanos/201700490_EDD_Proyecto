#include <iostream>
#include <fstream>
using namespace std;
#include "ListaSimple.h"
//#include "NodoLista.h"

class TablaHash
{
private:
    /* data */
    int tamTabla;
    int numElementos;
    ListaSimple *tabla;
public:
    TablaHash(int tamTabla_);
    int Clave(string valor);
    void Insertar(string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia);
    void imprimirTabla();
    Nodo * eliminar(string nId);
    void generaReporte(string filename);
    ~TablaHash();
};

TablaHash::TablaHash(int tamTabla_)
{
    tamTabla = tamTabla_;
    tabla = new ListaSimple[tamTabla];
    for (int i = 0; i < tamTabla; i++)
    {
        //cout << tabla->estaVacia() << endl;
    }
    numElementos = 0;    
}

int TablaHash::Clave(string valor)
{
    char c=valor[0];
    int sum = (int)c;
    for (int i=1;i<valor.size();i++){
        sum+=(int)valor[i]- '0';
    }

    return (int)(sum % 18);
}

Nodo * TablaHash::eliminar(string nId){
    int indice= Clave(nId);
    Nodo * eliminado= tabla[indice].eliminar(nId);
    return eliminado;
}

void TablaHash::Insertar(string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia)
{
    int indice = Clave(nId);
    tabla[indice].insertarFinal(nombre,nacionalidad,nId,vuelo,hVuelo,tLicencia);
}

void TablaHash::imprimirTabla()
{
    for (int i = 0; i < tamTabla; i++)
    {
        cout << "[" << i << "] -> ";
        tabla[i].visualizarLista();
    }
}

void TablaHash::generaReporte(string filename){
    ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }
        file << "digraph G {\n";
        file << "  label=\"Tabla de pilotos\";\n"<<endl;

        file<< "subgraph cluster_0{"<<endl;//cluster 0
        file<< "label=\"\";";
        for(int i=0; i<tamTabla;i++){
            file<<i;
            if(!(i==tamTabla-1)){
                file<<"->";
            }
        }
        file<<"[style=invis];"<<endl;
        file<<"}\n"<<endl;
        
        file<<"subgraph cluster_1{\n";//cluster 1
        file<<"label=\"\";";
        for(int i=0; i<tamTabla;i++){
            file<<"L"<<i;
            if(!(i==tamTabla-1)){
                file<<"->";
            }
        }
        file<<"[style= invis];"<<endl;
        file<<"}\n"<<endl;

        for(int i=0; i<tamTabla;i++){
            file<<"L"<<i<<"[label=\""<<tabla[i].getDatos()<<"\" shape=box];\n";
        }

        file << "}\n";
        file.close();

        system("dot -Tpng dot/tablaPilotos.dot -o imagenes/tablaPilotos.png");
        system("start imagenes/tablaPilotos.png");
}


TablaHash::~TablaHash()
{
}
