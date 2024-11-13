#include "../include/Complex.h"
#include <cmath>

Complex::Complex() : reel(0), imaginaire(0) {
    std::cout << "+++Complex() @ " << this << std::endl;
}

Complex::Complex(double a, double b) : reel(a), imaginaire(b) {
    std::cout << "+++Complex(" << a << ", " << b << ") @ " << this << std::endl;
}

Complex::Complex(double module, double argument, bool polaire) {
    if (polaire) {
        reel = module * std::cos(argument);
        imaginaire = module * std::sin(argument);
    }
}

Complex::Complex(const Complex& c) : reel(c.reel), imaginaire(c.imaginaire) {
    std::cout << "rrrComplex(" << c.reel << "+i" << c.imaginaire << ") @ " << this << " (copie de " << &c << ")" << std::endl;
}

Complex& Complex::operator = (const Complex& c){
    if(this != &c){
        reel = c.reel;
        imaginaire = c.imaginaire;
        std::cout << "op=Complex(" << c.reel << "+i" << c.imaginaire << ") @ " << this << " (affecte par " << &c << ")" << std::endl;
    }
    return *this;
}

Complex::~Complex() {
    std::cout << "---Complex(" << reel << "+i" << imaginaire << ") @ " << this << std::endl;
}

double Complex::getReal() const {
    return reel;
}

double Complex::getImaginary() const {
    return imaginaire;
}

double Complex::Module() const {
    return(std::sqrt(reel * reel + imaginaire * imaginaire));
}

double Complex::Argument() const {
    return(std::atan2(imaginaire, reel));
}

void Complex::printComplex() const {
    std::cout << reel << " + " << "i." << imaginaire << std::endl;
}

void Complex::Echanger(){
    std::swap(reel, imaginaire);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(reel * other.reel - imaginaire * other.imaginaire, reel * other.imaginaire + imaginaire * other.reel);
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(reel + other.reel, imaginaire + other.imaginaire);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(reel - other.reel, imaginaire - other.imaginaire);
}

Complex normalized(const Complex& c) {
    std::cout << "Appel de la fonction normalized pour le complexe: ";
    c.printComplex();
    double argument = c.Argument();
    Complex result(std::cos(argument), std::sin(argument));
    std::cout << "Complexe normalisé (module = 1): ";
    result.printComplex();
    return result;
}

void rotate(Complex& c, double angle) {
    std::cout << "Rotation du complexe: ";
    c.printComplex();
    std::cout << "avec un angle de: " << angle << " radians." << std::endl;
    double newReel = c.getReal() * std::cos(angle) - c.getImaginary() * std::sin(angle);
    double newImaginaire = c.getReal() * std::sin(angle) + c.getImaginary() * std::cos(angle);
    c = Complex(newReel, newImaginaire);
    std::cout << "Complexe après rotation: ";
    c.printComplex();
}

const Complex& maxModule(const Complex& c1, const Complex& c2) {
    std::cout << "Comparaison des modules des complexes:" << std::endl;
    c1.printComplex();
    c2.printComplex();
    if (c1.Module() >= c2.Module()) {
        std::cout << "Le complexe avec le plus grand module est: ";
        c1.printComplex();
        return c1;
    } else {
        std::cout << "Le complexe avec le plus grand module est: ";
        c2.printComplex();
        return c2;
    }
}

void racine_nieme(int n, Complex arr[]) {
    std::cout << "Initialisation des racines " << n << "-ièmes de l'unité:" << std::endl;
    for (int k = 0; k < n; ++k) {
        double angle = 2 * 3.14 * k / n;
        arr[k] = Complex(std::cos(angle), std::sin(angle));
        std::cout << "Racine " << k << ": ";
        arr[k].printComplex();
    }
}