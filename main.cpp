#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "shape.h"
#include "point.h"
#include "line.h"
#include "triangle.h"
#include "polygon.h"
#include "figure.h"

struct OuputCords
{
    float *x;
    float *y;
    int arraySize;
    OuputCords(float *x, float *y, int arraySize)
    {
        this->x = x;
        this->y = y;
        this->arraySize = arraySize;
    }
};

Polygon operator+(Shape &shape, Shape &anotherShape)
    {
        float *ShapeX1 = shape.getXCord();
        float *ShapeY1 = shape.getYCord();
        int arraySize1 = shape.getArraySize();

        float *ShapeX2 = anotherShape.getXCord();
        float *ShapeY2 = anotherShape.getYCord();
        int arraySize2 = anotherShape.getArraySize();
      

        float *newShapeX = new float[arraySize1+arraySize2]{0.0};
        float *newShapeY = new float[arraySize1+arraySize2]{0.0};

        for(int i = 0; i < arraySize1; i++)
        {
            newShapeX[i] = ShapeX1[i];
            newShapeY[i] = ShapeY1[i];
        }
        for(int i = arraySize1; i < arraySize1+arraySize2; i++)
        {
            newShapeX[i] = ShapeX2[i-arraySize1];
            newShapeY[i] = ShapeY2[i-arraySize1];

        }
        int newArraySize = arraySize1+arraySize2;
        Polygon newPolygon(newShapeX, newShapeY, newArraySize);
        
        
        return newPolygon;
    }

std::ostream& operator<<(std::ostream& out, OuputCords object)
{
    for(int i = 0; i < object.arraySize ; i++)
    {
        std::cout << "(" << object.x[i] << "," << object.y[i] << ")\n";
    }

    return out;

}


void xArray(int &xArraySize, float input, int counterX, float *&arrX)
{
    if(counterX == xArraySize)
    {
        arrX[xArraySize -1] = input;
    }
    else
    {
        float *tempArray = new float[xArraySize+1]{0.0};
        for(int i = 0; i < xArraySize; i++)
        {
            tempArray[i] = arrX[i];
        }
        delete[] arrX;
        xArraySize++;
        arrX = new float[xArraySize];
        for(int x = 0; x < xArraySize; x++)
        {
            arrX[x] = tempArray[x];
        }
        arrX[xArraySize-1] = input;

    }
   
    
}


int main()
{
    std::string line;
    float input = 0;
    int numberOfLines = 0;
    std::ifstream myReadFile;

    myReadFile.open("cords");
    while(getline(myReadFile, line))
    {
        numberOfLines++;
    }
    myReadFile.close();

    std::string inputString1 = "";
    int *counters = new int[numberOfLines]{0};
    int *countersX = new int [numberOfLines]{0};
    int *countersY = new int [numberOfLines]{0};
    float *arrX = new float[1]{0.0};
    float **arraysX = new float*[numberOfLines]{arrX};
    
    float *arrY = new float[1]{0.0};
    float **arraysY = new float*[numberOfLines]{arrY};

    int *xArraySize = new int[numberOfLines]{1};
    int *yArraySize = new int[numberOfLines]{1};
    
    myReadFile.open("cords");
    for(int x = 0; x < numberOfLines; x++)
    {
        getline(myReadFile, inputString1);

        
            std::stringstream stream (inputString1);
            
            while(stream >> input)
            {
                
                
                counters[x]++;

                if(counters[x] % 2 == 0)
                {
                    countersY[x]++;
                    xArray(yArraySize[x], input, countersY[x], arraysY[x]);
                }
                else
                {
                    countersX[x]++;
                    xArray(xArraySize[x], input, countersX[x], arraysX[x]);
                }

            }
    }
    
    myReadFile.close();
    Shape **shapes = new Shape*[numberOfLines];
    Figure fig(numberOfLines);
    
    for(int x = 0; x < numberOfLines; x++)
    {
        if(xArraySize[x] == 1)
        {
            shapes[x] = new Point(arraysX[x], arraysY[x], xArraySize[x]);
            
            fig.addShape(shapes[x]);
        }
        if(xArraySize[x] == 2)
        {
            shapes[x] = new Line(arraysX[x], arraysY[x], xArraySize[x]);
            
            fig.addShape(shapes[x]);
        }
        if(xArraySize[x] == 3)
        {
            shapes[x] = new Triangle(arraysX[x], arraysY[x], xArraySize[x]);
            
            fig.addShape(shapes[x]);
        }
        if(xArraySize[x] >= 4)
        {
            shapes[x] = new Polygon(arraysX[x], arraysY[x], xArraySize[x]);
            
            fig.addShape(shapes[x]);
        }
        
    }
    int amountOfShapes = 3;
    Shape **closestShapes = new Shape*[amountOfShapes];
    closestShapes = fig.getClosest(shapes[0], amountOfShapes);
    for(int i = 0; i < amountOfShapes; i++)
    {
        std::cout << "(" << closestShapes[i]->position().x << "," << closestShapes[i]->position().y << ") Shape: " << closestShapes[i]->getType() << "\n";
    }        
    getchar();
    return 0;
}