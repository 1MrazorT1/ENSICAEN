#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
    private:
        int n;
        int m;
        double* tab;
    
    public:
        Matrix();
        Matrix(int n, int m);
        ~Matrix();
        Matrix(const Matrix& A);
        Matrix(Matrix&& A);
        Matrix& operator=(const Matrix& A);
        Matrix& operator=(Matrix&& other);
        double* operator[](int indice);
        double get(int i, int j) const;
        void set(int i, int j, double val);
        Matrix operator*(const Matrix& other) const;
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator-() const;
        bool isCarree() const;
        Matrix transpose() const;
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
        friend std::istream& operator>>(std::istream& is, Matrix& mat);
        void printMatrix() const;
        static Matrix identite_gen(int taille);
};

#endif