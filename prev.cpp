#include "prev.h"
#include <memory>
#include <algorithm>
// DEBUG
#include <iostream>
#include <string>

using namespace std;

#define node_ptr shared_ptr<struct Node>

/**
 * @struct Strukura węzła z których budujemy nasze drzewo przedziałowe
 */
struct Node {
    node_ptr left, right;
    int value;
    // zwykły konstruktor
    Node(node_ptr l, node_ptr r, int v) : left(l), right(r), value(v) {}
};
// Tablica zawierająca korzenie drzew zawierających kolejne indeksy
static vector<node_ptr> roots;

/**
 * @brief Bezpieczne obliczenie średniej dwóch wartości
 * 
 * @param x pierwsza wartość
 * @param y druga wartość
 * @return średnia
 */
static int avg(int x, int y){
    return (x >> 1) + (y >> 1) + (x & 1) + (y & 1);
}

/**
 * @brief Przejscie po drzewie do wierzcholka z nr x, i zebranie po drodze wszystkich wezłów
 * @param index drzewo którego indeksu zabieramy
 * @param x szukana wartość w drzewie
 * @return lista węzłów po drodze (bez ostatniego)
 */
static vector<node_ptr> getNodesAlongWay(int index, int x){
    vector<node_ptr> gatheredNodes;
    int l = 0, r = 15, current;
    node_ptr curr_Node = roots[index];
    while(l + 1 != r){
        gatheredNodes.push_back(curr_Node);
        if(x >= avg(l, r)){
            l = avg(l, r);
            curr_Node = curr_Node->right;
        }else{
            r = avg(l, r);
            curr_Node = curr_Node->left;
        }
    }
    return gatheredNodes;
}
// funkcja debugowa rysujaca drzewo
static void printNode(const string prefix, const node_ptr node, bool isLeft){
    if(node != nullptr){
        cout << prefix << (isLeft ? "├──" : "└──" ) << node->value << std::endl;
        printNode( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printNode( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}
void printDrzewo(const node_ptr &node){
    printNode("", node, false);    
}

void pushBack(int v){
    int l = 0, p = 15, index = roots.size();
    bool following;
    node_ptr last;
    if(roots.empty()){
        following = false;
        last = nullptr;
    }else{
        following = true;
        last = roots.back();
    }
    node_ptr previous = make_shared<Node>(nullptr, nullptr, index);
    roots.push_back(previous);
    while(l + 1 != p){
        node_ptr new_node = make_shared<Node>(nullptr, nullptr, index);
        if(v >= avg(l, p)){
            l = avg(l, p); 
            previous->right = new_node;
            if(following){
                previous->left = last->left;
                if(last->right != nullptr)
                    last = last->right;
                else following =  false;
            }else previous->left = nullptr;
            previous = new_node;
        } else {
            p = avg(l, p);
            previous->left = new_node;
            if(following){
                previous->right = last->left;
                if(last->left != nullptr)
                    last = last->left;
                else following =  false;
            }else previous->right = nullptr;
            previous = new_node;
        }
    }
}

void init(const vector<int> &x){
    int x_size = x.size();
    for(int i = 0; i < x_size; i++)
        pushBack(x[i]);
    printDrzewo(roots.back());
}

int prevInRange(int index, int lo, int hi){
    int m = -1;
    vector<node_ptr> lo_nodes = getNodesAlongWay(index, lo);
    vector<node_ptr> hi_nodes = getNodesAlongWay(index, hi);
    for(int i = lo_nodes.size(); i > 0 && lo_nodes[i] != hi_nodes[i]; i--){
        if(lo_nodes[i]->right != nullptr)
            m = (lo_nodes[i]->right->value > m) ? lo_nodes[i]->right->value : m;
        if(hi_nodes[i]->left != nullptr)
            m = (lo_nodes[i]->left->value > m) ? lo_nodes[i]->left->value : m;
    }
    return m;
}

void done(){
    roots.clear();
}