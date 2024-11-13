#include "../include/matrice.h"
#include <iostream>

void foo(Matrix mat) {
    std::cout << "Dans la fonction foo\n";
}

int main() {
    std::cout << "Test des opérations sur les matrices\n";

    Matrix a(2, 2);
    Matrix b(2, 2);
    Matrix c(2, 2);

    a.set(0, 0, 1.0);
    a.set(0, 1, 2.0);
    a.set(1, 0, 3.0);
    a.set(1, 1, 4.0);

    b.set(0, 0, 5.0);
    b.set(0, 1, 6.0);
    b.set(1, 0, 7.0);
    b.set(1, 1, 8.0);

    std::cout << "Matrice a:\n" << a;
    std::cout << "Matrice b:\n" << b;

    Matrix d = a * b;
    std::cout << "Matrice d (a * b):\n" << d;

    c = a * b;
    std::cout << "Matrice c (a * b affectee):\n" << c;

    foo(c * c);

    return 0;
}
