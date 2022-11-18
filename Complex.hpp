#ifndef Complex_hpp
#define Complex_hpp
#include <iostream>
using namespace std;

class Complex
{
private:
    double imag;
    double real;
public:

    ~Complex();
    Complex();
    Complex(const Complex& cam);
    Complex(double cam);
    Complex(double cam1, double cam2);
    double& operator[](const char*);
    class InputOutOfBoundsException;
    friend const Complex operator*(const Complex&, const Complex&);
    friend const Complex operator/(const Complex&, const Complex&);
    friend const Complex operator+(const Complex&, const Complex&);
    friend const Complex operator-(const Complex&, const Complex&);
    friend double getMagnitude(const Complex&);
};



#endif 
