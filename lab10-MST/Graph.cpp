/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * Graph.cpp: This program implements all the function prototypes in Graph.h
*/

#include <queue>
#include <fstream>
#include <algorithm>
#include "Graph.h"


/**
 * Constructor with target size
 * @param size, size of the graph
 */
Graph::Graph(int size) {
    this->size = size;
    vertices = nullptr;
    edges = nullptr;
    countE = 0;
    totalDistance = 0;
}

/**
 * Default constructor
 */
Graph::Graph() {
    Graph(0);
    totalDistance = 0;
}


/**
 * Get the number of edges in this graph
 * @return number edges in this graph
 */
int Graph::getNumberOfEdges() const {
    return countE;
}


/**
 * Build a sparse UWG based on the input file
 * @param fileName
 */
void Graph::buildSparseUWGFromFile(const string &fileName) {

    ifstream myFile(fileName);
    string line;
    getline(myFile, line);
    try {
        size = stoi(line);
    }catch(exception& e){

    }

    tempVertices.resize(size);
    //Initialize vertices
    for (int i = 0; i < size; ++i) {
        tempVertices[i] = new Vertex(i);
    }
    //Build edges/connections
    while(getline(myFile, line)){
        int index1 = getFirstVertexFromFile(line);
        int index2 = getSecondVertexFromFile(line);
        int weight = getWeightFromFile(line);
        Vertex* v1 = tempVertices[index1];
        Vertex* v2 = tempVertices[index2];
        v1->adjList.push_back(v2);
        v2->adjList.push_back(v1);
        countE++;
    }

    edges = new Edges[countE];
    ifstream myFile2(fileName);
    getline(myFile2, line);
    int index = 0;
    while(getline(myFile2, line)){
        int index1 = getFirstVertexFromFile(line);
        int index2 = getSecondVertexFromFile(line);
        int weight = getWeightFromFile(line);
        edges[index].source = index1;
        edges[index].dest = index2;
        edges[index].weight = weight;
        index++;
    }


}

/**
 * Check whether two vertices in a graph are connected or not
 * @param startVertex, startVertex's serial number
 * @param goalVertex,
 * @return
 */
bool Graph::isConnected(int startVertex, int goalVertex) {
    bool* visited = new bool[size];
    for (int j = 0; j < size; ++j) {
        visited[j] = false;
    }
    list<Vertex*>::iterator i;
    //This method uses BFS
    queue<Vertex*> l;
    l.push(tempVertices[startVertex]);
    visited[startVertex] = true;
    while(!l.empty()){
        Vertex* temp = l.front();
        if(temp->serialNumber == goalVertex) return true;
        l.pop();
        for (i = temp->adjList.begin(); i != temp->adjList.end(); i++){
            Vertex* v = *i;
            if(!visited[v->serialNumber]){
                visited[v->serialNumber] = true;
                l.push(v);
            }
        }
    }
    delete [] visited;
    return false;
}

/**
 * Parse the string getting from the file
 * @param line
 * @return, first vertex
 */
int Graph::getFirstVertexFromFile(const string &line) {
    int index = 0;
    int result = 0;
    for (int i = 0; i < line.size(); ++i) {
        if(line[i] == ' '){
            index = i;
        }
    }
    try {
        result = stoi(line.substr(0, index));
    }catch (exception& e){

    }
    return result;
}

/**
 * Parse the string getting from the file
 * @param line
 * @return, second vertex
 */
int Graph::getSecondVertexFromFile(const string &line) {
    int first = 0;
    int second = 0;
    bool s = false;
    for (int i = 0; i < line.size(); ++i) {
        if(s && line[i] == ' '){
            second = i;
            break;
        }
        if(line[i] == ' ' && !s){
            first = i;
            s = true;
        }

    }
    second++;
    int result = 0;
    try{
        result = stoi(line.substr(first, second));
    }catch (exception& e){

    }
    return result;
}

/**
 * Parse the string getting from the file
 * @param line
 * @return, weight of the edge
 */
int Graph::getWeightFromFile(const string &line) {
    bool s = false;
    int index = 0;
    for (int i = 0; i < line.size(); ++i) {
        if(s && line[i] == ' '){
            index = i;
            break;
        }
        if(line[i] == ' ' && !s){
            s = true;
        }

    }
    index++;
    int r = 0;
    try{
        r = stoi(line.substr(index));
    }catch (exception& e){

    }
    return r;
}

/**
 * Rverse Kruskal algorithmimplementation
 * @param fileName
 */
void Graph::reverseKruskal(const string& fileName) {
    buildSparseUWGFromFile(fileName);
    int numberOfRemoval = 0;
    sort(edges, edges + countE, edgesCmr()); //ElogE
    for (int i = 0; i < countE; ++i) { // E
        //Assume the edge will be removed
        bool removed = true;
        int source = edges[i].source;
        int dest = edges[i].dest;
        Vertex* v1 = tempVertices[source];
        Vertex* v2 = tempVertices[dest];
        v1->adjList.remove(v2); // V
        v2->adjList.remove(v1);
        if(!isConnected(source, dest)){ // |V| + |E|
            v1->adjList.push_back(v2); //V
            v2->adjList.push_back(v1);
            removed = false;
        }
        if(removed){
            cout << "An Edge: <" << source << ", " <<  dest << ", " <<
            edges[i].weight << "> " << "has been removed" << endl;
            numberOfRemoval++;
            //Mark the edge as removed
            edges[i].source = -999;
        }
    }
    //Re-construct edge array
    Edges* temp = new Edges[countE - numberOfRemoval];
    int index = 0;
    for (int j = 0; j < countE; ++j) {
        if(edges[j].source != -999){
            temp[index++] = edges[j];
            totalDistance += edges[j].weight;
        }
    }
    delete edges;
    edges = temp;
    countE = countE - numberOfRemoval;
}


/**
 * Print out adjacency list
 */
void Graph::printAdjList() {
    for (int i = 0; i < tempVertices.size(); ++i) {
        Vertex* v = tempVertices[i];
        list<Vertex*>::iterator a;
        cout << v->serialNumber << ":";
        for (a = v->adjList.begin(); a != v->adjList.end(); a++) {
            cout << (*a)->serialNumber << "->";
        }
    }
}

/**
 * Print all th eedges in the graph
 */
void Graph::printEdges() {
    for (int i = 0; i < countE; ++i) {
        int source = edges[i].source;
        int dest = edges[i].dest;
        cout << "An Edge: <" << source << ", " <<  dest << ", " <<
             edges[i].weight << "> " << endl;
    }
    cout << endl;
}

/**
 * Get total distance in the graph
 * @return total distance in the graph
 */
int Graph::getTotalDistance(){
    return totalDistance;
}









