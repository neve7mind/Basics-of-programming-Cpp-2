
#include <Windows.h>
#include <cmath>
#include "Point.h"
#include "Line.h"
using namespace std;

// Class "Line" with implementation of methods

class ConcreteLine : public Line {
private:
    Point *start, *end;

public:
    ConcreteLine(Point* start, Point* end) : start(start), end(end) {}
    void draw(HDC hdc) override {
        start->draw(hdc);
        end->draw(hdc);
        MoveToEx(hdc, start->getX(), start->getY(), nullptr);
        LineTo(hdc, end->getX(), end->getY());
    }

    void move(double dx, double dy, HDC hdc) override {
        start->move(dx, dy, hdc);
        end->move(dx, dy, hdc);
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        MoveToEx(hdc, start->getX(), start->getY(), nullptr);
        LineTo(hdc, end->getX(), end->getY());
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void rotate(double angle, HDC hdc) override {
        double length = sqrt( pow((end->getX() - start->getX()), 2) + pow((end->getY() - start->getY()), 2));
        double angle_rad = angle * M_PI / 180;
        double new_x, new_y;
        MoveToEx(hdc, start->getX(), start->getY(), nullptr);

        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

        if (start->getX() > end->getX()) {
            if (start->getY() > end->getY()) {
                new_x = start->getX() - length * cos(angle_rad + acos((start->getX() - end->getX()) / length));
                new_y = start->getY() - length * sin(angle_rad + acos((start->getX() - end->getX()) / length));
            }
            else if (start->getY() == end->getY()) {
                new_x = start->getX() - length * cos(angle_rad);
                new_y = start->getY() - length * sin(angle_rad);
            }
            else if (start->getY() < end->getY()) {
                new_x = start->getX() - length * cos(angle_rad - acos((start->getX() - end->getX()) / length));
                new_y = start->getX() - length * sin(angle_rad - acos((start->getX() - end->getX()) / length));
            }
        }
        else if (start->getX() < end->getX()) {
            if (start->getY() == end->getY()) {
                new_x = start->getX() - length * cos(angle_rad + M_PI);
                new_y = start->getY() - length * sin(angle_rad + M_PI);
            }
            else if (start->getY() > end->getY()) {
                new_x = start->getX() - length * cos(angle_rad - acos((end->getX() - start->getX()) / length) + M_PI);
                new_y = start->getY() - length * sin(angle_rad - acos((end->getX() - start->getX()) / length) + M_PI);
            }
            else if (start->getY() < end->getY()) {
                new_x = start->getX() - length * cos(angle_rad + acos((end->getX() - start->getX()) / length) + M_PI);
                new_y = start->getY() - length * sin(angle_rad + acos((end->getX() - start->getX()) / length) + M_PI);
            }
        }
        else if (start->getX() == end->getX()) {
            if (start->getY() < end->getY()) {
                new_x = start->getX() - length * cos(angle_rad - M_PI/2);
                new_y = start->getY() - length * sin(angle_rad - M_PI/2);
            }
            else if (start->getY() > end->getY()) {
                new_x = start->getX() - length * cos(angle_rad + M_PI/2);
                new_y = start->getY() - length * sin(angle_rad + M_PI/2);
            }
        }
        LineTo(hdc, new_x, new_y);
        Ellipse(hdc, new_x - 4, new_y - 4, new_x + 4, new_y + 4);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void remove(HDC hdc) {
        int minX = min(start->getX(), end->getX());
        int maxX = max(start->getX(), end->getX());
        int minY = min(start->getY(), end->getY());
        int maxY = max(start->getY(), end->getY());
        RECT rect;
        rect.left = minX;
        rect.top = minY;
        rect.right = maxX;
        rect.bottom = maxY;
        HBRUSH hBrush = CreateSolidBrush(GetBkColor(hdc));
        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);
    }

    Point& getStart() override {
        return *start;
    }

    Point& getEnd() override {
        return *end;
    }
};