
#ifndef LAB03_POINT_H
#define LAB03_POINT_H
#include <Windows.h>

// Абстрактный класс "Точка"
class Point {
private:
    HWND hwnd = CreateWindowEx(0, "Static", "", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL,
                               NULL, NULL, NULL);

public:
    virtual void draw(HDC hdc) = 0;
    virtual void move(double x, double y, HDC hdc) = 0;
    virtual void remove(HWND hwnd, HDC hdc) = 0;
    virtual double getX() = 0;
    virtual double getY() = 0;
};

#endif //LAB03_POINT_H
