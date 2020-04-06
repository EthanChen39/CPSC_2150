#include <iostream>
#include "BST.h"

using namespace std;


int main(){
    BST<int> t;
    t.insert(1);
    t.insert(0);
    t.insert(-2);
    t.insert(34);
    t.insert(2);
    t.insert(52);
    t.printInOrder();
    cout << endl;
    t.printPreOrder();
    cout << endl;

    t.deleteByCopying(2);
    t.deleteByCopying(52);
    t.printInOrder();
    cout << endl;
    t.deleteByCopying(34);
    t.printPreOrder();
    cout << endl;


}