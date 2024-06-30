#include "NodoGrafo.h"

using namespace std;

// Definición de la clase GrafoDirigido
class GrafoDirigido {
private:
    NodoGrafo** adj; // Array de punteros a Nodo (lista de adyacencia)
    string* vertices; // Array de nombres de vértices
    int numVertices; // Número de vértices en el grafo
    int capacidad; // Capacidad actual de los arrays

    int buscarIndice(string v) {
        for (int i = 0; i < numVertices; ++i) {
            if (vertices[i] == v) {
                return i;
            }
        }
        return -1;
    }

public:
    // Constructor
    GrafoDirigido(int cap) : numVertices(0), capacidad(cap) {
        adj = new NodoGrafo*[capacidad];
        vertices = new string[capacidad];
        for (int i = 0; i < capacidad; ++i) {
            adj[i] = nullptr;
        }
    }

    // Método para agregar un vértice
    void agregarVertice(string v) {
        if (buscarIndice(v) == -1) {
            if (numVertices == capacidad) {
                cout << "Capacidad máxima alcanzada. No se puede agregar más vértices." << endl;
                return;
            }
            vertices[numVertices] = v;
            numVertices++;
        }
    }

    // Método para agregar una arista dirigida de u a v con peso p
    void agregarArista(string u, string v, int p) {
        int u_idx = buscarIndice(u);
        int v_idx = buscarIndice(v);

        if (u_idx == -1 || v_idx == -1) {
            cout << "Uno o ambos vértices no existen." << endl;
            return;
        }

        NodoGrafo* nuevoNodo = new NodoGrafo(v_idx, p);
        nuevoNodo->siguiente = adj[u_idx];
        adj[u_idx] = nuevoNodo;
    }

    // Método para eliminar una arista dirigida de u a v
    /*void eliminarArista(string u, string v) {
        int u_idx = buscarIndice(u);
        int v_idx = buscarIndice(v);

        if (u_idx == -1 || v_idx == -1) return;

        NodoGrafo* actual = adj[u_idx];
        NodoGrafo* previo = nullptr;

        while (actual != nullptr && actual->valor != v_idx) {
            previo = actual;
            actual = actual->siguiente;
        }

        if (actual != nullptr) {
            if (previo == nullptr) {
                adj[u_idx] = actual->siguiente;
            } else {
                previo->siguiente = actual->siguiente;
            }
            delete actual;
        }
    }
*/
    // Método para generar un archivo .dot que representa el grafo
    void generarDot(string filename) {
        ofstream file(filename);
        file << "digraph GrafoDirigido {" << endl;
        file << "  label=\"Rutas disponibles\";\n";

        for (int i = 0; i < numVertices; ++i) {
            NodoGrafo* actual = adj[i];
            while (actual != nullptr) {
                file << "  " << vertices[i] << " -> " << vertices[actual->valor] << " [label=\"" << actual->peso << "\"];" << endl;
                actual = actual->siguiente;
            }
        }

        file << "}" << endl;
        file.close();

        system("dot -Tpng dot/RutasDeVuelo.dot -o imagenes/RutasDeVuelo.png");
        system("start imagenes/RutasDeVuelo.png");
    }

    // Método para encontrar la ruta más corta desde el vértice fuente a todos los demás vértices usando Dijkstra
    pair<int*, int*> dijkstra(int src) {
        int* dist = new int[numVertices];
        int* prev = new int[numVertices];
        bool* visitado = new bool[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            dist[i] = INF;
            prev[i] = -1;
            visitado[i] = false;
        }

        dist[src] = 0;

        for (int i = 0; i < numVertices - 1; ++i) {
            int u = -1;
            for (int j = 0; j < numVertices; ++j) {
                if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            visitado[u] = true;

            NodoGrafo* actual = adj[u];
            while (actual != nullptr) {
                int v = actual->valor;
                int peso = actual->peso;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    prev[v] = u;
                }
                actual = actual->siguiente;
            }
        }

        delete[] visitado;
        return {dist, prev};
    }

    // Método para encontrar y mostrar la ruta más corta entre dos vértices
    void mostrarRutaMasCorta(string src, string dest) {
        int src_idx = buscarIndice(src);
        int dest_idx = buscarIndice(dest);

        if (src_idx == -1 || dest_idx == -1) {
            cout << "Uno o ambos vértices no existen." << endl;
            return;
        }

        auto result = dijkstra(src_idx);
        int* dist = result.first;
        int* prev = result.second;

        if (dist[dest_idx] == INF) {
            cout << "No hay ruta desde " << src << " a " << dest << "." << endl;
        } else {
            //cout << "La ruta más corta desde " << src << " a " << dest << " tiene una distancia de " << dist[dest_idx] << "." << endl;
            cout << "Ruta: ";
            vector<string> ruta;
            for (int at = dest_idx; at != -1; at = prev[at]) {
                ruta.push_back(vertices[at]);
            }
            reverse(ruta.begin(), ruta.end());
            for (size_t i = 0; i < ruta.size(); ++i) {
                cout << ruta[i];
                if (i < ruta.size() - 1) cout << " -> ";
            }
            cout << endl;
        }

        delete[] dist;
        delete[] prev;
    }

    // Destructor para liberar memoria
    ~GrafoDirigido() {
        for (int i = 0; i < numVertices; ++i) {
            NodoGrafo* actual = adj[i];
            while (actual != nullptr) {
                NodoGrafo* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
        delete[] adj;
        delete[] vertices;
    }
};