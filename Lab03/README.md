# 2D Figures Painting (WinAPI)

## The aim of the project

Write a computer program containing a class description for the list of geometric objects: 
- Point [Point.cpp]() ,
- Line,
- Square,
- Rhombus,
- Rectangle,
- Parallelogram

with an implementation of a set of methods:
- draw,
- move,
- rotate,
- remove.

## How did I do it anyway?

### Header files

For each .cpp class I created a header file with declaration of virtual methods

E.g. 
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

For such objects as Square, Parallelogram and Rhombus I created some additional classes such as
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


