
#include <iostream>
#include <cmath>
#include <Windows.h>
#include "Rhomb.h"
#include "Point.h"

using namespace std;

class Rhomb_Point : public Rhomb_Help_Point {
private:
    double x, y;

public:

    Rhomb_Point(double x, double y) : x(x), y(y) {}
    void draw(HDC hdc) override {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        Ellipse(hdc, x - 4, y - 4, x + 4, y + 4);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    double getX() override {
        return x;
    }

    double getY() override {
        return y;
    }
};

class Rhomb_Line : public Rhomb_Help_Line {
private:
    Rhomb_Help_Point *start, *end;

public:
    Rhomb_Line(Rhomb_Help_Point *start, Rhomb_Help_Point *end) : start(start), end(end) {}

    Rhomb_Help_Point& getStart() override {
        return *start;
    }

    Rhomb_Help_Point& getEnd() override {
        return *end;
    }

    std::tuple<double, double> rotate(double angle, HDC hdc) override {
        double length = sqrt(pow((end->getX() - start->getX()), 2) + pow((end->getY() - start->getY()), 2));
        double angle_rad = angle * M_PI / 180;

        if (start->getX() > end->getX()) {
            if (start->getY() > end->getY()) {
                return {start->getX() - length * cos(angle_rad + acos((start->getX() - end->getX()) / length)),
                        start->getY() - length * sin(angle_rad + acos((start->getX() - end->getX()) / length))};
            } else if (start->getY() == end->getY()) {
                return {start->getX() - length * cos(angle_rad), start->getY() - length * sin(angle_rad)};
            } else if (start->getY() < end->getY()) {
                return {start->getX() - length * cos(angle_rad - acos((start->getX() - end->getX()) / length)),
                        start->getX() - length * sin(angle_rad - acos((start->getX() - end->getX()) / length))};
            }
        } else if (start->getX() < end->getX()) {
            if (start->getY() == end->getY()) {
                return {start->getX() - length * cos(angle_rad + M_PI),
                        start->getY() - length * sin(angle_rad + M_PI)};
            } else if (start->getY() > end->getY()) {
                return {start->getX() - length * cos(angle_rad - acos((end->getX() - start->getX()) / length) + M_PI),
                        start->getY() - length * sin(angle_rad - acos((end->getX() - start->getX()) / length) + M_PI)};
            } else if (start->getY() < end->getY()) {
                return {start->getX() - length * cos(angle_rad + acos((end->getX() - start->getX()) / length) + M_PI),
                        start->getY() - length * sin(angle_rad + acos((end->getX() - start->getX()) / length) + M_PI)};
            }
        } else if (start->getX() == end->getX()) {
            if (start->getY() < end->getY()) {
                return {start->getX() - length * cos(angle_rad - M_PI / 2),
                        start->getY() - length * sin(angle_rad - M_PI / 2)};
            } else if (start->getY() > end->getY()) {
                return {start->getX() - length * cos(angle_rad + M_PI / 2),
                        start->getY() - length * sin(angle_rad + M_PI / 2)};
            }
        }
    }
};

// Class "Rhombus" with implementation of methods
class ConcreteRhombus : public Rhomb {
private:
    Point* p; // точка левого угла ромба
    double d1; // 1-ая диагональ ромба (горизонтальная)
    double d2; // 2-ая диагональ ромба (вертикальная)
public:
    ConcreteRhombus(Point* p, double d1, double d2) : p(p), d1(d1), d2(d2) {}
    void draw(HDC hdc) override {
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        p->draw(hdc);

        POINT points[4];
        points[0].x = p->getX();
        points[0].y = p->getY();
        points[1].x = p->getX() + d1/2;
        points[1].y = p->getY() + d2/2;
        points[2].x = p->getX() + d1;
        points[2].y = p->getY();
        points[3].x = p->getX() + d1/2;
        points[3].y = p->getY() - d2/2;

        Polygon(hdc, points, 4);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void move(double dx, double dy, HDC hdc) override {
        p->move(dx, dy, hdc);
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

        POINT points[4];
        points[0].x = p->getX();
        points[0].y = p->getY();
        points[1].x = p->getX() + d1/2;
        points[1].y = p->getY() + d2/2;
        points[2].x = p->getX() + d1;
        points[2].y = p->getY();
        points[3].x = p->getX() + d1/2;
        points[3].y = p->getY() - d2/2;

        Polygon(hdc, points, 4);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }
    void r_rotate(double angle, HDC hdc) override {
        Rhomb_Point d1_left(p->getX(), p->getY());
        Rhomb_Point d1_right(p->getX() + d1, p->getY());
        Rhomb_Point d2_top(p->getX() + d1/2, p->getY() - d2/2);
        Rhomb_Point d2_bot(p->getX() + d1/2, p->getY() + d2/2);
        Rhomb_Point center(p->getX() + d1/2, p->getY());
        center.draw(hdc);

        Rhomb_Line d1_1(&center, &d1_left);
        Rhomb_Line d1_2(&center, &d1_right);
        Rhomb_Line d2_1(&center, &d2_top);
        Rhomb_Line d2_2(&center, &d2_bot);

        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

        POINT points[4];
        points[0].x = get<0>(d1_1.rotate(angle, hdc));
        points[0].y = get<1>(d1_1.rotate(angle, hdc));
        points[1].x = get<0>(d2_1.rotate(angle, hdc));
        points[1].y = get<1>(d2_1.rotate(angle, hdc));
        points[2].x = get<0>(d1_2.rotate(angle, hdc));
        points[2].y = get<1>(d1_2.rotate(angle, hdc));
        points[3].x = get<0>(d2_2.rotate(angle, hdc));
        points[3].y = get<1>(d2_2.rotate(angle, hdc));

        Polygon(hdc, points, 4);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void remove(HWND hwnd, HDC hdc) override {
        double minX = min(p->getX(), min(p->getX() - d1, p->getX() + d1));
        double maxX = max(p->getX(), max(p->getX() - d1, p->getX() + d1));
        double minY = min(p->getY(), min(p->getY() - d2, p->getY() + d2));
        double maxY = max(p->getY(), max(p->getY() - d2, p->getY() + d2));
        RECT rect;
        rect.left = minX;
        rect.top = minY;
        rect.right = maxX;
        rect.bottom = maxY;
        InvalidateRect(hwnd, &rect, TRUE);
    }
};