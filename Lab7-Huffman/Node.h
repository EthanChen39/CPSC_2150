//
// Created by Shixi Chen on 2020-03-05.
//
#include <iostream>
#ifndef LAB7_NODE_H
#define LAB7_NODE_H


class Node {
public:
    Node(){
        letter = '$';
        occurrence = 0;
        left = right = nullptr;
    }

    Node(char l, int o){
        letter = l;
        occurrence = o;
        left = right = nullptr;
    }

    Node(int o){
        letter = '$';
        occurrence = o;
        left = right = nullptr;
    }

    Node(const Node& node){
        this->occurrence = node.occurrence;
        this->letter = node.letter;
        std::cout << "IN" << std::endl;
        left = node.left;
        right = node.right;

    }

    Node& operator= (const Node& node){
        this->occurrence = node.occurrence;
        this->letter = node.letter;
        left = node.left;
        right = node.right;
        return *this;
    }


    char letter;
    int occurrence;
    Node* left;
    Node* right;
};

struct comparator{
    bool operator()(const Node* r, const Node* l){
        return r->occurrence >= l->occurrence;
    }
};







#endif //LAB7_NODE_H
