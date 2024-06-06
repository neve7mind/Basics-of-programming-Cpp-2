
#ifndef LAB03_RHOMB_H
#define LAB03_RHOMB_H
#include <Windows.h>
#include "Rhomb_help.cpp"

// Абстрактный класс "Ромб"
class Rhomb {

private:
    HWND hwnd = CreateWindowEx(0, "Static", "", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL,
                               NULL, NULL, NULL);

public:
    virtual void draw(HDC hdc) = 0;
    virtual void remove(HWND hwnd, HDC hdc) = 0;
    virtual void move(double x, double y, HDC hdc) = 0;
    virtual void r_rotate(double angle, HDC hdc) = 0;
};


#endif //LAB03_RHOMB_H
