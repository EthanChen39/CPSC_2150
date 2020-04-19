/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * Graph.h: This program contains FOUR classes - Edges, Node, Vertex and Graph
*/

#ifndef LAB9_GRAPH_H
#define LAB9_GRAPH_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Edges{
protected:
    Edges(){
        source = -1;
        dest = -1;
        weight = -1;
    }
    int source;
    int dest;
    int weight;
    friend class Graph;
};


class Node{
public:
    Node(int n){
        serialNumber = n;
        next = nullptr;
    }
    Node(){Node(-1);}

protected:
    int serialNumber;
    Node* next;
    friend class Graph;
    friend class Vertex;
};

class Vertex{
public:
    /**
     * Constructor with certain serial number
     * @param num, serialNumber
     */
    Vertex(int num){
        serialNumber = num;
        sizeOfAdjList = 0;
        adjList = nullptr;
        next = nullptr;
    }
    /**
     * Default construcotr
     */
    Vertex(){
        Vertex(-1);
    }
    /**
     * Add node to the tail of the list
     * @param node, new node
     */
    void addNodeToAdjList(const Node* node){
        Node* newNode = new Node(node->serialNumber);
        if(adjList == nullptr){
            adjList = newNode;
        }else{
            Node* temp = adjList;
            while(temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }
    }

protected:
    //Data members
    Vertex* next;
    int serialNumber;
    int sizeOfAdjList;
    Node* adjList;
    friend class Graph;
};

class Graph {
public:
    //Constructors
    Graph(int size);
    Graph();
    int getNumberOfEdges() const;
    void printAdjList();
    void printEdgesToFile(const string& fileName);
    void makeSparseUDWG();
    void makeDenseDWG();
    void printAdjMatrix();

private:
    //Private funtions
    void generateVertices();
    void buildSparseUDWG();
    void buildDenseDWG();
    bool isContainNumber(Node* head, int serialNumber);
    //Data members
    bool isDenseGraph;
    vector<Vertex*> tempForUDWG;
    vector< vector<int> > adjMatrix;
    Vertex* vertices;
    Edges* edges;
    int countE;
    int size;
};


#endif //LAB9_GRAPH_H
