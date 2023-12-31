#include "prev.h"
#include <memory>
// DEBUG
#include <iostream>
#include <string>

using namespace std;

#define node_ptr shared_ptr<struct Node>

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

struct Node {
    node_ptr left, right;
    int value;
    Node(node_ptr l, node_ptr r, int v) : left(l), right(r), value(v) {}
};

static void printNode(const string prefix, const node_ptr node, bool isLeft){
    if( node != nullptr ){
        cout << prefix << (isLeft ? "├──" : "└──" ) << node->value << std::endl;
        printNode( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printNode( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

static void printDrzewo(const node_ptr &node){
    printNode("", node, false);    
}

static vector<node_ptr> roots;

void pushBack(int v){
    
    int l = 0, p = 15
    
    , index = roots.size();
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
}