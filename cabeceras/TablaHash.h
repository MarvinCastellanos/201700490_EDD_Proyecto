#include <iostream>
#include <fstream>
using namespace std;
#include "ListaSimple.h"

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
        sum+=(int)valor[i];
    }

    /*for (char ch : valor) {
        sum += static_cast<int>(ch);
    }*/
    
    return (int)(sum % tamTabla);
    /*int i;
    i = (int)(valor % tamTabla);
    //cout << "Llave asignada: " << i << endl;
    return i;*/
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
        
        file<<"subgraph cluster_1{";//cluster 1
        file<<"label=\"\";";
        for(int i=0; i<tamTabla;i++){
            file<<"L"<<i;
            if(!(i==tamTabla-1)){
                file<<"->";
            }
        }
        file<<"[style= invis];";
        file<<"}\n";

        for(int i=0; i<tamTabla;i++){
            file<<"L"<<i<<"[label=\""<<tabla[i].getDatos()<<"\" shape=box];";
        }

        file << "}\n";
        file.close();

        system("dot -Tpng dot/tablaPilotos.dot -o imagenes/tablaPilotos.png");
}


TablaHash::~TablaHash()
{
}
