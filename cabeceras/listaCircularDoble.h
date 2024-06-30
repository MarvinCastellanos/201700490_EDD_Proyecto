#include <iostream>
#include <fstream>
#include "nodoCircularD.h"
using namespace std;

class circularDoble {
private:
    NodeCircular* head;

public:
    circularDoble() : head(nullptr) {}

    void insert(string vuelo,string nRegistro, string modelo, int capacidad, string aerolinea, string ciudadDestino, string estado) {
        NodeCircular* newNode = new NodeCircular(vuelo,nRegistro,modelo,capacidad,aerolinea,ciudadDestino,estado);

        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            NodeCircular* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    void remove(string nRegistro) {
        if (!head) return;

        NodeCircular* current = head;
        do {
            if (current->nRegistro == nRegistro) {
                NodeCircular* prevNode = current->prev;
                NodeCircular* nextNode = current->next;
                if (current == head && current->next == head) {
                    head = nullptr;
                } else {
                    prevNode->next = nextNode;
                    nextNode->prev = prevNode;
                    if (current == head) head = nextNode;
                }
                delete current;
                return;
            }
            current = current->next;
        } while (current != head);
    }

    void generateDotFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        file << "digraph G {\n";
        file << "  rankdir=LR;\n";
        file << "  label=\"Lista de aviones en mantenimiento\";\n";
        file << "  node [shape=record];\n";

        if (head) {
            NodeCircular* current = head;
            int count = 0;
            do {
                file << "  node" << count << " [label=\" " << current->nRegistro << " \"];\n";
                current = current->next;
                count++;
            } while (current != head);

            for (int i = 0; i < count; ++i) {
                file << "  node" << i << " -> node" << (i + 1) % count << ";\n";
                file << "  node" << (i + 1) % count << " -> node" << i << ";\n";
            }
        }

        file << "}\n";
        file.close();

        system("dot -Tpng dot/avionesMantenimiento.dot -o imagenes/avionesMantenimiento.png");
        system("start imagenes/avionesMantenimiento.png");
    }

    void printList() {
        if (!head) return;

        NodeCircular* current = head;
        do {
            cout << current->nRegistro << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }
};