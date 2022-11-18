#include "Complex.hpp"
#include <iostream>
#include <cmath>
using namespace std;

class Complex::InputOutOfBoundsException
{
private:
    const char* errorMessage;
    const char* offendingIndex;
public:
    InputOutOfBoundsException(const char*, const char*);
    const char* returnError();
    const char* returnOffendingIndex();

};


Complex:: ~Complex()
{
    //cout << "Complex destructor is called" << endl;
};

Complex::Complex() :imag(0.0), real(0.0)
{
    //cout << "Complex constructor is called" << endl;
};

Complex::Complex(const Complex& c_cam) : imag(0.0), real(0.0)
{
    imag = c_cam.imag;
    real = c_cam.real;
    //cout << "Complex copy constructor is called" << endl;
}

Complex::Complex(double cam) : imag(0.0), real(0.0)
{
    real = cam;
    //cout << "Complex one arg constructor is called" << endl;
}

Complex::Complex(double c_imag, double c_real) : imag(0.0), real(0.0)
{
    imag = c_imag;
    real = c_real;
    //cout << "Complex two arg constructor is called" << endl;
};

double& Complex:: operator[](const char* real_imag)
{
    if (strcmp(real_imag, "real") == 0)
    {
        return real;
    }
    else if (strcmp(real_imag, "imag") == 0)
    {
        return imag;
    }
    else
    {
        throw (InputOutOfBoundsException("Invalid Input!!", real_imag));
    }
};

Complex::InputOutOfBoundsException::InputOutOfBoundsException(const char* error, const char* index) : errorMessage(error), offendingIndex(index)
{
};

const char* Complex::InputOutOfBoundsException::returnError()
{
    return errorMessage;
};

const char* Complex::InputOutOfBoundsException::returnOffendingIndex()
{
    return offendingIndex;
};

const Complex operator*(const Complex& c1, const Complex& c2)
{
    Complex product;

    product.real = (c1.real * c2.real) - (c1.imag * c2.imag);
    product.imag = (c1.real * c2.imag) + (c1.imag * c2.real);

    return product;
};

const Complex operator/(const Complex& c1, const Complex& c2)
{
    Complex quotient;

    quotient.real = ((c1.real * c2.real) + (c1.imag * c2.imag)) / (pow(c2.real, 2) + pow(c2.imag, 2));
    quotient.imag = ((c1.imag * c2.real) - (c1.real * c2.imag)) / (pow(c2.real, 2) + pow(c2.imag, 2));

    return quotient;
};

const Complex operator+(const Complex& c1, const Complex& c2)
{
    Complex c3;
    c3.real = c1.real + c2.real;
    c3.imag = c1.imag + c2.imag;

    return c3;
};

const Complex operator-(const Complex& c1, const Complex& c2)
{
    Complex c3;
    c3.real = c1.real - c2.real;
    c3.imag = c1.imag - c2.imag;

    return c3;
};

double getMagnitude(const Complex& c1)
{
    return sqrt((c1.real * c1.real) + (c1.imag * c1.imag));
};

