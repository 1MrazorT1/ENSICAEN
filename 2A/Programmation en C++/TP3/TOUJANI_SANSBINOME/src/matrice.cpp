#include "../include/matrice.h"
#include <cstring>
#include <stdexcept>
#include <iomanip>

Matrix::Matrix() : n(0), m(0), tab(nullptr) {
    std::cout << "Constructeur par défaut appele\n";
}

Matrix::Matrix(int n, int m) : n(n), m(m) {
    tab = new double[n * m]();
    std::cout << "Constructeur avec dimensions (" << n << ", " << m << ") appelé\n";
}

Matrix::~Matrix() {
    delete[] tab;
    std::cout << "Destructeur appele\n";
}

Matrix::Matrix(const Matrix& A) : n(A.n), m(A.m) {
    tab = new double[n * m];
    std::memcpy(tab, A.tab, n * m * sizeof(double));
    std::cout << "Constructeur par copie appele\n";
}

Matrix::Matrix(Matrix&& A) : n(A.n), m(A.m), tab(A.tab) {
    A.tab = nullptr;
    A.n = 0;
    A.m = 0;
    std::cout << "Constructeur par déplacement appele\n";
}

Matrix& Matrix::operator=(const Matrix& A) {
    if (this != &A) {
        delete[] tab;
        n = A.n;
        m = A.m;
        tab = new double[n * m];
        std::memcpy(tab, A.tab, n * m * sizeof(double));
        std::cout << "Affectation par copie appelee\n";
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
    if (this != &other) {
        delete[] tab;
        n = other.n;
        m = other.m;
        tab = other.tab;
        other.tab = nullptr;
        other.n = 0;
        other.m = 0;
        std::cout << "Affectation par deplacement appelee\n";
    }
    return *this;
}

double* Matrix::operator[](int indice) {
    if (indice >= n || indice < 0) {
        throw std::out_of_range("Index out of range");
    }
    return &tab[indice * m];
}

double Matrix::get(int i, int j) const {
    if (i >= n || j >= m || i < 0 || j < 0) {
        throw std::out_of_range("Index out of range");
    }
    return tab[i * m + j];
}

void Matrix::set(int i, int j, double val) {
    if (i >= n || j >= m || i < 0 || j < 0) {
        throw std::out_of_range("Index out of range");
    }
    tab[i * m + j] = val;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (m != other.n) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }
    Matrix result(n, other.m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < other.m; ++j) {
            for (int k = 0; k < m; ++k) {
                result.tab[i * other.m + j] += tab[i * m + k] * other.tab[k * other.m + j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (n != other.n || m != other.m) {
        throw std::invalid_argument("Matrix dimensions do not match for addition");
    }
    Matrix result(n, m);
    for (int i = 0; i < n * m; ++i) {
        result.tab[i] = tab[i] + other.tab[i];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (n != other.n || m != other.m) {
        throw std::invalid_argument("Matrix dimensions do not match for subtraction");
    }
    Matrix result(n, m);
    for (int i = 0; i < n * m; ++i) {
        result.tab[i] = tab[i] - other.tab[i];
    }
    return result;
}

Matrix Matrix::operator-() const {
    Matrix result(n, m);
    for (int i = 0; i < n * m; ++i) {
        result.tab[i] = -tab[i];
    }
    return result;
}

bool Matrix::isCarree() const {
    return n == m;
}

Matrix Matrix::transpose() const {
    Matrix result(m, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result.tab[j * n + i] = tab[i * m + j];
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.n; ++i) {
        os << "[";
        for (int j = 0; j < mat.m; ++j) {
            os << std::setw(8) << mat.get(i, j);
            if (j < mat.m - 1) {
                os << ", ";
            }
        }
        os << "]\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& mat) {
    for (int i = 0; i < mat.n; ++i) {
        for (int j = 0; j < mat.m; ++j) {
            double val;
            is >> val;
            mat.set(i, j, val);
        }
    }
    return is;
}

void Matrix::printMatrix() const {
    std::cout << *this;
}

Matrix Matrix::identite_gen(int taille) {
    Matrix result(taille, taille);
    for (int i = 0; i < taille; ++i) {
        result.set(i, i, 1.0);
    }
    return result;
}
