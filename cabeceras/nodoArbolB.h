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

    void insertNonFull(string k);
    void splitChild(int i, BTreeNode* y);
};

BTreeNode::BTreeNode(int t1, bool leaf) {
    t = t1;
    isLeaf = leaf;
}
