// BST.h file
// Description: This file is to implement Hash class.
// Author: Shixi Chen(Ethan)
// Creation date: March 12, 2020

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

#ifndef LAB8_HASH_H
#define LAB8_HASH_H

class Hash{
public:
    Hash(const string& fileName){
        this->fileName = fileName;
    }

    int stringLengthCollisions();
    int firstCharacterCollisions();
    int additiveCollisions();
    int myMystery();
    int bonus();


private:
    const int SIZE = (int)pow(2, 16);
    vector<int> hashTable = vector<int>(SIZE);
    string fileName;
};

int Hash::stringLengthCollisions() {
    string line;
    fstream myFile(fileName);
    if(myFile.is_open()){
        while(getline(myFile, line)){
            int length = (int)line.length();
            int index = length % SIZE;
            hashTable[index]++;
        }
    }
    myFile.close();
    int max = hashTable[0];
    int min = hashTable[0];
    for (int i = 0; i < hashTable.size(); ++i) {
        if(hashTable[i] > max){
            max = hashTable[i];
        }
        if(hashTable[i] < min){
            min = hashTable[i];
        }
    }
    hashTable.clear();
    hashTable.resize(SIZE);
    return max - min;
}


int Hash::firstCharacterCollisions() {
    string line;
    fstream myFile(fileName);
    if(myFile.is_open()){
        while(getline(myFile, line)){
            int firstChar = line[0];
            int index = firstChar % SIZE;
            hashTable[index]++;
        }
    }
    myFile.close();
    int max = hashTable[0];
    int min = hashTable[0];
    for (int i = 0; i < hashTable.size(); ++i) {
        if(hashTable[i] > max){
            max = hashTable[i];
        }
        if(hashTable[i] < min){
            min = hashTable[i];
        }
    }
    hashTable.clear();
    hashTable.resize(SIZE);
    return max - min;
}

int Hash::additiveCollisions() {
    string line;
    fstream myFile(fileName);
    if(myFile.is_open()){
        while(getline(myFile, line)){
            int sum = 0;
            for (int i = 0; i < line.length(); ++i) {
                sum += (int)line[i];
            }
            int index = sum % SIZE;
            hashTable[index]++;
        }
    }
    myFile.close();
    int max = hashTable[0];
    int min = hashTable[0];
    for (int i = 0; i < hashTable.size(); ++i) {
        if(hashTable[i] > max){
            max = hashTable[i];
        }
        if(hashTable[i] < min){
            min = hashTable[i];
        }
    }
    hashTable.clear();
    hashTable.resize(SIZE);
    return max - min;
}

int Hash::myMystery() {
    string line;
    fstream myFile(fileName);
    if(myFile.is_open()){
        while(getline(myFile, line)){
            int sum = 0;
            for (int i = 0; i < line.length(); ++i) {
                sum += pow((int)line[i], 2);
            }
            int index = sum % SIZE;
            hashTable[index]++;
        }
    }
    myFile.close();
    int max = hashTable[0];
    int min = hashTable[0];
    for (int i = 0; i < hashTable.size(); ++i) {
        if(hashTable[i] > max){
            max = hashTable[i];
        }
        if(hashTable[i] < min){
            min = hashTable[i];
        }
    }
    hashTable.clear();
    hashTable.resize(SIZE);
    return max - min;
}

int Hash::bonus() {
    string line;
    fstream myFile(fileName);
    if(myFile.is_open()){
        while(getline(myFile, line)){
            const int p = 31;
            int hashValue = 0;
            int power = 1;
            for (char c : line) {
                hashValue = (hashValue + (int)(c - 'a') * power) % SIZE;
                power = (power * p) % SIZE;
            }
            hashValue = abs(hashValue);
            hashTable[hashValue]++;
        }
    }
    myFile.close();
    int max = hashTable[0];
    int min = hashTable[0];
    for (int i = 0; i < hashTable.size(); ++i) {
        if(hashTable[i] > max){
            max = hashTable[i];
        }
        if(hashTable[i] < min){
            min = hashTable[i];
        }
    }
    hashTable.clear();
    hashTable.resize(SIZE);
    return max - min;
}

#endif //LAB8_HASH_H
