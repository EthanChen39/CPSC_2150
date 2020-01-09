// Circle.h file
// Description: This class models a circle
// Author: Shixi Chen(Ethan)
// Creation date: Jan 7, 2019

#ifndef LAB1_CIRCLE_H
#define LAB1_CIRCLE_H


class Circle {
private:
    int x;
    int y;
    double radius;
    static int numberOfCircles;
    static int numberOfCirclesInLeftSid;
public:
    //Part A

    //Default constructor
    Circle();
    //Destructor
    ~Circle();
    // Constructor to create a new circle with the given values
    Circle(int x, int y, double radius);

    // Getters that return information about the circle
    int getX() const;
    int getY() const;
    double getRadius() const;

    // Setters that change the values of the attributes
    void translateXY(int x, int y);
    void setRadius(double r);

    // Compute and return the area of "this" circle
    double computeArea() const;

    // Display method that prints the circle's coordinate and radius
    void displayCircle() const;

    //Check whether two circles are intersected
    bool intersect(const Circle& c2); // bonus

    //Part B
    static int getNumberOfCurrentCircles();
    static int getNumberOfCirclesInLeftSid(); //Bonus
};

#endif //LAB1_CIRCLE_H
