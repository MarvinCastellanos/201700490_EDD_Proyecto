#include <iostream>
#include <fstream>

class Node {
public:
    //int data;
    string nombre;
    string nacionalidad;
    string nId;
    string vuelo;
    int hVuelo;
    string tLicencia;
    Node* left;
    Node* right;

    Node(string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia) : nombre(nombre), nacionalidad(nacionalidad), nId(nId),vuelo(vuelo),hVuelo(hVuelo),tLicencia(tLicencia), left(nullptr), right(nullptr) {}
};
