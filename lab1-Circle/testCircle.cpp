// testCircle.cpp file
// Description: This file is to test the functionality of Circle.cpp
// Author: Shixi Chen(Ethan)
// Creation date: Jan 7, 2019

#include "Circle.h"
#include "iostream"
using namespace std;
int main(){
    Circle c1(-2, 5, 10);
    Circle c2(-1, -2, 5);
    Circle c3;
    Circle c4(6, 10, 3);

    cout << "c1: ";c1.displayCircle();
    cout << "c2: ";c2.displayCircle();
    cout << "c3: ";c3.displayCircle();
    cout << "c4: ";c4.displayCircle();

    cout << "Number of circles created: " << Circle::getNumberOfCurrentCircles() << endl;
    cout << "Number of circles in the left: " << Circle::getNumberOfCirclesInLeftSid() << endl << endl;

    cout << "Change the radius of c1 from (10) to (1)." << endl;
    c1.setRadius(1);
    c1.displayCircle();
    cout << "Number of circles created: " << Circle::getNumberOfCurrentCircles() << endl;
    cout << "Number of circles in the left: " << Circle::getNumberOfCirclesInLeftSid() << endl;
}
