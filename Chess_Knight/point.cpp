#include "point.h"

point::point() {
    row = 0;
    col = 0;
}

point::point(int row, int col) {
    this->row = row;
    this->col = col;
}


int point::getRow() const {
    return row;
}

int point::getCol() const {
    return col;
}

bool point::operator==(const point &p) {
    return (row == p.row && col == p.col);
}

point &point::operator=(const point &p) {
    row = p.row;
    col = p.col;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const point &p) {
    out << "[" << p.getRow() << "," << p.getCol() << "]";
    return out;
}





