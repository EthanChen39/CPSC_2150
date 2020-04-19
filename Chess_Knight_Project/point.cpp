/*
 * Name: Shixi Chen (Ethan)
 * ID: 100304065
 * Instructor: Bita Shadgar
 * Section: CPSC 2150 - 001
 * AVL.cpp: This program implements all the functionality of point.h file.
*/

#include "point.h"

/**
 * Default constructor
 */
point::point() {
    row = 0;
    col = 0;
}

/**
 * Constructor with specify row and col
 * @param row
 * @param col
 */
point::point(int row, int col) {
    this->row = row;
    this->col = col;
}

/**
 * Get row
 * @return row
 */
int point::getRow() const {
    return row;
}

/**
 * Get column
 * @return column
 */
int point::getCol() const {
    return col;
}

/**
 * == operator overloading
 * @param p, another point
 * @return
 */
bool point::operator==(const point &p) {
    return (row == p.row && col == p.col);
}

/**
 * Assignment operator overloading
 * @param p
 * @return
 */
point &point::operator=(const point &p) {
    row = p.row;
    col = p.col;
    return *this;
}

/**
 * output stream operator overload
 * @param out
 * @param p
 * @return
 */
std::ostream& operator<<(std::ostream &out, const point &p) {
    out << "[" << p.getRow() << "," << p.getCol() << "]";
    return out;
}





