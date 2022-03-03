#include <iostream>
#include <cstring>
#include <math.h>
#include "polynomial.hpp"

Polynomial::Polynomial() 
    : degree{0}, coeffs{nullptr} {
    this->coeffs = new float[1];
    this->coeffs[0] = 0;
}

Polynomial::Polynomial(long degree) 
    : degree{degree}, coeffs{nullptr} {
    this->coeffs = new float[degree + 1];
    for(auto i = 0; i <= this->degree; ++i)
        this->coeffs[i] = 0;
}

Polynomial::Polynomial(const Polynomial &src) 
    : degree{src.degree}, coeffs{nullptr} {
    this->coeffs = new float[src.degree + 1];
    for(auto i = 0; i <= this->degree; ++i)
        this->coeffs[i] = src.coeffs[i];
}

Polynomial::Polynomial(Polynomial &&src) 
    : degree(src.degree), coeffs(src.coeffs) {
    src.degree = -1;
    src.coeffs = nullptr;
}

Polynomial::~Polynomial() {
    delete this->coeffs;
}

Polynomial &Polynomial::operator=(const Polynomial &rhs) {
    this->degree = rhs.degree;
    delete [] this->coeffs;
    this->coeffs = new float[rhs.degree + 1];
    for(auto i = 0; i <= this->degree; ++i)
        this->coeffs[i] = rhs.coeffs[i];
    return *this;
}

Polynomial &Polynomial::operator=(Polynomial &&rhs) {
    this->degree = rhs.degree;
    rhs.degree = -1;
    delete [] this->coeffs;
    this->coeffs = rhs.coeffs;
    rhs.coeffs = nullptr;
    return *this;
}

bool Polynomial::operator==(const Polynomial &rhs) const {
    bool res = (this->degree == rhs.degree);

    for(auto i = 0; res && i <= this->degree; ++i)
        res = (this->coeffs[i] == rhs.coeffs[i]);

    return res;
}

Polynomial Polynomial::operator+(const Polynomial &rhs) const {
    long size = (this->degree > rhs.degree) ? this->degree : rhs.degree;
    Polynomial temp(size);
    for(int i = 0; i <= size; ++i) {
        if(i <= this->degree)
            temp.coeffs[i] += this->coeffs[i];
        if(i <= rhs.degree)
            temp.coeffs[i] += rhs.coeffs[i];
    }
    
    long new_degree = temp.degree;
    while(new_degree >= 0 && temp.coeffs[new_degree] == 0) new_degree--;

    Polynomial res(new_degree);
    for(auto i = 0; i <= new_degree; ++i)
        res.coeffs[i] = temp.coeffs[i];
    return res;
}

Polynomial Polynomial::operator-(const Polynomial &rhs) const {
    long size = (this->degree > rhs.degree) ? this->degree : rhs.degree;
    Polynomial temp(size);
    for(int i = 0; i <= size; ++i) {
        if(i <= this->degree)
            temp.coeffs[i] += this->coeffs[i];
        if(i <= rhs.degree)
            temp.coeffs[i] -= rhs.coeffs[i];
    }
    
    long new_degree = temp.degree;
    while(new_degree >= 0 && temp.coeffs[new_degree] == 0) new_degree--;

    Polynomial res(new_degree);
    for(auto i = 0; i <= new_degree; ++i)
        res.coeffs[i] = temp.coeffs[i];
    return res;
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const {
    Polynomial res(this->degree + rhs.degree);

    for(auto i = 0; i <= this->degree; ++i)
        for(auto j = 0; j <= rhs.degree; ++j)
            res.coeffs[i + j] += this->coeffs[i] * rhs.coeffs[j];
    return res;
}

Polynomial Polynomial::increaseExponent(long n) {
    this->setDegree(this->degree + n);

    for(auto i = this->degree; i >= 0; --i) {
        if(i < n) this->coeffs[i] = 0;
        else this->coeffs[i] = this->coeffs[i - n];
    }
    return *this;
}

Polynomial Polynomial::karatsuba(const Polynomial &rhs) const {
    if(this->degree <= 1 || rhs.degree >= 1)
        return ((*this) * rhs);

    Polynomial res(this->degree + rhs.degree);

    long half = floor(this->degree / 2);
    Polynomial A0(half - 1), A1(this->degree - half), B0(half - 1), B1(this->degree - half);
    for(auto i = 0; i < half; ++i) {
        A0.setCoeff(this->coeffs[i], i);
        B0.setCoeff(rhs.coeffs[i], i);
        A1.setCoeff(this->coeffs[i + half], i);
        B1.setCoeff(rhs.coeffs[i + half], i);
        if(this->degree % 2 == 1 && i + 1 == half) {
            A1.setCoeff(this->coeffs[i + half], i);
            B1.setCoeff(rhs.coeffs[i + half], i);
        }
    }

    Polynomial U = A0.karatsuba(B0);
    Polynomial Y = (A0 + A1).karatsuba(B0 + B1);
    Polynomial Z = A1.karatsuba(B1);

    Polynomial W = Y - U - Z;
    res = U + (W.increaseExponent(half)) + (Z.increaseExponent(this->degree));
    return res;
}

void Polynomial::displayCoeffs() const {
    for(auto i = 0; i <= this->degree; ++i)
        std::cout << this->coeffs[i] << " ";
    std::cout << std::endl;
}

void Polynomial::inputPolynomial() {
    for(auto i = 0; i <= this->degree; ++i)
        std::cin >> this->coeffs[i];
}

void Polynomial::randomPolynomial() {
    for(auto i = 0; i <= this->degree; ++i)
        this->coeffs[i] = rand() % 100;
}

float Polynomial::getCoeff(long n) {
    return this->coeffs[n];
}

void Polynomial::setCoeff(long n, int coeff) {
    this->coeffs[n] = coeff;
}

long Polynomial::getDegree() {
    return this->degree;
}

void Polynomial::setDegree(long n) {
    long prev_degree = this->degree;
    float prev_coeffs[prev_degree + 1];
    for(auto i = 0; i <= prev_degree; ++i)
        prev_coeffs[i] = this->coeffs[i];

    this->degree = n;
    this->coeffs = new float[this->degree + 1];

    for(auto i = 0; i <= this->degree; ++i) {
        if(i < prev_degree) this->coeffs[i] = 0;
        else this->coeffs[i] = prev_coeffs[i];
    }
}
