// BST.h file
// Description: This file is to test Hash class.
// Author: Shixi Chen(Ethan)
// Creation date: March 12, 2020

#include "Hash.h"
using namespace std;

int main(){
    string fileName;
    cout << "Please enter the file name: ";
    cin >> fileName;
    Hash hash(fileName);
    cout << "The difference between maximum and minimum collision on the entries of " << endl;
    cout << "the hash table using the following hash function are:" << endl << endl;
    //cout << "String length: " << hash.stringLengthCollisions() << endl;
    cout << "First character: " << hash.firstCharacterCollisions() << endl;
    //cout << "Additive: " << hash.additiveCollisions() << endl;
    //cout << "Mystery: " << hash.myMystery() << endl;
    //cout << "Bonus: " << hash.bonus() << endl;
    return 0;
}