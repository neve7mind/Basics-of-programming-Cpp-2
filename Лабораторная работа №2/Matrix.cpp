//Мурашов Иван Вячеславович, НКАбд-04-23

#include <iostream>
#include "Matrix.h"
using namespace std;

Matrix::Matrix(int dim, const double* arr) {
    this->dim = dim;
    count++;
    num = count;
    a = new double[dim*dim];
    for (int i = 0; i < (dim*dim); i++) {
        if (arr != nullptr) {
            a[i] = arr[i];
        } else {
            a[i] = 0;
        }
    }
    cout << "Matrix #" << num << " is created" << endl << endl;
}

void Matrix::print() {
    cout << "Matrix #" << num << ": " << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << a[i*dim + j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

Matrix::~Matrix() {
    delete a;
    count -= 1;
    cout << "Matrix #" << num << " is destroyed" << endl << endl;
}

Matrix Matrix::operator+(Matrix const& other) {
    if (dim != other.dim)
        cerr << "Error: Matrixes are not same dimensional";
    Matrix new_matrix = Matrix(dim, nullptr);
    for (int i = 0; i < dim*dim; i++) {
        new_matrix.a[i] = a[i] + other.a[i];
    }
    return new_matrix;
}

Matrix Matrix::operator-(Matrix const& other) {
    if (dim != other.dim)
        cerr << "Error: Matrixes are not same dimensional";
    Matrix new_matrix = Matrix(dim, nullptr);
    for (int i = 0; i < dim*dim; i++) {
        new_matrix.a[i] = a[i] - other.a[i];
    }
    return new_matrix;
}

Matrix Matrix::operator-() {
    Matrix new_matrix = Matrix(dim, nullptr);
    for (int i = 0; i < dim*dim; i++) {
        new_matrix.a[i] = -1 * a[i];
    }
    return new_matrix;
}

Matrix Matrix::operator*(Matrix const& other) {
    if (dim != other.dim)
        cerr << "Error: Matrixes are not same dimensional";
    Matrix new_matrix = Matrix(dim, nullptr);
    for (int i = 0; i < dim*dim; i++) {
        new_matrix.a[i] = a[i] * other.a[i];
    }
    return new_matrix;
}

Matrix Matrix::operator*(double const& other) {
    Matrix new_matrix = Matrix(dim, nullptr);
    for (int i = 0; i < dim*dim; i++) {
        new_matrix.a[i] = a[i] * other;
    }
    return new_matrix;
}

Matrix& Matrix::operator=(Matrix const& other) {
    if (this == &other) {
        cerr << "Error: Matrixes are same dimensional" << endl;
    } else {
        delete a;
        dim = other.dim;
        a = new double[dim * dim];
        for (int i = 0; i < (dim * dim); i++) {
            a[i] = other.a[i];
        }
    }
    return *this;
}
