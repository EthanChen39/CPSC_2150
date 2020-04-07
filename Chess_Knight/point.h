#include <iostream>
#include <vector>
using namespace std;
#ifndef CHESSKNIGHT_POINT_H
#define CHESSKNIGHT_POINT_H

class point {
public:

    point();

    point(int row, int col);



    int getRow() const ;

    int getCol() const;

    bool operator==(const point& p);

    point& operator=(const point& p);

    friend std::ostream& operator<<(std::ostream& out, const point& p);

    vector<point> prev;
private:
    int row;
    int col;

};



#endif //CHESSKNIGHT_POINT_H
