// lab3.cpp file
// Description: This file implements numPathsFromHome and hasSubsequence functions.
// Author: Shixi Chen(Ethan)
// Creation date: Jan 23, 2019

#include "iostream"

using namespace std;

int numPathsFromHome(int street, int avenue);

bool hasSubsequence(const string& T, const string& S);

int main(){
    cout << "Eric goes home: " << endl;

    int ways = numPathsFromHome(4, 2);
    cout << "Street: 4  Avenue: 2: " << ways << endl;
    cout << "Street: 3  Avenue: 8: " << numPathsFromHome(3, 8) << endl;
    cout << "Street: 4  Avenue: 7: " << numPathsFromHome(4, 7) << endl;
    cout << "Street: 2  Avenue: 6: " << numPathsFromHome(2, 6) << endl;

    cout << "--------------------------------------------" << endl;
    cout << "Subsequence: " << endl;
    //Case 1
    string a = "team";
    string b = "em";
    cout << "Is /" << b << "/ a substring of /" << a << "/ ";
    hasSubsequence(a, b)? cout <<"Yes" << endl: cout << "No" << endl;

    //Case 2
    string c = "programming";
    string d = "pin";
    cout << "Is /" << d << "/ a substring of /" << c << "/ ";
    hasSubsequence(c, d)? cout <<"Yes" << endl: cout << "No" << endl;

    //Case 3
    string e = "Hello";
    string f = "";
    cout << "Is /" << f << "/ a substring of /" << e << "/ ";
    hasSubsequence(e, f)? cout <<"Yes" << endl: cout << "No" << endl;

    //Case 4
    string g = "jhsalvaeoirjasijd";
    string h = "jzd";
    cout << "Is /" << h << "/ a substring of /" << g << "/ ";
    hasSubsequence(g, h)? cout <<"Yes" << endl: cout << "No" << endl;


}


/**
 * Gets the total number of ways to go back home.
 * @param street, a number of street
 * @param avenue, a number of avenue
 * @return the total number of ways to go back home.
 */
int numPathsFromHome(int street, int avenue){
    bool isEdge = ((street == 0) || (avenue == 0));
    if(isEdge){
        //At the edge means one route
        return 1;
    }else{
        //total number of times that get to Left edge OR Bottom edge
        return numPathsFromHome(street - 1, avenue) + numPathsFromHome(street, avenue - 1);
    }
}

/**
 * Check whether S is a substring of T or not.
 * @param T, Original string
 * @param S, target string
 * @return true -> it is a substring, false -> not a substring.
 */
bool hasSubsequence(const string& T, const string& S){
    unsigned long lastIndexOfT = T.size() - 1;
    unsigned long lastIndexOfS = S.size() - 1;
    //Base case
    if(S.empty()){
        return true;
    }else if(T.empty()){
        //Base case
        return false;
    }else{
        if(T[0] == S[0]){//If the first char are matched, then both of them -> move to the next char
            return hasSubsequence(T.substr(1, lastIndexOfT), S.substr(1, lastIndexOfS));
        }else{
            //Only move the T string
            return hasSubsequence(T.substr(1, lastIndexOfT), S);
        }
    }
}