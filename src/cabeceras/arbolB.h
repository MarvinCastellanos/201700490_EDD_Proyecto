#include <iostream>
#include <vector>
#include <fstream>

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
    void remove(string k);
    void generateDotFile(const string& filename);
    void generateDotFile(ofstream &file, BTreeNode* node, int &nodeCount);
};

void BTree::remove(string k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(k);

    if (root->keys.size() == 0) {
        BTreeNode* tmp = root;
        if (root->isLeaf)
            root = nullptr;
        else
            root = root->children[0];
        delete tmp;
    }
}

void BTreeNode::remove(string k) {
    int idx = find(keys.begin(), keys.end(), k) - keys.begin();

    if (idx < keys.size() && keys[idx] == k) {
        if (isLeaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (isLeaf) {
            cout << "The key " << k << " is not in the tree\n";
            return;
        }

        bool flag = ((idx == keys.size()) ? true : false);

        if (children[idx]->keys.size() < t)
            fill(idx);

        if (flag && idx > keys.size())
            children[idx - 1]->remove(k);
        else
            children[idx]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    string k = keys[idx];

    if (children[idx]->keys.size() >= t) {
        string pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->keys.size() >= t) {
        string succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        merge(idx);
        children[idx]->remove(k);
    }
}

string BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->isLeaf)
        cur = cur->children[cur->keys.size()];
    return cur->keys[cur->keys.size() - 1];
}

string BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->isLeaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t)
        borrowFromPrev(idx);
    else if (idx != keys.size() && children[idx + 1]->keys.size() >= t)
        borrowFromNext(idx);
    else {
        if (idx != keys.size())
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);

    if (!child->isLeaf)
        child->children.insert(child->children.begin(), sibling->children[sibling->children.size() - 1]);

    keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];

    sibling->keys.pop_back();
    if (!sibling->isLeaf)
        sibling->children.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    if (!child->isLeaf)
        child->children.push_back(sibling->children[0]);

    keys[idx] = sibling->keys[0];

    sibling->keys.erase(sibling->keys.begin());
    if (!sibling->isLeaf)
        sibling->children.erase(sibling->children.begin());
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    for (int i = 0; i < sibling->keys.size(); i++)
        child->keys.push_back(sibling->keys[i]);

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->keys.size(); i++)
            child->children.push_back(sibling->children[i]);
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);

    delete sibling;
}

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
    system("start imagenes/avionesDisponibles.png");
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