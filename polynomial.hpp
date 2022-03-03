#ifndef _POLYNOMIAL_HPP_
#define _POLYNOMIAL_HPP_

class Polynomial {
private:
    long degree;
    float *coeffs;
public:
    // Constructors
    Polynomial();
    Polynomial(long degree);
    // Copy constructor
    Polynomial(const Polynomial &src);
    // Move constructor
    Polynomial(Polynomial &&src);
    // Destructor
    ~Polynomial();

    // Copy assignment
    Polynomial &operator=(const Polynomial &rhs);
    // Move assignment
    Polynomial &operator=(Polynomial &&rhs);

    bool operator==(const Polynomial &rhs) const;
    Polynomial operator+(const Polynomial &rhs) const;
    Polynomial operator-(const Polynomial &rhs) const;
    Polynomial operator*(const Polynomial &rhs)const;  // polynomial multiplication by brute force

    Polynomial increaseExponent(long n);
    Polynomial karatsuba(const Polynomial &rhs) const; // polynomial multiplication by divide and conquer

    void displayCoeffs() const;
    void inputPolynomial();
    void randomPolynomial();

    float getCoeff(long n);
    void setCoeff(long n, int coeff);
    long getDegree();
    void setDegree(long n);
};

#endif
