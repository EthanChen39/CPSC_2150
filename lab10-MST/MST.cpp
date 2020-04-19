/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * Graph.h: This program is to test the functionality of reverse kruskal.
*/

#include "Graph.h"

using namespace std;

void ReverseKruskal(Graph& g, const string& fileName);

int main(){
    Graph g;
    string fileName;
    cout << "Please enter a file name: ";
    cin >> fileName;
    ReverseKruskal(g, fileName);

    cout << "The remaining edges are: " << endl;
    g.printEdges();


    cout << "The total distance of the MST is: " << g.getTotalDistance() << endl;


    return 0;
}

/**
 * Reverse Kruskal algorithm
 * @param g, graph
 * @param fileName
 */
void ReverseKruskal(Graph& g, const string& fileName){
    g.reverseKruskal(fileName);
}