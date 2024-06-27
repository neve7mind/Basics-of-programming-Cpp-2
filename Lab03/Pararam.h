
#ifndef LAB03_PARARAM_H
#define LAB03_PARARAM_H
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

// Abstract class "Parallelogram"
class Pararam {

private:
    HWND hwnd = CreateWindowEx(0, "Static", "", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL,
                               NULL, NULL, NULL);

public:
    virtual void draw(HDC hdc) = 0;
    virtual void remove(HWND hwnd, HDC hdc) = 0;
    virtual void move(double x, double y, HDC hdc) = 0;
    virtual void p_rotate(double ang, HDC hdc) = 0;
};


#endif //LAB03_PARARAM_H
