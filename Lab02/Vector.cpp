
#include <iostream>
#include "Vector.h"

using namespace std;

unsigned int Vector::count = 0;

Vector::Vector(unsigned int dim, double* arr) {
    this->dim = dim;
    count++;
    num = count;
    a = new double[dim];
    for (int i = 0; i < dim; i++) {
        a[i] = arr[i];
    }
    cout << "Vector #" << num << " created" << endl << endl;
}

void Vector::print() {
    cout << "Vector " << num << ": ";
    for (int i = 0; i < dim; i++) {
        cout << a[i] << " ";
    }
    cout << endl << endl;
}

Vector::~Vector() {
    count -= 1;
    cout << "Vector #" << num << " destroyed" << endl << endl;
    delete[] a;
}

Vector Vector::operator+(Vector const& other) {
    if (dim != other.dim) {
        cerr << "Error: Vectors are not same dimensional";
    }
    double* arr = new double[dim];
    for (int i = 0; i < dim; i++) {
        arr[i] = a[i] + other.a[i];
    }
    return Vector(dim, arr);
}

Vector Vector::operator-(Vector const& other) {
    if (dim != other.dim) {
        cerr << "Error: Vectors are not same dimensional";
    }
    double* arr = new double[dim];
    for (int i = 0; i < dim; i++) {
        arr[i] = a[i] - other.a[i];
    }
    return Vector(dim, arr);
}

Vector Vector::operator-() {
    double* arr = new double[dim];
    for (int i = 0; i < dim; i++) {
        arr[i] = -a[i];
    }
    return Vector(dim, arr);
}

Vector Vector::operator*(Vector const& other) {
    if (dim != other.dim) {
        cerr << "Error: Vectors are not same dimensional";
    }
    double* arr = new double[dim];
    for (int i = 0; i < dim; i++) {
        arr[i] = a[i] * other.a[i];
    }
    return Vector(dim, arr);
}

Vector Vector::operator*(double const& n) {
    double* arr = new double[dim];
    for (int i = 0; i < dim; i++) {
        arr[i] = a[i] * n;
    }
    return Vector(dim, arr);
}

Vector Vector::operator=(Vector const& other) {
    if (this == &other) {
        cerr << "Error: Equivalent objects" << endl;
        return *this;
    }
    dim = other.dim;
    double* arr = new double[dim];
    for (int i = 0; i < dim; ++i) {
        arr[i] = other.a[i];
    }
    return *this;
}

const double Vector::operator[](unsigned index) const {
    if (index >= dim) {
        throw std::out_of_range("Index out of range");
    }
    return a[index];
}

