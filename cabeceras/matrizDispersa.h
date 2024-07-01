#include <iostream>
#include <fstream>

using namespace std;
// Nodo que almacena los datos
struct NodeMatriz {
    string row, col;
    string value;
    NodeMatriz* right;
    NodeMatriz* left;
    NodeMatriz* down;
    NodeMatriz* up;
    
    NodeMatriz(const string& r, const string& c, const string& v) : row(r), col(c), value(v), right(nullptr), left(nullptr), down(nullptr), up(nullptr) {}
};

// Nodo cabeza para filas y columnas
struct HeadNode {
    string index;
    HeadNode* next;
    HeadNode* prev;
    NodeMatriz* node;
    
    HeadNode(const string& i) : index(i), next(nullptr), prev(nullptr), node(nullptr) {}
};

class MatrizDispersa {
private:
    HeadNode* rowHead;
    HeadNode* colHead;

    HeadNode* getOrCreateRowHead(const string& row);
    HeadNode* getOrCreateColHead(const string& col);
    void removeFromRow(const string& row, const string& col);
    void removeFromCol(const string& row, const string& col);
    void appendHeadNode(HeadNode*& head, HeadNode* newNode);
    void appendDataNode(NodeMatriz*& head, NodeMatriz* newNode, bool isRow);

public:
    MatrizDispersa();
    ~MatrizDispersa();
    void insert(const string& row, const string& col, const string& value);
    void remove(const std::string& row, const std::string& col);
    //void display();
    void generateDot(const string& filename);
};

MatrizDispersa::MatrizDispersa() : rowHead(nullptr), colHead(nullptr) {}

MatrizDispersa::~MatrizDispersa() {
    // Cleanup code to free memory
    // To be implemented
}

