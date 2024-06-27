
#ifndef LAB03_LINE_H
#define LAB03_LINE_H
#include "Point.h"

// Abstract class "Line"
class Line {
public:
    virtual void draw(HDC hdc) = 0;
    virtual void remove(HDC hdc) = 0;
    virtual void move(double x, double y, HDC hdc) = 0;
    virtual void rotate(double angle, HDC hdc) = 0;
    virtual Point& getStart() = 0;
    virtual Point& getEnd() = 0;
};


#endif //LAB03_LINE_H
