# 2D Figures Painting (WinAPI)

![](https://github.com/neve7mind/Basics-of-programming-Cpp-2/assets/134313494/f836e0b3-0592-4d6f-bc78-5cd6cb6cacbd)

## The aim of the project

Write a computer program containing a class description for the list of geometric objects: 
- Point ( [Point.cpp](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Point.cpp), [Point.h](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Point.h) ),
- Line  ( [Line.cpp](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Line.cpp), [Line.h](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Line.h) ),
- Square ( [Square.cpp](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Square.cpp), [Square.h](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Square.h) ),
- Rhombus ( [Rhomb.cpp](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Rhomb.cpp), [Rhomb.h](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Rhomb.h) ),
- Parallelogram ( [Pararam.cpp](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Pararam.cpp), [Pararam.h](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Pararam.h) )

with an implementation of a set of methods:
- draw,
- move,
- rotate,
- remove.

## How did I do it anyway?

### Header files

For each .cpp class I created a header file with declaration of virtual methods.

E.g. ([Line.h](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Line.h))
```cpp
class Line {
public:
    virtual void draw(HDC hdc) = 0;
    virtual void remove(HDC hdc) = 0;
    virtual void move(double x, double y, HDC hdc) = 0;
    virtual void rotate(double angle, HDC hdc) = 0;
    virtual Point& getStart() = 0;
    virtual Point& getEnd() = 0;
};
```

For such objects as Square, Parallelogram and Rhombus I created some additional classes such as ([Square.h](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Square.h))
```cpp
class Square_Help_Point {
public:
    virtual double getX() = 0;
    virtual double getY() = 0;
};

class Square_Help_Line {
public:
    virtual std::tuple<double, double> rotate(double angle, HDC hdc) = 0;
    virtual Square_Help_Point& getStart() = 0;
    virtual Square_Help_Point& getEnd() = 0;
};
```

I need them to avoid this error
```diff
- redefinition of 'class ... '
```

### .cpp files

In every .cpp file (except main, of course) there're a conctructor for a Concrete Figure and a realisation of methods declared earlier in header file.

E.g. ([Line.cpp](https://github.com/neve7mind/Basics-of-programming-Cpp-2/blob/main/Lab03/Line.cpp))
```cpp
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
```

### main.cpp

Main class contains the usage of some methods for some figures, you can try it yourself!

