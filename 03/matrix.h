#pragma once

#include <iostream>

class MatrixRow {
private:
    size_t n;
    int *row;
public:
    MatrixRow(size_t n_);
    size_t getSize() const;  

    int& operator[] (size_t i);
    const int& operator[] (size_t i) const;
    MatrixRow& operator*= (int x);
    MatrixRow& operator= (const MatrixRow& m);
    MatrixRow operator+ (const MatrixRow& m) const;
    bool operator== (const MatrixRow& m) const;
    bool operator!= (const MatrixRow& m) const;

    ~ MatrixRow();
};


class Matrix {
private:
    size_t nrows, ncolumns;
    MatrixRow** mproxy;
public:
    Matrix(size_t nrows_, size_t ncolumns_);
    size_t getRows() const;
    size_t getColumns() const;

    MatrixRow& operator[] (size_t i);
    const MatrixRow& operator[] (size_t i) const;
    Matrix& operator*= (int x);
    Matrix operator+ (const Matrix& m) const;
    bool operator== (const Matrix& m) const;
    bool operator!= (const Matrix& m) const;

    ~Matrix();
};

std::ostream& operator<< (std::ostream& out, const Matrix& matrix);
std::ostream& operator<< (std::ostream& out, const MatrixRow& row);