void MatrizDispersa::appendHeadNode(HeadNode*& head, HeadNode* newNode) {
    if (!head) {
        head = newNode;
    } else {
        HeadNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void MatrizDispersa::appendDataNode(NodeMatriz*& head, NodeMatriz* newNode, bool isRow) {
    if (!head) {
        head = newNode;
    } else {
        NodeMatriz* temp = head;
        while (isRow ? temp->right : temp->down) {
            temp = isRow ? temp->right : temp->down;
        }
        if (isRow) {
            temp->right = newNode;
            newNode->left = temp;
        } else {
            temp->down = newNode;
            newNode->up = temp;
        }
    }
}

HeadNode* MatrizDispersa::getOrCreateRowHead(const string& row) {
    HeadNode* temp = rowHead;
    while (temp) {
        if (temp->index == row) return temp;
        temp = temp->next;
    }

    HeadNode* newHead = new HeadNode(row);
    appendHeadNode(rowHead, newHead);
    return newHead;
}

HeadNode* MatrizDispersa::getOrCreateColHead(const string& col) {
    HeadNode* temp = colHead;
    while (temp) {
        if (temp->index == col) return temp;
        temp = temp->next;
    }

    HeadNode* newHead = new HeadNode(col);
    appendHeadNode(colHead, newHead);
    return newHead;
}

void MatrizDispersa::insert(const string& row, const string& col, const string& value) {
    HeadNode* rowNode = getOrCreateRowHead(row);
    HeadNode* colNode = getOrCreateColHead(col);

    NodeMatriz* newNode = new NodeMatriz(row, col, value);

    appendDataNode(rowNode->node, newNode, true);
    appendDataNode(colNode->node, newNode, false);
}

void MatrizDispersa::removeFromRow(const string& row, const string& col) {
    HeadNode* rowNode = rowHead;
    while (rowNode && rowNode->index != row) {
        rowNode = rowNode->next;
    }

    if (!rowNode) return;

    NodeMatriz* temp = rowNode->node;
    if (temp->col == col) {
        rowNode->node = temp->right;
        if (temp->right) temp->right->left = nullptr;
        delete temp;
        return;
    }

    while (temp->right && temp->right->col != col) {
        temp = temp->right;
    }

    if (temp->right) {
        NodeMatriz* toDelete = temp->right;
        temp->right = toDelete->right;
        if (toDelete->right) toDelete->right->left = temp;
        delete toDelete;
    }
}

void MatrizDispersa::removeFromCol(const string& row, const string& col) {
    HeadNode* colNode = colHead;
    while (colNode && colNode->index != col) {
        colNode = colNode->next;
    }

    if (!colNode) return;

    NodeMatriz* temp = colNode->node;
    if (temp->row == row) {
        colNode->node = temp->down;
        if (temp->down) temp->down->up = nullptr;
        delete temp;
        return;
    }

    while (temp->down && temp->down->row != row) {
        temp = temp->down;
    }

    if (temp->down) {
        NodeMatriz* toDelete = temp->down;
        temp->down = toDelete->down;
        if (toDelete->down) toDelete->down->up = temp;
        delete toDelete;
    }
}

void MatrizDispersa::remove(const string& row, const string& col) {
    removeFromRow(row, col);
    removeFromCol(row, col);
}

/*void MatrizDispersa::display() {
    HeadNode* tempRow = rowHead;
    while (tempRow) {
        NodeMatriz* tempNode = tempRow->node;
        while (tempNode) {
            cout << "(" << tempNode->row << ", " << tempNode->col << ", " << tempNode->value << ") ";
            tempNode = tempNode->right;
        }
        tempRow = tempRow->next;
    }
    cout << endl;
}*/

void MatrizDispersa::generateDot(const string& filename) {
    ofstream file;
    file.open(filename);
    file << "digraph Matriz_dispersa {\n";
    file << "node[shape=box];\n";
    file << "label=\"Tabla de Vuelos\";\n";

    //cabeceras de columnas
    HeadNode *auxCol= colHead;
    file<<"\n";
    file<< "n0 [label=\"head\" group=0];"<<endl;
    while(auxCol){
        //n0 [label="admin" group=1];
        file << "c"<<auxCol->index<<"[label=\""<<auxCol->index<<"\" group="<<auxCol->index<<"];"<<endl;
        auxCol=auxCol->next;
    }

    //cabeceras de filas
    HeadNode *auxRow= rowHead;
    file<<"\n";
    while(auxRow){
        //n0 [label="admin" group=1];
        file << "r"<<auxRow->index<<"[label=\""<<auxRow->index<<"\" group=0];"<<endl;
        auxRow=auxRow->next;
    }

    //columnas
    HeadNode *auxCol1= colHead;
    file<<"\n";
    while(auxCol1){
        NodeMatriz *auxNode = auxCol1->node;
        while(auxNode){
            //n7 [label="Usr1" group=2];
            file<<"n"<<auxNode->value<<"[label=\""<<auxNode->value<<"\" group="<<auxNode->col<<"];"<<endl;
            auxNode=auxNode->down;
        }
        file<<"\n";
        auxCol1=auxCol1->next;
    }

    //Relaciones col
    auxCol = colHead;
    //n0 -> n1 -> n2 -> n3;
    file<<"\n";
    file<<"n0";
    while(auxCol){
        file<<"->c"<<auxCol->index;
        auxCol=auxCol->next;
    }
    file<<";"<<endl;

    auxRow=rowHead;
    file<<"\n";
    while (auxRow)
    {
        file<<"r"<<auxRow->index;
        NodeMatriz *auxNode=auxRow->node;
        while (auxNode)
        {
            file<<"->"<<"n"<<auxNode->value;
            auxNode=auxNode->right;
        }
        file<<";"<<endl;
        auxRow=auxRow->next;
    }
    file<<"\n";
    
    //Relacioens row
    auxRow = rowHead;
    //n0 -> n1 -> n2 -> n3;
    file<<"\n";
    file<<"n0";
    while(auxRow){
        file<<"->r"<<auxRow->index;
        auxRow=auxRow->next;
    }
    file<<";"<<endl;

    auxCol=colHead;
    file<<"\n";
    while (auxCol)
    {
        file<<"c"<<auxCol->index;
        NodeMatriz *auxNode=auxCol->node;
        while (auxNode)
        {
            file<<"->"<<"n"<<auxNode->value;
            auxNode=auxNode->down;
        }
        file<<";"<<endl;
        auxCol=auxCol->next;
    }
    file<<"\n";

    //encuadre
    //{ rank=same; n0; n1; n2; n3; }
    file<<"{ rank=same;";
    file<<"n0";
    auxCol=colHead;
    while(auxCol){
        file<<";c"<<auxCol->index;
        auxCol=auxCol->next;
    }
    file<<";}"<<endl;

    auxRow=rowHead;
    file<<"\n";
    while (auxRow)
    {
        file<<"{rank=same;r"<<auxRow->index;
        NodeMatriz *auxNode=auxRow->node;
        while (auxNode)
        {
            file<<";"<<"n"<<auxNode->value;
            auxNode=auxNode->right;
        }
        file<<";}"<<endl;
        auxRow=auxRow->next;
    }
    file<<"\n";

    file << "}\n";
    file.close();

    system("dot -Tpng dot/tablaDeVuelos.dot -o imagenes/tablaDeVuelos.png");
    system("start imagenes/tablaDeVuelos.png");
}