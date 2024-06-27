
#include "Point.h"
#include <Windows.h>

// Class "Point" with implementation of methods
class ConcretePoint : public Point {
private:
    double x, y;

public:
    ConcretePoint(double x, double y) : x(x), y(y) {}

    void draw(HDC hdc) override {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        Ellipse(hdc, x - 4, y - 4, x + 4, y + 4);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void move(double dx, double dy, HDC hdc) override {
        x += dx;
        y += dy;
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        Ellipse(hdc, x - 4, y - 4, x + 4, y + 4);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }


    void remove(HWND hwnd, HDC hdc) override {
        RECT rect;
        rect.left = getX() - 4;
        rect.top = getY() - 4;
        rect.right = getX() + 4;
        rect.bottom = getY() + 4;
        InvalidateRect(hwnd, &rect, TRUE);
    }

    double getX() override {
        return x;
    }

    double getY() override {
        return y;
    }
};


