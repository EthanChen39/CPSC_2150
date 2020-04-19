// testBST.cpp file
// Description: This file contains all the test cases of BST.h class
// Author: Shixi Chen(Ethan)
// Creation date: March 1, 2019

#include "iostream"
#include "BST.h"
#include "stack"

using namespace std;

int* genData(int n);
void printList(int* list, int size);
BST<int> makeBST(int* list, int size);
template <typename T>
void printBT(BST<T> bst);
void remove(int target,BST<int> bst);
int height(BST<int>& bst);
BST<int> mergeBST(const BST<int>& bst1, const BST<int>& bst2);
string getExpression();

BST<char> infixExprTree(string infix);
BSTNode<char>* infixExprTreeHelper(BSTNode<char>* r, string infix);
BSTNode<char>* infixExprTreeHelperWithBracket(string infix);

string InfixPostfixExpr(string infix);



int main(){
    BST<int> bst1;
    BST<int> bst2;
    BST<int> bst3;
    BST<char> bst4;

    //List 1
    int size1 = 15;
    int* l1 = genData(size1);
    cout << "The List1: ";
    printList(l1, size1);


    //List 2
    int size2 = 12;
    int* l2 = genData(size2);
    cout << "The Lis2: ";
    printList(l2, size2);
    cout << endl;

//––––––––––––––––––––––––––––––––––––––––––––––––––––
    bst1 = makeBST(l1, size1);
    cout << "In-order traversal of bst1 is: ";
    printBT(bst1);

    remove(l1[size1/2], bst1);
    cout << "In-order traversal of bst1 after deleting [" << l1[size1/2] << "] is: ";
    printBT(bst1);
    cout << endl;

//––––––––––––––––––––––––––––––––––––––––––––––––––––
    bst2 = makeBST(l2, size2);
    cout << "In-order traversal of bst2 is®: ";
    printBT(bst2);


    remove(l2[size2/2], bst2);
    cout << "In-order traversal of bst2 after deleting [" << l2[size2/2] << "] is: ";
    printBT(bst2);
    cout << endl;

//––––––––––––––––––––––––––––––––––––––––––––––––––––
    bst3 = mergeBST(bst1, bst2);
    cout << "In_order traversal of bst3 is: ";
    printBT(bst3);
    cout << endl;


//––––––––––––––––––––––––––––––––––––––––––––––––––––
    cout << "The height of bst1 is " << height(bst1) << endl;
    cout << "The height of bst2 is " << height(bst2) << endl;
    cout << "The height of merged tree is " << height(bst3) << endl;

//––––––––––––––––––––––––––––––––––––––––––––––––––––
    string infix = getExpression();

    bst4 = infixExprTree(infix);
    cout << "In-order traversal of bt4 is: ";
    printBT(bst4);

    cout << "The postfix expression is: " << InfixPostfixExpr(infix) << endl;

    return 0;
}

/**
 * Generate random numbers in the list
 * @param n, range of the data, and the number of digits
 * @return
 */
int* genData(int n){
    srand(time(NULL));
    int* result = new int[n];
    for (int i = 0; i < n; ++i) {
        int randomNumber = rand() % (2 * n + 1) - n;
        result[i] = randomNumber;
    }
    return result;
}

/**
 * Print an array
 * @param list, array
 * @param size, size of the array
 */
void printList(int* list, int size){
    cout << "[";
    for (int i = 0; i < size; ++i) {
        if(i == size - 1)
            cout << list[i];
        else
            cout << list[i] << ", ";
    }cout << "]" << endl;
}

/**
 * Make a BST base on the array
 * @param list, arrya
 * @param size, size of the array
 * @return
 */
BST<int> makeBST(int* list, int size){
    BST<int> tree;
    for (int i = 0; i < size; ++i) {
        tree.insert(list[i]);
    }
    return tree;
}

/**
 * In-order traversal
 * @tparam T
 * @param bst
 */
template <typename T>
void printBT(BST<T> bst){
    bst.printInOrder();
    cout << endl;
}

/**
 * Remove element from given BST
 */
void remove(int target,BST<int> bst){
    bst.deleteByCopying(target);
}

