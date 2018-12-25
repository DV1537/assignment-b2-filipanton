#ifndef FIGURE_H
#define FIGURE_H
#include "Shape.h"
#include <cmath>
#include <iostream>
struct boundingBoxCorners
{
    float xTopLeft;
    float yTopLeft;
    float xBottomRight;
    float yBottomRight;

};

class Figure
{
private:
    int counter;
    int numberOfShapes;
    Shape **Shapes = new Shape*[5];
public:
    Figure(int numberOfLines);
    void addShape(Shape *s);
    boundingBoxCorners getBoundingBox();
    Shape** getClosest(Shape *location, int n); 
    void sortDistance(Shape *location, int n);
    Shape** getShapes()
    {
        return Shapes;
    }

};


#endif