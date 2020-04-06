/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * AVL.h: This program contains AVL class. It inherites
*/

#include "BST.h"


#ifndef AVL_TREE_AVL_H
#define AVL_TREE_AVL_H

template<typename T>
class AVL : public BST<T>{
public:
    AVL();
    void insert(const T& element);
    int height();
    void deleteByCopying(const T& target);




private:

    int getSkewness(BSTNode<T>* r);
    BSTNode<T>* insertHelper(BSTNode<T>* r, const T& target);
    BSTNode<T>* rightRotate(BSTNode<T>* r);
    BSTNode<T>* leftRotate(BSTNode<T>* r);
    BSTNode<T>* leftRightRotate(BSTNode<T>* r);
    BSTNode<T>* rightLeftRotate(BSTNode<T>* r);
    int getHeightHelper(const BSTNode<T>* r);
    BSTNode<T>* deleteByCopyingHelper(BSTNode<T>* node, const T& target);

};


#endif //AVL_TREE_AVL_H
