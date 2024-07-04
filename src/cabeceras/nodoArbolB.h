#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class BTreeNode {
public:
    vector<string> keys;
    vector<BTreeNode*> children;
    bool isLeaf;
    int t; // Minimum degree

    BTreeNode(int _t, bool _isLeaf);
    void remove(string k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);

    void insertNonFull(string k);
    void splitChild(int i, BTreeNode* y);
    string getPredecessor(int idx);
    string getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

BTreeNode::BTreeNode(int t1, bool leaf) {
    t = t1;
    isLeaf = leaf;
}
