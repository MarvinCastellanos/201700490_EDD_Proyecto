#include <iostream>
#include <fstream>
#include "nodoArbolBinario.h"

using namespace std;

class arbolBinario {
private:
    Node* root;

    Node* insert(Node* node, string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia) {
        if (node == nullptr) {
            return new Node(nombre,nacionalidad,nId,vuelo,hVuelo,tLicencia);
        }
        if (hVuelo < node->hVuelo) {
            node->left = insert(node->left, nombre,nacionalidad,nId,vuelo,hVuelo,tLicencia);
        } else if (hVuelo > node->hVuelo) {
            node->right = insert(node->right, nombre,nacionalidad,nId,vuelo,hVuelo,tLicencia);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, int data) {
        if (node == nullptr) {
            return node;
        }
        if (data < node->hVuelo) {
            node->left = remove(node->left, data);
        } else if (data > node->hVuelo) {
            node->right = remove(node->right, data);
        } else {
            // Nodo con solo un hijo o sin hijos
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Nodo con dos hijos: obtener el sucesor en inorden (más pequeño en el subárbol derecho)
            Node* temp = findMin(node->right);
            node->hVuelo = temp->hVuelo;
            node->right = remove(node->right, temp->hVuelo);
        }
        return node;
    }

    void generateDotFile(ofstream& file, Node* node) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                file << "    " << node->hVuelo << " -> " << node->left->hVuelo << ";\n";
                generateDotFile(file, node->left);
            }
            if (node->right != nullptr) {
                file << "    " << node->hVuelo << " -> " << node->right->hVuelo << ";\n";
                generateDotFile(file, node->right);
            }
        }
    }

public:
    arbolBinario() : root(nullptr) {}

    void insert(string nombre, string nacionalidad, string nId, string vuelo, int hVuelo, string tLicencia) {
        root = insert(root, nombre,nacionalidad,nId,vuelo,hVuelo,tLicencia);
    }

    Node* getRoot(){
        return this->root;
    }

    void remove(int data) {
        root = remove(root, data);
    }

    void preOrder(Node* node) {
        if (node != nullptr) {
            cout << node->hVuelo << "->";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->hVuelo << "->";
            inOrder(node->right);
        }
    }

    void posOrder(Node* node) {
        if (node != nullptr) {
            posOrder(node->left);
            posOrder(node->right);
            cout << node->hVuelo << "->";
        }
    }

    void generateDotFile(const string& filename) {
        ofstream file;
        file.open(filename);
        file << "digraph G {\n";
        file << "  label=\"Arbol de horas de vuelo\";\n";
        if (root != nullptr) {
            generateDotFile(file, root);
        }
        file << "}\n";
        file.close();

        system("dot -Tpng dot/horasVuelo.dot -o imagenes/horasVuelo.png");
        system("start imagenes/horasVuelo.png");
    }
};