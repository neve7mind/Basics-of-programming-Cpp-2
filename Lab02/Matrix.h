
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {

private:

    inline static unsigned int count;
    int dim;
    double *a;
    int num;

public:

    Matrix(int dim, const double *arr);
    ~Matrix();
    Matrix operator+(Matrix const &other);
    Matrix operator-(Matrix const &other);
    Matrix operator-();
    Matrix operator*(Matrix const &other);
    Matrix operator*(double const &other);
    Matrix &operator=(Matrix const &other);
    void print();
};

#endif
