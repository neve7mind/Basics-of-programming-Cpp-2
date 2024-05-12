//Мурашов Иван Вячеславович, НКАбд-04-23

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:

    static unsigned int count;
    int num;
    int dim;
    double* a;

public:

    Vector(unsigned d, double* arr);
    ~Vector();
    Vector operator+(Vector const& other);
    Vector operator-(Vector const& other);
    Vector operator-();
    Vector operator*(Vector const& other);
    Vector operator*(double const& other);
    Vector operator=(Vector const& other);
    const double operator[](unsigned index) const;
    void print();
};

#endif