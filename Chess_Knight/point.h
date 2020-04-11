/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * AVL.cpp: This program is contains a point class.
*/

#include <iostream>
#include <vector>

using namespace std;
#ifndef CHESSKNIGHT_POINT_H
#define CHESSKNIGHT_POINT_H

class point {
public:
    //Constructors
    point();
    point(int row, int col);

    //Getters
    int getRow() const ;
    int getCol() const;

    //Operator overloading
    bool operator==(const point& p);
    point& operator=(const point& p);
    friend std::ostream& operator<<(std::ostream& out, const point& p);
    vector<point> prev;
private:
    //Data members
    int row;
    int col;

};



#endif //CHESSKNIGHT_POINT_H
