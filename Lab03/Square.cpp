
#include "Square.h"
#include "Point.h"

using namespace std;

// Класс "Квадрат" с реализацией методов
class ConcreteSquare : public Square {

private:
    Point *p; // точка верхнего левого угла квадрата
    double side; // сторона квадрата

public:
    ConcreteSquare(Point* p, double side) : p(p), side(side) {}
    void draw(HDC hdc) override {
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        p->draw(hdc);
        Rectangle(hdc, p->getX(), p->getY(), p->getX() + side, p->getY() + side);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void move(double dx, double dy, HDC hdc) override {
        p->move(dx, dy, hdc);
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        Rectangle(hdc, p->getX(), p->getY(), p->getX() + side, p->getY() + side);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void s_rotate(double angle, HDC hdc) override {
        Square_Point start(p->getX(), p->getY());
        Square_Point end(p->getX() + side, p->getY());
        Square_Line line(&start, &end);

        double endX = get<0>(line.rotate(angle, hdc));
        double endY = get<1>(line.rotate(angle, hdc));

        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

        POINT points[4];
        points[0].x = p->getX();
        points[0].y = p->getY();
        points[1].x = endX;
        points[1].y = endY;
        points[2].x = endX - endY + p->getY();
        points[2].y = endX + endY - p->getX();
        points[3].x = p->getX() - endY + p->getY();
        points[3].y = p->getY() + endX - p->getX();

        Polygon(hdc, points, 4);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void remove(HWND hwnd, HDC hdc) override {
        RECT rect;
        rect.left = p->getX();
        rect.top = p->getY();
        rect.right = p->getX() + side;
        rect.bottom = p->getY() + side;
        InvalidateRect(hwnd, &rect, TRUE);
    }
};