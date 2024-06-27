#include "nodoArbolB.h"
using namespace std;

class BTree {
private:
    BTreeNode* root;
    int t;

public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void insert(string k);
    void generateDotFile(const string& filename);
    void generateDotFile(ofstream &file, BTreeNode* node, int &nodeCount);
};

void BTree::insert(string k) {
   if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);
            root = s;
        } else
            root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(string k) {
   int i = keys.size() - 1;

    if (isLeaf) {
        keys.push_back("");
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        i++;
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);
            if (keys[i] < k)
                i++;
        }
        children[i]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
   BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    for (int j = 0; j < t - 1; j++)
        z->keys.push_back(y->keys[j + t]);
    if (!y->isLeaf) {
        for (int j = 0; j < t; j++)
            z->children.push_back(y->children[j + t]);
    }
    y->keys.resize(t - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

void BTree::generateDotFile(const string& filename) {
    ofstream file;
    file.open(filename);
    file << "digraph G {\n";
    file << "  label=\"Arbol de aviones disponibles\";\n";
    file << "  node [shape=record];\n";
    int nodeCount = 0;
    generateDotFile(file, root, nodeCount);
    file << "}\n";
    file.close();

    system("dot -Tpng dot/avionesDisponibles.dot -o imagenes/avionesDisponibles.png");
}

void BTree::generateDotFile(ofstream &file, BTreeNode* node, int &nodeCount) {
    if (!node) return;

    int currentNode = nodeCount;
    file << "    node" << currentNode << " [label=\"";
    for (int i = 0; i < node->keys.size(); i++) {
        file << node->keys[i];
        if (i != node->keys.size() - 1) file << "|";
    }
    file << "\"];\n";

    for (int i = 0; i < node->children.size(); i++) {
        nodeCount++;
        file << "    node" << currentNode << " -> node" << nodeCount << ";\n";
        generateDotFile(file, node->children[i], nodeCount);
    }
}