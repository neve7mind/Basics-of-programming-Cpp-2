
#include <cmath>
#include "Pararam.h"
#include "Point.h"

using namespace std;

// Class "Parallelogram" with implementation of methods
class ConcretePararam : public Pararam {
private:
    Point* p; // bottom left corner of the parallelogram
    double side1; // 1st side parallelogram (short)
    double side2; // 2nd side parallelogram (long)
    double angle; // smaller parallelogram angle

public:
    ConcretePararam(Point* p, double side1, double side2, double angle) : p(p), side1(side1), side2(side2), angle(angle) {}

    void draw(HDC hdc) override {
        double angle_rad = angle * M_PI / 180;
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        p->draw(hdc);

        POINT points[4];
        points[0].x = p->getX();
        points[0].y = p->getY();
        points[1].x = p->getX() + cos(angle_rad) * side1;
        points[1].y = p->getY() + sin(angle_rad) * side1;
        points[2].x = points[1].x + side2;
        points[2].y = points[1].y;
        points[3].x = p->getX() + side2;
        points[3].y = p->getY();

        Polygon(hdc, points, 4);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void move(double dx, double dy, HDC hdc) override {
        double angle_rad = angle * M_PI / 180;
        p->move(dx, dy, hdc);
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

        POINT points[4];
        points[0].x = p->getX();
        points[0].y = p->getY();
        points[1].x = p->getX() + cos(angle_rad) * side1;
        points[1].y = p->getY() + sin(angle_rad) * side1;
        points[2].x = points[1].x + side2;
        points[2].y = points[1].y;
        points[3].x = p->getX() + side2;
        points[3].y = p->getY();

        Polygon(hdc, points, 4);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    // Pathetic attempts to write a pivot method
    /*void p_rotate(double ang, HDC hdc) override {
        double angle_rad = angle * M_PI / 180;
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        p->draw(hdc);

        Pararam_Point p1(p->getX(), p->getY());
        Pararam_Point p2(p->getX() + cos(angle_rad) * side1, p->getY() + sin(angle_rad) * side1);
        Pararam_Point p4(p->getX() + side2, p->getY());

        Pararam_Line l12(&p1, &p2);
        Pararam_Line l14(&p1, &p4);

        POINT points[4];
        points[0].x = p->getX();
        points[0].y = p->getY();
        points[1].x = get<0>(l12.rotate(ang, hdc));
        points[1].y = get<1>(l12.rotate(ang, hdc));
        points[2].x =
        points[2].y =
        points[3].x = get<0>(l14.rotate(ang, hdc));
        points[3].y = get<1>(l14.rotate(ang, hdc));

        Polygon(hdc, points, 4);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }*/
    //points[1].x + cos(angle_rad) * side2; //points[1].x + side2;
    //points[1].y + sin(angle_rad) * side1; //points[1].y;

    void p_rotate(double ang, HDC hdc) override {
        double angle_rad = angle * M_PI / 180;
        double rotate_rad = ang * M_PI / 180;
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
        p->draw(hdc);

        POINT points[4];
        points[0].x = p->getX();
        points[0].y = p->getY();
        points[1].x = p->getX() + cos(angle_rad) * side1;
        points[1].y = p->getY() + sin(angle_rad) * side1;
        points[2].x = points[1].x + side2;
        points[2].y = points[1].y;
        points[3].x = p->getX() + side2;
        points[3].y = p->getY();

        double centerX = (points[0].x + points[2].x) / 2;
        double centerY = (points[0].y + points[2].y) / 2;
        for (int i = 0; i < 4; i++) {
            double dx = points[i].x - centerX;
            double dy = points[i].y - centerY;
            points[i].x = centerX + cos(rotate_rad) * dx - sin(rotate_rad) * dy;
            points[i].y = centerY + sin(rotate_rad) * dx + cos(rotate_rad) * dy;
        }

        Polygon(hdc, points, 4);

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
    }

    void remove(HWND hwnd, HDC hdc) {
        double angle_rad = angle * M_PI / 180;
        int minX = min(p->getX(), min(p->getX() + cos(angle_rad) * side1, min(p->getX() + cos(angle_rad) * side1 + side2, p->getX() + side2)));
        int maxX = max(p->getX(), max(p->getX() + cos(angle_rad) * side1, max(p->getX() + cos(angle_rad) * side1 + side2, p->getX() + side2)));
        int minY = min(p->getY(), min(p->getY() + sin(angle_rad) * side1, min(p->getY() + sin(angle_rad) * side1, p->getY())));
        int maxY = max(p->getY(), max(p->getY() + sin(angle_rad) * side1, max(p->getY() + sin(angle_rad) * side1, p->getY())));

        RECT rect;
        rect.left = minX - 1;
        rect.top = minY - 1;
        rect.right = maxX + 1;
        rect.bottom = maxY + 1;
        InvalidateRect(hwnd, &rect, TRUE);
    }
};