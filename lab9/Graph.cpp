/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * Graph.cpp: This program implements all the function prototypes in Graph.h
*/
#include <ctime>
#include <fstream>
#include "Graph.h"


/**
 * Constructor with target size
 * @param size, size of the graph
 */
Graph::Graph(int size) {
    this->size = size;
    vertices = nullptr;
    edges = nullptr;
    tempForUDWG.resize(size);
    isDenseGraph = false;
    countE = 0;
}

/**
 * Default constructor
 */
Graph::Graph() {
    Graph(0);
}

/**
 * Generate vertices and store them into a vector
 */
void Graph::generateVertices() {
    int index = 0;
    Vertex* start = new Vertex(0);
    tempForUDWG[index++] = start;
    for (int i = 1; i < size; ++i) {
        Vertex* newVertex = new Vertex(i);
        tempForUDWG[index++] = newVertex;
        start->next = newVertex;
        start = start->next;
    }
}

/**
 * Build Sparse UDWG
 */
void Graph::buildSparseUDWG() {
    srand(time(NULL));
    edges = new Edges[2*size];
    int index = 0;
    for (int i = 0; i < size; ++i) {
        Vertex* currentVertex = tempForUDWG[i];
        //Generate two random indices of vertices
        int randomIndex1 = rand() % size;
        int randomIndex2 = rand() % size;

        //Make sure these two indices are not the same, and not as same as 'i'
        while (randomIndex1 == i) randomIndex1 = rand() % size;
        while (randomIndex2 == i || randomIndex2 == randomIndex1) randomIndex2 = rand() % size;

        Vertex* vertex1 = tempForUDWG[randomIndex1];
        Vertex* vertex2 = tempForUDWG[randomIndex2];

        Node* node1 = new Node(vertex1->serialNumber);
        Node* node2 = new Node(vertex2->serialNumber);


        bool isContainVertex1 = isContainNumber(currentVertex->adjList, node1->serialNumber);
        bool isContainVertex2 = isContainNumber(currentVertex->adjList, node2->serialNumber);

        //Set up the edges

        //If the current adj-list does not contain vertex 1
        if(!isContainVertex1){
            edges[index].source = currentVertex->serialNumber;
            edges[index].dest = vertex1->serialNumber;
            edges[index].weight = rand() % 101;
            countE += 1;
            index++;
        }
        //If the current adj-list does not contain vertex 2
        if(!isContainVertex2){
            edges[index].source = currentVertex->serialNumber;
            edges[index].dest = vertex2->serialNumber;
            edges[index].weight = rand() % 101;
            countE += 1;
            index++;
        }


        //Insert these node to the current vertex's adjacent list
        if(!isContainVertex1){ currentVertex->addNodeToAdjList(node1);
        currentVertex->sizeOfAdjList++;}
        if(!isContainVertex2){ currentVertex->addNodeToAdjList(node2);
        currentVertex->sizeOfAdjList++;}



        //Add current vertex as a node to vertex1 and vertex2
        Node* currentNode = new Node(currentVertex->serialNumber);
        bool isVertex1ContainsCurrentNode = isContainNumber(vertex1->adjList, currentNode->serialNumber);
        bool isVertex2ContainsCurrentNode = isContainNumber(vertex2->adjList, currentNode->serialNumber);
        if(!isVertex1ContainsCurrentNode){
            vertex1->addNodeToAdjList(currentNode);
            vertex1->sizeOfAdjList++;
        }
        if(!isVertex2ContainsCurrentNode){
            vertex2->addNodeToAdjList(currentNode);
            vertex2->sizeOfAdjList++;
        }


    }
}

/**
 * Build dense DWG
 */
void Graph::buildDenseDWG() {
    isDenseGraph = true;
    adjMatrix.resize(size);
    //Assign weights to the edges
    //Assume edges have the worst case
    edges = new Edges[size * (size - 1)];
    int index = 0;
    for (int i = 0; i < size; ++i) {
        adjMatrix[i].resize(size);
        for (int j = 0; j < size; ++j) {
            int r = rand() % 4;
            bool ran = r == 0 || r == 1 || r == 2;
            if(j == i || !ran){
                adjMatrix[i][j] = 0;
            }else{
                    adjMatrix[i][j] = 1;
                    edges[index].source = i;
                    edges[index].dest = j;
                    edges[index].weight = rand() % 101;
                    index++;
                    countE++;

            }
        }
    }

}

/**
 * Get the number of edges in this graph
 * @return number edges in this graph
 */
int Graph::getNumberOfEdges() const {
    return countE;
}

/**
 * Print adj-List of this graph
 */
void Graph::printAdjList() {
    if(isDenseGraph){
        cout << "Adjacent list did not generated for denseDWG." << endl;
        return;
    }

    for (int i = 0; i < tempForUDWG.size(); ++i) {
        cout << tempForUDWG[i]->serialNumber << ": ";
        Node* head = tempForUDWG[i]->adjList;
        Node* tempHead = head;
        while(tempHead != nullptr){
            if(tempHead->next == nullptr)
                cout << tempHead->serialNumber;
            else
                cout << tempHead->serialNumber << "->";
            tempHead = tempHead->next;
        }
        cout << endl;
    }
}


/**
 * Print all the edges to the gievn file path
 * @param fileName
 */
void Graph::printEdgesToFile(const string& fileName) {
    ofstream myFile;
    myFile.open(fileName);
    myFile << size << endl;
    if(myFile.is_open()) {
        for (int i = 0; i < countE; ++i) {
            Edges e = edges[i];
            myFile << e.source << " " << e.dest
                   << " " << e.weight << endl;
        }
        myFile.close();
    }else{
        cout << "File does not exist" << endl;
    }
}


/**
 * Check whether the adj-list contains target node
 * @param head, head of the adj-list
 * @param serialNumber, serialNumber of the number
 * @return true -> is in the list, false -> not in the list
 */
bool Graph::isContainNumber(Node *head, int serialNumber) {
    if(head == nullptr) return false;
    Node* tempHead = head;
    while(tempHead!=nullptr){
        if(tempHead->serialNumber == serialNumber) return true;
        tempHead = tempHead->next;
    }
    return false;
}


void Graph::makeSparseUDWG() {
    generateVertices();
    buildSparseUDWG();
}

void Graph::makeDenseDWG() {
    generateVertices();
    buildDenseDWG();
}

/**
 * Print out the adj-matrix
 */
void Graph::printAdjMatrix() {
    cout << "    ";
    for (int k = 1; k <= size; ++k) {
        cout << k << " ";
    }
    cout << endl;
    for (int i = 0; i < size; ++i) {
        if(i <= 8) {
            cout << i + 1 << "   ";
        }
        else{
            cout << i + 1 << "  ";
        }
        for (int j = 0; j < size; ++j) {
            if(j >= 9){
                cout << " " << adjMatrix[i][j] << " ";
            }else {
                cout << adjMatrix[i][j] << " ";
            }

        }
        cout << endl;
    }
    cout << endl;
}








