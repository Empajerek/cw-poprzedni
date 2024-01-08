#include "prev.h"
#include <memory>
// DEBUG
#include <iostream>
#include <string>

using namespace std;

#define node_ptr shared_ptr<struct Node>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

/**
 * @struct Node
 * @brief Strukura węzła z których budujemy nasze drzewo przedziałowe
 */
struct Node {
    node_ptr left, right;
    int value;
    // konstruktor do pustego węzła z wartością
    Node(int v) : left(nullptr), right(nullptr), value(v) {}
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
    return (x >> 1) + (y >> 1);
}

/**
 * @brief Przejscie po drzewie do wierzcholka z nr x, i zebranie po drodze wszystkich wezłów
 * @param index drzewo którego indeksu zabieramy
 * @param x szukana wartość w drzewie
 * @return lista węzłów po drodze (bez pierwszego)
 */
static vector<node_ptr> getNodesAlongWay(int index, int x){
    vector<node_ptr> gatheredNodes;
    int l = INT_MIN, r = INT_MAX;
    node_ptr curr_Node = roots[index];
    while(l != r){
        if(x > avg(l, r)){
            l = avg(l, r) + 1;
            curr_Node = curr_Node->right;
        }else{
            r = avg(l, r);
            curr_Node = curr_Node->left;
        }
        if(curr_Node == nullptr)
            break;
        gatheredNodes.push_back(curr_Node);
    }
    return gatheredNodes;
}

void pushBack(int v){
    int l = INT_MIN, p = INT_MAX, index = (int) roots.size();
    node_ptr prev_in_tree;
    if(roots.empty()){
        prev_in_tree = nullptr;
    }else{
        prev_in_tree = roots.back();
    }
    node_ptr previous = make_shared<Node>(index);
    roots.push_back(previous);
    while(l != p){
        node_ptr new_node = make_shared<Node>(index);
        if(v > avg(l, p)){
            l = avg(l, p) + 1; 
            previous->right = new_node;
            if(prev_in_tree != nullptr){
                previous->left = prev_in_tree->left;
                prev_in_tree = prev_in_tree->right;
            }
        } else {
            p = avg(l, p);
            previous->left = new_node;
            if(prev_in_tree != nullptr){
                previous->right = prev_in_tree->right;
                prev_in_tree = prev_in_tree->left;
            }
        }
        previous = new_node;
    }
}

void init(const vector<int> &x){
    int x_size = (int) x.size();
    for(int i = 0; i < x_size; i++)
        pushBack(x[i]);
}

int prevInRange(int index, int lo, int hi){
    int m = -1;
    int common_node_index = 0;
    vector<node_ptr> lo_nodes = getNodesAlongWay(index, lo);
    vector<node_ptr> hi_nodes = getNodesAlongWay(index, hi);
    while(common_node_index < (int) lo_nodes.size() && common_node_index < (int) hi_nodes.size() &&
           lo_nodes[common_node_index] == hi_nodes[common_node_index]) {
        common_node_index++;
    }
    // gdy jest co sprawdzać dla wartości mniejszych
    if(common_node_index != (int) lo_nodes.size()){
        for(int i = (int) common_node_index; i < (int) lo_nodes.size() - 1; i++) {
            if (lo_nodes[i]->right != nullptr && lo_nodes[i]->right->value > m 
                && lo_nodes[i]->right != lo_nodes[i+1]) {
                    m = lo_nodes[i]->right->value;
            }
        }
        if(lo_nodes.back()->left == nullptr)
            m = MAX(m, lo_nodes.back()->value);
    }
    // gdy jest co sprawdzać dla wartości większych
    if(common_node_index != (int) hi_nodes.size()){
        for(int i = (int) common_node_index; i < (int) hi_nodes.size() - 1; i++) {
            if (hi_nodes[i]->left != nullptr && hi_nodes[i]->left->value > m
                && hi_nodes[i]->left != hi_nodes[i+1]) {
                m = hi_nodes[i]->left->value;
            }
        }
        if(hi_nodes.back()->right == nullptr)
            m = MAX(m, hi_nodes.back()->value);
    }
    // gdy obie wartości są takie same, i znaleziono tą wartość
    if(lo == hi && lo_nodes.back()->left == lo_nodes.back()->right)
        m = lo_nodes.back()->value;
    return m;
}

void done(){
    roots.clear();
    roots.resize(0);
}