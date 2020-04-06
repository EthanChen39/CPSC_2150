/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * AVL.cpp: This program is to test the functionality of AVL class
*/


#include "AVL.h"



template<typename T>
BSTNode<T>* AVL<T>::insertHelper(BSTNode<T> *r, const T &target) {
    //If the root is null
    if(r == nullptr){
        r = new BSTNode<T>(target);
        return r;
    }
    //Traverse the tree and find the right spot
    if(target < r->element) r->left = insertHelper(r->left, target);
    else r->right = insertHelper(r->right, target);
    //Perform AVL tree feature
    //Rotate certain node if necessary
    r->height = max(getHeightHelper(r->left), getHeightHelper(r->right)) + 1;
    int skewness = r == nullptr ? 0 : getHeightHelper(r->left) - getHeightHelper(r->right);
    if(skewness > 1 && target < r->left->element) return rightRotate(r);
    if(skewness < -1 && target > r->right->element) return leftRotate(r);
    if(skewness > 1 && target > r->left->element) return leftRightRotate(r);
    if(skewness < -1 && target < r->right->element) return rightLeftRotate(r);
    return r;

}

/**
 * Perform right rotation on a root
 * @tparam T
 * @param r root
 * @return
 */
template<typename T>
BSTNode<T>* AVL<T>::rightRotate(BSTNode<T>* r){
    BSTNode<T>* newRoot = r->left;
    BSTNode<T>* temp = newRoot->right;
    newRoot->right = r;
    r->left = temp;
    r->height = max(getHeightHelper(r->left), getHeightHelper(r->right)) + 1;
    newRoot->height = max(getHeightHelper(newRoot->left), getHeightHelper(newRoot->right)) + 1;
    return newRoot;
}

/**
 * Perform left rotation on a root
 * @tparam T
 * @param r root
 * @return
 */
template<typename T>
BSTNode<T>* AVL<T>::leftRotate(BSTNode<T> *r) {
    BSTNode<T>* newRoot = r->right;
    BSTNode<T>* temp = newRoot->left;
    newRoot->left = r;
    r->right = temp;
    r->height = max(getHeightHelper(r->left), getHeightHelper(r->right)) + 1;
    newRoot->height = max(getHeightHelper(newRoot->left), getHeightHelper(newRoot->right)) + 1;
    return newRoot;
}

/**
 * Perform right left rotation
 * @tparam T
 * @param r, root of the tree
 * @return
 */
template<typename T>
BSTNode<T>* AVL<T>::rightLeftRotate(BSTNode<T> *r) {
    r->right = rightRotate(r->right);
    return leftRotate(r);
}

/**
 * Perform left right rotation
 * @tparam T
 * @param r, root of the tree
 * @return
 */
template<typename T>
BSTNode<T>* AVL<T>::leftRightRotate(BSTNode<T> *r) {
    r->left = leftRotate(r->left);
    return rightRotate(r);
}

template<typename T>
void AVL<T>::insert(const T &element) {
    BSTNode<T>* temp = BST<T>::root;
    BST<T>::root = insertHelper(temp, element);
}


/**
 * Get the height of the tree with the given node
 * @tparam T
 * @param r, root
 * @return height of the tree with the given node
 */
template<typename T>
int AVL<T>::getHeightHelper(const BSTNode<T>* r) {
    if(r == nullptr) return 0;
    return r->height;
}

template<typename T>
int AVL<T>::height() {
    return getHeightHelper(BST<T>::root);
}

template<typename T>
AVL<T>::AVL(): BST<T>() {

}

template<typename T>
int AVL<T>::getSkewness(BSTNode<T> *r) {
    if(r == nullptr) return 0;
    return getHeightHelper(r->left) - getHeightHelper(r->right);
}

template<typename T>
void AVL<T>::deleteByCopying(const T &target) {
    //Calling the helper function
    BSTNode<T>* node = BST<T>::root;
    BST<T>::root = deleteByCopyingHelper(node, target);
}

template<typename T>
BSTNode<T>* AVL<T>::deleteByCopyingHelper(BSTNode<T> *r, const T &target) {
    if(r == nullptr){
        cout << "Element /"<< target << "/ is Not Found" << endl;
        return r;}
    //Traver the tree and find the target element
    if(r->element > target) r->left = deleteByCopyingHelper(r->left, target);
    else if(r->element < target) r->right = deleteByCopyingHelper(r->right, target);
    else{
        if((r->left == nullptr) || (r->right == nullptr)){
            BSTNode<T>* temp = r->left ? r->left : r->right;
            if(temp == nullptr){
                temp = r;
                r = nullptr;
            }else *r = *temp;

            delete temp;

        }else {
            //If there are two child
            BSTNode<T> *minNode = r->right;
            //Find the right-most node in the left subtree
            while (minNode->left != nullptr) minNode = minNode->left;
            r->element = minNode->element;
            //Delete the copied-node
            r->right = deleteByCopyingHelper(r->right, minNode->element);
        }
    }

    //If there is only one node in the tree
    if(r == nullptr) return r;
    //AVL feature
    //Rotate the tree if is nesscary
    r->height = max(getHeightHelper(r->left), getHeightHelper(r->right)) + 1;
    int skewness = getSkewness(r);
    if(skewness > 1 && getSkewness(r->left) >= 0) return rightRotate(r);
    if(skewness > 1 && getSkewness(r->left) < 0) return leftRightRotate(r);
    if(skewness < -1 && getSkewness(r->right) <= 0) return leftRotate(r);
    if(skewness < -1 && getSkewness(r->right) > 0) return rightLeftRotate(r);
    return r;
}
