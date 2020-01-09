// Circle.cpp file
// Description: This file implements all the prototypes in Circle.h file
// Author: Shixi Chen(Ethan)
// Creation date: Jan 7, 2019

#include "Circle.h"
#include "cmath"
#include "iostream"

using namespace std;

int Circle::numberOfCircles = 0;
int Circle::numberOfCirclesInLeftSid = 0;

//Default constructor
Circle::Circle() {
    x = y = 0;
    radius = 10;
    numberOfCircles++;
}

//Destructor
Circle::~Circle() {
    delete this;
}

// Constructor to create a new circle with the given values
Circle::Circle(int x, int y, double radius) {
    this->x = x;
    this->y = y;
    setRadius(radius);
    numberOfCircles++;
}

// Getters that return information about the circle
int Circle::getX() const{
    return x;
}

int Circle::getY() const{
    return y;
}

double Circle::getRadius() const{
    return radius;
}

// Setters that change the values of the attributes
void Circle::translateXY(int x, int y) {
    this->x = x;
    this->y = y;

    //Check new Circle's coordinate
    if(abs(radius) < abs(x)){
        numberOfCirclesInLeftSid++;
    }
}

void Circle::setRadius(double r) {
    if(r >= 0){
        radius = r;
    }else{
        radius = 10;
    }
    //Check new Circle's coordinate
    if(abs(radius) < abs(x)){
        numberOfCirclesInLeftSid++;
    }
}

// Compute and return the area of "this" circle
double Circle::computeArea() const{
    return M_PI * pow(radius, 2);
}

// Display method that prints the circle's coordinate and radius
void Circle::displayCircle() const{
    cout << "[x = " << x << ", y = " << y << ", radius = " << radius << "]" << endl;
}

//Check whether two circles are intersected
bool Circle::intersect(const Circle &c2) {
    double distance = sqrt(pow(x - c2.x, 2) + pow(y - c2.y, 2));
    return (distance <= radius + c2.radius);
}

//Return the number of circle
int Circle::getNumberOfCurrentCircles() {
    return numberOfCircles;
}

//count the circles which are in left side of y-axis
int Circle::getNumberOfCirclesInLeftSid() {
    return numberOfCirclesInLeftSid;
}



