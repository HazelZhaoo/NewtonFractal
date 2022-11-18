#ifndef Fractal_hpp
#define Fractal_hpp
#include "Pixel.hpp"
#include "Complex.hpp"
#include <iostream>
using namespace std;

class Fractal
{
private:
    unsigned int cols;
    Pixel** grid;
    unsigned int maxIter;
    unsigned int rows;
    Pixel determinePixelColor(Complex);
    void makeNewtonFractal();

public:
    ~Fractal();
    Fractal();
    Fractal(const Fractal&);
    Fractal(Fractal&&);
    Fractal(unsigned int, unsigned int);
    const Fractal& operator= (const Fractal&);
    Fractal& operator=(Fractal&&);
    friend void saveToPPM(const Fractal&, const char*);

};

#endif