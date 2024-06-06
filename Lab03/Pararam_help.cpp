
#include "Pararam_help.h"
#include <cmath>

class Pararam_Point : public Pararam_Help_Point {
private:
    double x, y;

public:
    Pararam_Point(double x, double y) : x(x), y(y) {}

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

class Pararam_Line : public Pararam_Help_Line {
private:
    Pararam_Help_Point *start, *end;

public:
    Pararam_Line(Pararam_Help_Point *start, Pararam_Help_Point *end) : start(start), end(end) {}

    Pararam_Help_Point& getStart() override {
        return *start;
    }

    Pararam_Help_Point& getEnd() override {
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
