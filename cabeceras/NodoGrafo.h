#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();

// Definición de la clase Nodo para la lista de adyacencia
class NodoGrafo {
public:
    int valor;
    int peso; // Peso de la arista
    NodoGrafo* siguiente;

    NodoGrafo(int v, int p) : valor(v), peso(p), siguiente(nullptr) {}
};