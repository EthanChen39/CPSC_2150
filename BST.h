/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * testAVL.cpp: This program is to test the functionality of AVL class
*/



#include "iostream"

using namespace std;

#ifndef ASSIGNMENT_3_BST_H
#define ASSIGNMENT_3_BST_H

template<typename T>
class BSTNode {
public:
    /**
     * Default constructor
     */
    BSTNode() {
        left = right = nullptr;
        height = 1;
    }

    /**
     * Custome constructor
     * @param ele, new element
     * @param l, left child
     * @param r, right child
     */
    BSTNode(const T &ele, BSTNode<T> *l = nullptr, BSTNode<T> *r = nullptr) {
        element = ele;
        left = l;
        right = r;
        height = 1;
    }

    /**
     * Custome constructor
     * @param ele, new element
     * @param l, left child
     * @param r, right child
     * @param height, height of this node in the BST
     */
    BSTNode(const T &ele, int height, BSTNode<T> *l = nullptr, BSTNode<T> *r = nullptr) {
        element = ele;
        left = l;
        right = r;
        this->height = height;
    }
    //Data members
    T element;
    int height;
    BSTNode<T> *left;
    BSTNode<T> *right;
};

//I have implemented AVL tree features in this BST class!

template<typename T>
class BST {
public:
    BST<T>();
    BST<T>(BSTNode<T>* node);
    BST<T>(const BST<T>& tree);
    ~BST<T>();

    virtual void insert(const T &element);
    void printInOrder();
    void printPreOrder();


    virtual void deleteByCopying(const T& target);
    int getHeight();
    void clear();

protected:
    BSTNode<T>* copyTree(BSTNode<T>* r, BSTNode<T>* newRoot);
    int getHeightHelper(BSTNode<T>* node);

    //These functions are helper functions
    BSTNode<T>* insertHelper(BSTNode<T>* r, const T& target, int heightCount);
    void printPreOrderHelper(BSTNode<T>* node);
    void printInOrderHelper(const BSTNode<T>* node);
    void clearHelper(BSTNode<T>* r);
    virtual BSTNode<T>* deleteByCopyingHelper(BSTNode<T>* node, const T& target);

    //Data member
    BSTNode<T> *root;
};

/**
 * Default constructor
 * @tparam T
 */
template<typename T>
BST<T>::BST() {
    root = nullptr;

}

/**
 * Copy another node pointer
 * @tparam T
 * @param node
 */
template<typename T>
BST<T>::BST(BSTNode<T>* node) {
    root = node;
}

/**
 *
 * @tparam T
 * @param tree
 */
template<typename T>
BST<T>::BST(const BST<T> &tree) {
    BSTNode<T>* newRoot = new BSTNode<T>();
    newRoot = copyTree(tree.root, newRoot);
    root = newRoot;
}

/**
 * Copy another tree
 * @tparam T
 * @param r, root
 * @param newRoot, copied tree's root
 * @return
 */
template<typename T>
BSTNode<T>* BST<T>::copyTree(BSTNode<T> *r, BSTNode<T>* newRoot) {
    if(r == nullptr) return r;
    BSTNode<T>* newNode = new BSTNode<T>();
    newNode->element = r->element;
    newNode->height = r->height;

    newNode->left = copyTree(r->left, newNode);
    newNode->right = copyTree(r->right, newNode);


    return newNode;
}

template<typename T>
void BST<T>::insert(const T &element) {
    root = insertHelper(root, element, 1);
}

template<typename T>
BSTNode<T> *BST<T>::insertHelper(BSTNode<T> *r, const T &target, int heightCount) {
    if(r == nullptr){
        auto* newNode = new BSTNode<T>(target);
        newNode->height = heightCount;
        return newNode;
    }
    if(r->element > target) r->left =  insertHelper(r->left, target, ++heightCount);
    else r->right =  insertHelper(r->right, target, ++heightCount);
    return r;
}




template<typename T>
void BST<T>::printInOrder() {
    printInOrderHelper(root);
}

template<typename T>
void BST<T>::printInOrderHelper(const BSTNode<T> *node) {
    if (node == nullptr) {
        return;
    }
    printInOrderHelper(node->left);
    cout << node->element << " ";
    printInOrderHelper(node->right);
}




template<typename T>
BST<T>::~BST<T>() {

}

/**
 * Get the height of the tree with the given node
 * @return height of the tree with the given node
 */
template<typename T>
int BST<T>::getHeight(){
    BSTNode<T>* temp = root;
    return getHeightHelper(temp);
}




/**
 * Delete a target element in the BST
 * @tparam T, data type
 * @param target element
 */
template<typename T>
void BST<T>::deleteByCopying(const T &target) {
    root = deleteByCopyingHelper(root, target);

}

/**
 * Delete the target element in the BST
 * @tparam T, type
 * @param r, initially, it's root
 * @param target, target element
 * @return the new root of this BST
 */
template<typename T>
BSTNode<T>* BST<T>::deleteByCopyingHelper(BSTNode<T>* r, const T& target) {
    if(r == nullptr) return r;
    else if(target < r->element){
        r->left = deleteByCopyingHelper(r->left, target);
    }
    else if(target > r->element) r->right = deleteByCopyingHelper(r->right, target);
    else{
        if(root->left == nullptr){
            BSTNode<T>* temp = r->right;
            delete r;
            return temp;
        }else if(root->right == nullptr){
            BSTNode<T>* temp = root->left;
            delete r;
            return temp;
        }
        BSTNode<T>* temp = r->left;
        while(temp != nullptr && temp->right != nullptr){
            temp = temp->right;
        }
        r->element = temp->element;
        r->right = deleteByCopyingHelper(r->right, temp->element);

    }

    return r;
}

template<typename T>
int BST<T>::getHeightHelper(BSTNode<T> *node) {
    if(node == nullptr) return 0;
    return  node->height;
}

template<typename T>
void BST<T>::clear() {
    clearHelper(root);
    root = nullptr;
}

template<typename T>
void BST<T>::clearHelper(BSTNode<T>* r) {
    if(r == nullptr) return;
    clearHelper(r->left);
    clearHelper(r->right);
    delete r;
}

template<typename T>
void BST<T>::printPreOrder() {
    printPreOrderHelper(root);
}

template<typename T>
void BST<T>::printPreOrderHelper(BSTNode<T> *node) {
    if(node == nullptr) return;

    cout << node->element << " ";
    printPreOrderHelper(node->left);
    printPreOrderHelper(node->right);
}




#endif //ASSIGNMENT_3_BST_H
