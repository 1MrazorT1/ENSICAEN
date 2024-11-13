/*
#include "../include/complex.h"
#include <iostream>
#include <limits>

int main(){
    Complex a;
    a.printComplex();
    Complex b(1,2);
    b.printComplex();
    Complex c = a;
    c.printComplex();
    Complex d;
    d = b;
    d.printComplex();
    std::cout << "le reel du complexe b est " << b.getReal() << " et son imaginaire est " << b.getImaginary() << std::endl;
    b.Echanger();
    std::cout << "le reel du complexe b est " << b.getReal() << " et son imaginaire est " << b.getImaginary() << std::endl;
    (a*b).printComplex();
    (a+b).printComplex();
    (a-b).printComplex();
    Complex z(2, 3.14 / 4, true);
    std::cout << "Complexe initialise avec module et argument: ";
    z.printComplex();
    z = normalized(z);
    double angle = 3.14 / 2;
    rotate(z, angle);
    Complex z2 = z;
    Complex z1 = maxModule(z2, z2 * z2);
    int n = 5;
    Complex* roots = new Complex[n];
    racine_nieme(n, roots);
    return 0;
}
*/