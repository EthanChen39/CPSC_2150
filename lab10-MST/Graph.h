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
#include <list>

using namespace std;

class Edges{
public:
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

struct edgesCmr{
    bool operator()(const Edges& e1, const Edges& e2){
        return e1.weight > e2.weight;
    }
};


class Vertex{
public:
    /**
     * Constructor with certain serial number
     * @param num, serialNumber
     */
    Vertex(int num){
        serialNumber = num;
    }
    /**
     * Default constructor
     */
    Vertex(){
        Vertex(-1);
    }

protected:
    //Data members
    int serialNumber;
    list<Vertex*> adjList;
    friend class Graph;
};

class Graph {
public:
    //Constructors
    Graph(int size);
    Graph();
    int getNumberOfEdges() const;
    void buildSparseUWGFromFile(const string& fileName);
    void reverseKruskal(const string& fileName);
    void printAdjList();
    void printEdges();
    int getTotalDistance();


private:
    //Private functions
    //void isConnected(int startVertex, int goalVertex);
    bool isConnected(int startVertex, int goalVertex);
    int getFirstVertexFromFile(const string& line);
    int getSecondVertexFromFile(const string& line);
    int getWeightFromFile(const string& line);

    //Data members
    Vertex* vertices;
    vector<Vertex*> tempVertices;
    Edges* edges;
    int countE;
    int size;
    int totalDistance;
};


#endif //LAB9_GRAPH_H
