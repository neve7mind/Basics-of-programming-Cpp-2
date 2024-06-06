
#ifndef LAB03_PARARAM_HELP_H
#define LAB03_PARARAM_HELP_H
#include <Windows.h>
#include <tuple>

class Pararam_Help_Point {
public:
    virtual void draw(HDC hdc) = 0;
    virtual double getX() = 0;
    virtual double getY() = 0;
};

class Pararam_Help_Line {
public:
    virtual std::tuple<double, double> rotate(double angle, HDC hdc) = 0;
    virtual Pararam_Help_Point& getStart() = 0;
    virtual Pararam_Help_Point& getEnd() = 0;
};


#endif //LAB03_PARARAM_HELP_H
