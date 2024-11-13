#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex{
    private:
        double reel;
        double imaginaire;
    public:
        Complex();
        Complex(double a, double b);
        Complex(const Complex& c);
        Complex(double module, double argument, bool polaire);
        Complex& operator=(const Complex& c);
        ~Complex();
        double getReal() const;
        double getImaginary() const;
        double Module() const;
        double Argument() const;
        void printComplex() const;
        void Echanger();
        Complex operator*(const Complex& other) const;
        Complex operator+(const Complex& other) const;
        Complex operator-(const Complex& other) const;
};

Complex normalized(const Complex& c);
void rotate(Complex& c, double angle);
const Complex& maxModule(const Complex& c1, const Complex& c2);
void racine_nieme(int n, Complex arr[]);


/*Complex operator*(const Complex& a, const Complex& b);
Complex operator+(const Complex& a, const Complex& b);
Complex operator-(const Complex& a, const Complex& b);*/


#endif