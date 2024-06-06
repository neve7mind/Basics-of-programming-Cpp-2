
#ifndef LAB03_RHOMB_HELP_H
#define LAB03_RHOMB_HELP_H
#include <Windows.h>
#include <tuple>

class Rhomb_Help_Point {
public:
    virtual void draw(HDC hdc) = 0;
    virtual double getX() = 0;
    virtual double getY() = 0;
};

class Rhomb_Help_Line {
public:
    virtual std::tuple<double, double> rotate(double angle, HDC hdc) = 0;
    virtual Rhomb_Help_Point& getStart() = 0;
    virtual Rhomb_Help_Point& getEnd() = 0;
};

#endif //LAB03_RHOMB_HELP_H
