/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * testAVL.cpp: This program is to test the functionality of AVL class
*/

#include <ctime>
#include <iostream>
#include <fstream>
#include "AVL.cpp"

using namespace std;


int getInput();
void generateInputFile(int numberOfNodes, const string& fileName);
AVL<int>* BuildAVLTree(const string& fileName);
void printAVL(AVL<int>* tree);
void InsertNodeAVL(AVL<int>* tree, int node);
void DeleteNodeAVL(AVL<int>* tree, int node);
void DeleteAVLTree(AVL<int>* tree);

int main(){
    string fileName = "AVLTree.txt";
    AVL<int>* avl;
    int node;

    int n = getInput();
    generateInputFile(n, fileName);
    avl = BuildAVLTree(fileName);
    cout << "height of AVL tree is:" << avl->height() << endl;
    printAVL(avl);
    cout << endl;

    cout << "Enter a value to insert: ";
    cin >> node;
    InsertNodeAVL(avl, node);
    cout << "height of AVL tree is:" << avl->height() << endl;
    printAVL(avl);
    cout << endl;

    cout << "Enter a value to delete: " ;
    cin >> node;
    DeleteNodeAVL(avl, node);
    cout << "height of AVL tree is: " << avl->height() << endl;
    printAVL(avl);
    cout << endl;

    DeleteAVLTree(avl);
    cout << "After the tree is deleted: \n";
    printAVL(avl);



    return 0;
}

int getInput(){
    int result = -1;
    while(result < 0){
        cout << "Please enter an non-negative integer: ";
        cin >> result;
    }
    return result;
}

void generateInputFile(int numberOfNodes, const string& fileName){
    srand(time(NULL));
    ofstream myFile(fileName);
    myFile << numberOfNodes << endl;
    for (int i = 0; i < numberOfNodes; ++i) {
        int ranNum = 1000 + rand() % 4000;
        myFile << ranNum << endl;
    }
}

AVL<int>* BuildAVLTree(const string& fileName){
    AVL<int>* result = new AVL<int>();
    ifstream myFile(fileName);
    string line;
    getline(myFile, line);
    int numberOfNodes = stoi(line);
    for (int i = 0; i < numberOfNodes; ++i) {
        getline(myFile, line);
        result->insert(stoi(line));
    }
    return result;
}

void printAVL(AVL<int>* tree){
    cout << "In-Order traversal: ";
    tree->printInOrder();
    cout << endl;
    cout << "Pre-Order traversal: ";
    tree->printPreOrder();
    cout << endl;
}

void InsertNodeAVL(AVL<int>* tree, int node){
    tree->insert(node);
}

void DeleteNodeAVL(AVL<int>* tree, int node){
    tree->deleteByCopying(node);
}

void DeleteAVLTree(AVL<int>* tree){
    tree->clear();
}