/**
 * get height of the BST
 * @param bst, binary search tree
 * @return
 */
int height(BST<int>& bst){
    return bst.getHeight();
}

/**
 * Merge two BST
 * @param bst1
 * @param bst2
 * @return
 */
BST<int> mergeBST(const BST<int>& bst1, const BST<int>& bst2){
    BST<int>* result = new BST<int>();
    result = result->merge(bst1, bst2);
    return *result;
}

/**
 * Get expression from the user
 * @return
 */
string getExpression(){
    string result;
    cout << "Enter an infix expression: ";
    cout << "For example: (2+(2*(3-4))/2) OR 2 - 5 * 4 / 2 + 6 : " << endl;
    getline(cin, result);
    //Trim all the space from the string
    result.erase(remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

/**
 * Convert user's input into an expression tree
 * @param infix, infix expression
 * @return
 */
BST<char> infixExprTree(string infix){
    bool hasBraket  = false;
    BSTNode<char> *root;
    for (int i = 0; i < infix.length(); ++i) {
        if(infix[i] == '(') {
            hasBraket = true;break;
        }
    }
    root = !hasBraket ? infixExprTreeHelper(nullptr, infix) : infixExprTreeHelperWithBracket(infix);
    BST<char> result(root);
    return result;
}

/**
 * This is a helper function
 * @param r, root of the tree
 * @param infix, infix expression
 * @return
 */
BSTNode<char>* infixExprTreeHelper(BSTNode<char>* r, string infix){
    if(infix.length() == 3){
        r = new BSTNode<char>(infix[1]);
        BSTNode<char>* left = new BSTNode<char>(infix[0]);
        BSTNode<char>* right = new BSTNode<char>(infix[2]);
        r->left = left;
        r->right = right;
        return r;
    }
    if(infix.length() == 1){
        BSTNode<char>* temp = new BSTNode<char>(infix[0]);
        return temp;
    }
    int index = 0;
    for (int i = 0; i < infix.length(); ++i) {
        if(infix[i] == '+' || infix[i] == '-'){
            index = i;
        }
    }
    if(index != 0) {
        string leftExpression = infix.substr(0, index);
        string rightExpression = infix.substr(++index);
        r = new BSTNode<char>(infix[--index]);
        r->left = infixExprTreeHelper(r, leftExpression);
        r->right = infixExprTreeHelper(r, rightExpression);
    }else{
        //When only * and / left in the expression
        BSTNode<char>* left = new BSTNode<char>(infix[0]);
        for (int i = 1; i < infix.length(); i += 2) {
            BSTNode<char>* operand = new BSTNode<char>(infix[i]);
            BSTNode<char>* right = new BSTNode<char>(infix[i + 1]);
            operand->left = left;
            operand->right = right;
            left = operand;
            if(r != operand) r = operand;
        }

    }

    return r;
}

/**
 * Consert infix expression into post fix
 * @param infix
 * @return
 */
string InfixPostfixExpr(string infix){
    BST<char> temp = infixExprTree(infix);
    return temp.getPostOrder();
}

/**
 * This is a helper fucntion
 * @param infix
 * @return BSTNode
 */
BSTNode<char>* infixExprTreeHelperWithBracket(string infix){
    BSTNode<char> *root = nullptr;
    stack<BSTNode<char>*> c;
    for (int i = 0; i < infix.length(); ++i) {
        if(infix[i] != '(' && infix[i] != ')'){
            BSTNode<char>* node = new BSTNode<char>(infix[i]);
            c.push(node);
        }else if(infix[i] == ')'){
            BSTNode<char>* right = c.top();c.pop();
            BSTNode<char>* operand = c.top();c.pop();
            BSTNode<char>* left = c.top();c.pop();
            operand->left = left;
            operand->right = right;
            c.push(operand);
            root = operand;
        }
    }
    if(c.size() > 0){
        BSTNode<char>* right = c.top();c.pop();
        BSTNode<char>* operand = c.top();c.pop();
        BSTNode<char>* left = c.top();c.pop();
        operand->left = left;
        operand->right = right;
        root = operand;
        while(c.size()!=0) c.pop();
    }

    return root;
}