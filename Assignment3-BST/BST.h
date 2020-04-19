// BST.h file
// Description: This file is to implement all the function prototypes of binary search tree.
// Author: Shixi Chen(Ethan)
// Creation date: March 1, 2019

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

template<typename T>
class BST {
public:
    BST<T>();
    BST<T>(BSTNode<T>* node);
    BST<T>(const BST<T>& tree);
    ~BST<T>();
    void insert(const T &element);
    void printInOrder();
    string getPostOrder();
    void deleteByCopying(const T& target);
    int getHeight();
    BST<T>* merge(const BST<T>& bst1, const BST<T>& bst2);

private:
    BSTNode<T>* copyTree(BSTNode<T>* r, BSTNode<T>* newRoot);

    //These functions are helper functions
    void getPostOrderHelper(string& result, BSTNode<T>* node);
    void insertNodeFromAnotherTree(BST<T>& tree, BSTNode<T>* root2);
    int getHeightHelper(const BSTNode<T>* r);
    void printInOrderHelper(const BSTNode<T>* node);
    BSTNode<T>* deleteByCopyingHelper(BSTNode<T>* node, const T& target);
    BSTNode<T>* mergeHelper(BSTNode<T>* n1, BSTNode<T>* n2);

    //AVL features
    int getSkewness(BSTNode<T>* r);
    BSTNode<T>* insertHelper(BSTNode<T>* r, const T& target);
    BSTNode<T>* rightRotate(BSTNode<T>* r);
    BSTNode<T>* leftRotate(BSTNode<T>* r);
    BSTNode<T>* leftRightRotate(BSTNode<T>* r);
    BSTNode<T>* rightLeftRotate(BSTNode<T>* r);

    //Data memeber
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
      BSTNode<T>* temp = root;
     root = insertHelper(temp, element);
}
template<typename T>
int BST<T>::getSkewness(BSTNode<T> *r) {
    if(r == nullptr) return 0;
    return getHeightHelper(r->left) - getHeightHelper(r->right);
}

template<typename T>
void BST<T>::insertNodeFromAnotherTree(BST<T> &tree, BSTNode<T> *root2) {
    if(root2 == nullptr) return;
    insertNodeFromAnotherTree(tree,root2->left);
    tree.insert(root2->element);
    insertNodeFromAnotherTree(tree, root2->right);

}

template<typename T>
BSTNode<T>* BST<T>::insertHelper(BSTNode<T> *r, const T &target) {
    //If the root is null
    if(r == nullptr){
        r = new BSTNode<T>(target);
        return r;
    }
    //Traverse the tree and find the right spot
    if(target < r->element) r->left = insertHelper(r->left, target);
    else r->right = insertHelper(r->right, target);
    //Perform AVL tree feature
    //Rotate certain node if nesscary
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
BSTNode<T>* BST<T>::rightRotate(BSTNode<T>* r){
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
BSTNode<T>* BST<T>::leftRotate(BSTNode<T> *r) {
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
BSTNode<T>* BST<T>::rightLeftRotate(BSTNode<T> *r) {
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
BSTNode<T>* BST<T>::leftRightRotate(BSTNode<T> *r) {
    r->left = leftRotate(r->left);
    return rightRotate(r);
}




template<typename T>
void BST<T>::printInOrder() {
    printInOrderHelper(root);
}

template<typename T>
string BST<T>::getPostOrder() {
    string result = "";
    getPostOrderHelper(result, root);
   return result;
}
/**
 * Travese in post order to get post order expression
 * @tparam T
 * @param result
 * @param node
 */
template<typename T>
void BST<T>::getPostOrderHelper(string& result, BSTNode<T> *node) {
    if(node == nullptr) return;
    getPostOrderHelper(result, node->left);
    getPostOrderHelper(result, node->right);
    result.push_back(node->element);
}

template<typename T>
void BST<T>::printInOrderHelper(const BSTNode<T> *node) {
    if (node == NULL) {
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
 * Get the height of the tree with the given node
 * @tparam T
 * @param r, root
 * @return height of the tree with the given node
 */
template<typename T>
int BST<T>::getHeightHelper(const BSTNode<T>* r) {
    if(r == nullptr) return 0;
    return r->height;
}

/**
 * Delete a target element in the BST
 * @tparam T, data type
 * @param target element
 */
template<typename T>
void BST<T>::deleteByCopying(const T &target) {
    //Calling the helper function
    BSTNode<T>* node = root;
    root = deleteByCopyingHelper(node, target);

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

/**
 * Merge two BSTs
 * @tparam T, data type
 * @param bst1
 * @param bst2
 * @return a merged-BST
 */
template<typename T>
BST<T>* BST<T>::merge(const BST<T> &bst1, const BST<T> &bst2) {
    BST<T>* result = new BST<T>();
    BSTNode<T>* root1 = bst1.root;
    BSTNode<T>* root2 = bst2.root;
    BSTNode<T>* newRoot = new BSTNode<T>();
    getHeightHelper(root1) > getHeightHelper(root2) ?
    newRoot = copyTree(root1, newRoot) : newRoot = copyTree(root2, newRoot);
    result->root = newRoot;
    insertNodeFromAnotherTree(*result, root2);
    return result;
}

/**
 * Merge two BSTs
 * @tparam T, data type
 * @param n1, root from the first BST
 * @param n2, root from the second BST
 * @return, new root of the new tree
 */
template<typename T>
BSTNode<T> *BST<T>::mergeHelper(BSTNode<T> * n1, BSTNode<T> * n2) {
    if(n1 == nullptr && n2 == nullptr) return nullptr;
    T val1 = n1 != nullptr ? n1->element : 0;
    T val2 = n2 != nullptr ? n2->element : 0;
    BSTNode<T>* newNode = new BSTNode<T>(val1 + val2);
    newNode->left = mergeHelper(n1 != nullptr ? n1->left : nullptr, n2 != nullptr ? n2->left : nullptr);
    newNode->right = mergeHelper(n1 != nullptr ? n1->right : nullptr, n2 != nullptr ? n2->right : nullptr);

    return newNode;
}



#endif //ASSIGNMENT_3_BST_H
