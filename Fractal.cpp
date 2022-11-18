#include "Fractal.hpp"
#include "Pixel.hpp"
#include "Complex.hpp"
#include <fstream>
#include <cmath>

Fractal::Fractal() :cols(0), grid(nullptr), maxIter(30), rows(0)
{
    //cout << "Fractal defualt constructor is called" << endl;
};

Fractal::~Fractal()
{

    for (int i = 0; i < rows; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
   // cout << "Fractal destructor is called" << endl;
};

Fractal::Fractal(const Fractal& frac) :cols(0), grid(nullptr), maxIter(30), rows(0)
{

    cols = frac.cols;
    maxIter = frac.maxIter;
    rows = frac.rows;

    grid = new Pixel * [rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new Pixel[cols];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = frac.grid[i][j];
        }
    }
    //cout << "Fractal copy constructor is called" << endl;

};

Fractal::Fractal(Fractal&& frac) :cols(0), grid(nullptr), maxIter(30), rows(0)
{

    cols = frac.cols;
    grid = frac.grid;
    maxIter = frac.maxIter;
    rows = frac.rows;
    frac.cols = 0;
    frac.grid = nullptr;
    frac.maxIter = 0;
    frac.rows = 0;
    //cout << "Fractal move constructor is called" << endl;
};

Fractal::Fractal(unsigned int grid_r, unsigned int grid_c) :cols(grid_c), grid(nullptr), maxIter(30), rows(grid_r)
{

    grid = new Pixel * [rows];
    for (unsigned int i = 0; i < rows; i++)
    {
        grid[i] = new Pixel[cols];
    }

    makeNewtonFractal();
    //cout << "Fractal two args constructor is called" << endl;
};

Pixel Fractal::determinePixelColor(Complex Z)
{
    double total = 1E-6;
    double diff = 1.0;
    double test = sqrt(3.0) / 2.0;
    unsigned int iter = 0;
    unsigned int color = 0;
    Complex Znew;

    while (iter < 512)
    {
        iter++;
        Znew = Z - (Z * Z * Z - 1.0) / (3 * Z * Z);
        diff = getMagnitude(Z - Znew);
        Z = Znew;
        if (diff < total)
        {
            color = maxIter - min(iter, maxIter);
            if (abs(Znew["imag"]) < total)
            {
                return Pixel(color, 0, 0);
            }
            else if (abs(Znew["imag"] - test) < total)
            {
                return Pixel(0, color, 0);
            }
            else if (abs(Znew["imag"] + test) < total)
                return Pixel(0, 0, color);
        }
    }
    return Pixel(0, 0, 0);
};

void Fractal::makeNewtonFractal()
{
    //cout << "Now creating the Newton Fractal..." << endl;
    Complex complex_z;
    double step_height = 4.0 / rows;
    double step_width = 4.0 / cols;
    for (int j = 0; j < rows; j++)
    {
        for (int k = 0; k < cols; k++)
        {
            complex_z["imag"] = 2.0 - (j * step_height);
            complex_z["real"] = (k * step_width) - 2.0;
            grid[j][k] = determinePixelColor(complex_z);
        }
    }
};

const Fractal& Fractal:: operator=(const Fractal& frac)
{
    rows = frac.rows;
    cols = frac.cols;
    maxIter = frac.maxIter;
    if (grid != nullptr)
    {
        delete[]grid;
    }
    grid = new Pixel * [rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new Pixel[cols];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = frac.grid[i][j];
        }
    }

    return frac;
}

Fractal& Fractal:: operator=(Fractal&& frac)
{
    if (this != &frac)
    {
        swap(rows, frac.rows);
        swap(cols, frac.cols);
        swap(grid, frac.grid);
        swap(maxIter, frac.maxIter);
    }

    return *this;
}


void saveToPPM(const Fractal& frac, const char* file)
{
    //cout << "Saving Fractals to ASCII file...." << endl;
    ofstream output;
    output.open(file, ios::out);

    output << "P3" << endl;
    output << "#Newton Fractal" << endl;
    output << frac.cols << " " << frac.rows << endl;
    output << frac.maxIter << endl;

    for (int i = 0; i < frac.rows; i++)
    {
        for (int j = 0; j < frac.cols; j++)
        {
            output << frac.grid[i][j] << " ";

        }
        output << endl;
    }
}