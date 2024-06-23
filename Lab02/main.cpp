
#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

int main()
{
    double arr1[] = {0, 2.47, 24};
    double arr2[] = {7, 11.74, 6.12};

    Vector v1(3, arr1);
    v1.print();

    Vector v2(3, arr2);
    v2.print();

    Vector v3 = v1 + v2;
    v3.print();

    Vector v4 = v1 - v2;
    v4.print();

    Vector v5 = -v1;
    v5.print();

    Vector v6 = v1 * v2;
    v6.print();

    Vector v7 = v1 * v2;
    v7.print();

    Vector v8 = v1;
    v8 = v2;
    v8.print();


    double arr3[3][3] = {
            {1, 54, 2.3},
            {14.4, 7.68, 7.9},
            {67, 0, 41}};
    double arr4[3][3] = {
            {4, 2.124, 12},
            {4, 5, 13.5},
            {87.2, 6, 8.2114}};

    Matrix m1(3, (double *)arr3);
    m1.print();

    Matrix m2(3, (double *)arr4);
    m2.print();

    Matrix m3 = m1 + m2;
    m3.print();

    Matrix m4 = m1 - m2;
    m4.print();

    Matrix m5 = -m1;
    m5.print();

    Matrix m6 = m1 * m2;
    m6.print();

    Matrix m7 = m1 * 2;
    m7.print();

    Matrix m8 = m1;
    m8.print();

    m8 = m2;
    m8.print();

    return 0;
}
