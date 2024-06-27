
#include "Square.h"
#include "Point.h"

using namespace std;

class Square_Point : public Square_Help_Point {
private:
    double x, y;

public:

    Square_Point(double x, double y) : x(x), y(y) {}

    double getX() override {
        return x;
    }

    double getY() override {
        return y;
    }
};

class Square_Line : public Square_Help_Line {
private:
    Square_Help_Point *start, *end;

public:
    Square_Line(Square_Help_Point *start, Square_Help_Point *end) : start(start), end(end) {}

    Square_Help_Point &getStart() override {
        return *start;
    }

    Square_Help_Point &getEnd() override {
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

// Class "Square" with implementation of methods
class ConcreteSquare : public Square {

private:
    Point *p; // top left of the square point
    double side; // square side

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