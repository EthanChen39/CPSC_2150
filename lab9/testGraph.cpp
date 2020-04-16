/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * testGraph.cpp: This program is to test the functionality of Graph class
*/
#include <iostream>
#include "Graph.h"
#include <ctime>
#include <climits>

using namespace std;

Graph makeSparseUDWG(int size);
Graph makeDenseDWG(int size);
void printGraph(Graph& UWG, const string& fileName);


int main(){
    //Exercise 1
    srand(time(NULL));
      int n1 = 10 + rand() % 21;
    Graph sparseUDWG = makeSparseUDWG(n1);
    cout << "Size of the sparseUDWG is: " << n1 << endl;
    cout << "Number of edges: " << sparseUDWG.getNumberOfEdges() << endl;
    sparseUDWG.printAdjList();
    

    cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––" << endl;

    //Exercise 2
    n1 = 10 + rand() % 21;
    Graph denseDWG = makeDenseDWG(n1);
    cout << "Number of edges for denseDWG: " << denseDWG.getNumberOfEdges() << ", which is greater than "
    << (n1 * (n1 - 2)) / 2 << endl;
    denseDWG.printAdjMatrix();


    //Exercise 3
    Graph sparseUDWG2;
    string fileName;
    cout << "Please enter your file name: ";
    cin >> fileName;
    printGraph(sparseUDWG2, fileName);

    return 0;
}

/**
 * Make sparse UDWG
 * @param size, size of the graph
 * @return, a graph with specified size
 */
Graph makeSparseUDWG(int size){
    Graph result(size);
    result.makeSparseUDWG();
    return result;
}

/**
 * Make dense DWG
 * @param size, size of the graph
 * @return a graph with specified size
 */
Graph makeDenseDWG(int size){
    Graph result(size);
    result.makeDenseDWG();
    return result;
}

/**
 * Print the target graph to the target file
 * @param UWG
 * @param fileName
 */
void printGraph(Graph& UWG, const string& fileName){
    //Get the number of node from the file name
    string temp;
    bool end = false;
    string fileNameCopy = fileName;
    int numberOfNode = INT_MAX;
    while(numberOfNode == INT_MAX){

    for (int i = (int)fileNameCopy.size() - 1; i >= 0; --i) {
        if(isdigit(fileNameCopy[i]) && !end){
            temp.push_back(fileNameCopy[i]);
            end = true;
        }
        if(!isdigit(fileNameCopy[i]) && end){
            temp.push_back(fileNameCopy[i+1]);
            break;
        }
    }
    for (int j = 0; j < temp.size()/2; ++j) {
        char t = temp[j];
        temp[j] = temp[temp.size() - j - 1];
        temp[temp.size() - j - 1] = t;
    }
    
    try{
        numberOfNode = stoi(temp);
    }catch(exception& e){
        cout << "Format of the file name is incorrect." << endl;
        cout << "E.g: sparse25.txt" << endl;
        cin >> fileNameCopy;
    }
    }
    Graph g(numberOfNode);
    g.makeSparseUDWG();
    g.printEdgesToFile(fileNameCopy);
}
