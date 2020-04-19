#include <iostream>
#include <queue>
#include <vector>
#include "Node.h"

using namespace std;


void printTrie(Node* root);
void printTrieHelper(Node* root, string& test);
void frequency(const string& s, vector<Node*>& result);
Node* makeHuffmanTree(const string& s);

int sizeOfList = 0;

int main(){
    string a = "PROGRAMMING";
    cout << "word: " << a << endl;
    Node* root1 = makeHuffmanTree(a);
    printTrie(root1);

    cout << "––––––––––––––––––––––––––––––––––––––––––" << endl;

    string b = "EYEWITNESSNEWS";
    ::sizeOfList = 0;
    cout << "word: " << b << endl;
    Node* root2 = makeHuffmanTree(b);
    printTrie(root2);

    cout << "––––––––––––––––––––––––––––––––––––––––––" << endl;

    string c = "HOWAREYOU";
    ::sizeOfList = 0;
    cout << "word: " << c << endl;
    Node* root3 = makeHuffmanTree(c);
    printTrie(root3);

    cout << "––––––––––––––––––––––––––––––––––––––––––" << endl;

    string d = "GOODWEATHER";
    ::sizeOfList = 0;
    cout << "word: " << d << endl;
    Node* root4 = makeHuffmanTree(d);
    printTrie(root4);

    return 0;
}

Node* makeHuffmanTree(const string& s){
    priority_queue<Node*, vector<Node*>, comparator> list;
    vector<Node*> occurrence(52);

    frequency(s, occurrence);

    for (int j = 0; j < ::sizeOfList; ++j) {
        cout << occurrence[j]->letter << " " << occurrence[j]->occurrence << "    ";
    }
    cout << endl;

    for (int i = 0; i < ::sizeOfList; ++i) {
        list.push(occurrence[i]);
    }

    while(list.size() > 1){
        int leftOccurrence = list.top()->occurrence;
        Node* left = list.top();list.pop();

        int rightOccurrence = list.top()->occurrence;
        Node* right = list.top();list.pop();

        int sum = leftOccurrence + rightOccurrence;

        Node* internalNode = new Node(sum);

        internalNode->left = right;
        internalNode->right = left;

        list.push(internalNode);
    }
    Node* result = list.top();
    list.pop();

    return result;
}

void printTrie(Node* root){
    string temp = "";
    printTrieHelper(root, temp);
}

void printTrieHelper(Node* root, string& test){
    if(root == nullptr) return;
    if(root->left == nullptr && root->right == nullptr){
        cout << root->letter  << ": " << test << endl;
        return;
    }
    test += '0';
    printTrieHelper(root->left, test);
    test = test.substr(0, test.length() - 1);
    test+= '1';
    printTrieHelper(root->right, test);
    test = test.substr(0, test.length() - 1);
}

void frequency(const string& s, vector<Node*>& result) {
    int *temp = new int[26];
    for (int j = 0; j < 2; ++j) {
        char l = (j == 0 ? 'a' : 'A');
        for (int i = 0; i < 26; i++) {
            temp[i] = 0;
        }
        for (char i : s) {
            int index = i - l;
            temp[index]++;
        }
        for (int i = 0; i < 26; ++i) {
            if (temp[i] != 0) {
                char letter = (char) (l + i);
                Node* a = new Node(letter, temp[i]);
                result[::sizeOfList] = a;
                ::sizeOfList++;
                continue;
            }
        }
    }
    delete [] temp;
}