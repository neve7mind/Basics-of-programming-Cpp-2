
#include <string>
#include <windows.h>
#include <cmath>

#include "Point.cpp"
#include "Line.cpp"
#include "Square.cpp"
#include "Rhomb.cpp"
#include "Pararam.cpp"

int main() {

    HWND hwnd = CreateWindowEx(0, "Static", "", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL,
                               NULL, NULL, NULL);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    HDC hdc = GetDC(hwnd);


    ConcretePoint p1(100, 100);
    p1.draw(hdc);
    ConcretePoint p2(100, 250);
    p2.draw(hdc);

    p1.move(100, 100, hdc);

    ConcretePoint p3(180, 163);
    ConcretePoint p4(220, 135);
    ConcretePoint p5(350, 100);
    ConcretePoint p6(100, 350);
    ConcretePoint p7(500, 460);
    ConcretePoint p8(450, 350);
    ConcretePoint p9(400, 460);

    ConcreteLine l1(&p3, &p2);
    l1.draw(hdc);

    l1.move(100, 100, hdc);

    l1.rotate(60, hdc);

    ConcreteSquare s1(&p4, 25);
    s1.draw(hdc);

    s1.move(100, 100, hdc);

    s1.s_rotate(230, hdc);

    ConcreteRhombus r1(&p5, 60, 40);
    r1.draw(hdc);

    r1.move(100, 100, hdc);

    r1.r_rotate(30, hdc);

    //r1.remove(hwnd, hdc);

    ConcretePararam par1(&p6, 25, 75, 60);
    par1.draw(hdc);

    par1.move(100, 100, hdc);

    par1.p_rotate(90, hdc);

    //p6.remove(hwnd, hdc);

    //l1.remove(hdc);

    ConcreteSquare s2(&p7, 60);
    s2.draw(hdc);

    //s2.remove(hwnd, hdc);

    ConcreteRhombus r2(&p8, 50, 30);
    r2.draw(hdc);

    //r2.remove(hwnd, hdc);

    ConcretePararam par2(&p9, 30, 100, 120);
    par2.draw(hdc);

    par2.remove(hwnd, hdc);


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);


    return 0;
}
