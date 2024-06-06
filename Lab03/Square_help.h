
#ifndef LAB03_SQUARE_HELP_H
#define LAB03_SQUARE_HELP_H
#include <Windows.h>
#include <tuple>


class Square_Help_Point {
public:
    virtual double getX() = 0;
    virtual double getY() = 0;
};

class Square_Help_Line {
public:
    virtual std::tuple<double, double> rotate(double angle, HDC hdc) = 0;
    virtual Square_Help_Point& getStart() = 0;
    virtual Square_Help_Point& getEnd() = 0;
};


#endif //LAB03_SQUARE_HELP_H
