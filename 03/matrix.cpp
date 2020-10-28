#include "matrix.h"

MatrixRow::MatrixRow(size_t n_)
    : n(n_) {
        row = new int[n];
}

size_t MatrixRow::getSize() const {
    return n;
}
    
int& MatrixRow::operator[] (size_t i) {
    if (i >= n) {
        throw std::out_of_range("");
    }
    return row[i];
}

const int& MatrixRow::operator[] (size_t i) const{
    if (i >= n) {
        throw std::out_of_range("");
    }
    return row[i];
}

MatrixRow& MatrixRow::operator= (const MatrixRow& m_row) {
    for (size_t i = 0; i < n; i++) {
        row[i] = m_row[i];
    }
    return *this;
}

MatrixRow& MatrixRow::operator*= (int x) {
    for (size_t i = 0; i < n; i++) {
        row[i] *= x;
    }
    return *this;
}

MatrixRow MatrixRow::operator+ (const MatrixRow& m_row) const {
    MatrixRow m_row_sum = MatrixRow(n);
    for (size_t i = 0; i < n; i++) {
        m_row_sum[i] = row[i] + m_row[i];
    }
    return m_row_sum;
}

bool MatrixRow::operator== (const MatrixRow& m_row) const {
    for (size_t i = 0; i < n; i++) {
        if (row[i] != m_row[i]) {
            return false;
        }
    }
    return true;
}

bool MatrixRow::operator!= (const MatrixRow& m_row) const {
    for (size_t i = 0; i < n; i++) {
        if (row[i] != m_row[i]) {
            return true;
        }
    }
    return false;
}

MatrixRow::~ MatrixRow() {
    delete [] row;
}


Matrix::Matrix(size_t nrows_, size_t ncolumns_)
    : nrows(nrows_)
    , ncolumns(ncolumns_) {
        mproxy = new MatrixRow* [nrows];
        for (size_t i = 0; i < nrows; i++) {
            mproxy[i] = new MatrixRow(ncolumns);
        }
}
    
size_t Matrix::getRows() const {
    return nrows;
}

size_t Matrix::getColumns() const {
    return ncolumns;
}

MatrixRow& Matrix::operator[] (size_t i) {
    if (i >= nrows) {
        throw std::out_of_range("");
    }
    return *mproxy[i];
}

const MatrixRow& Matrix::operator[] (size_t i) const {
    if (i >= nrows) {
        throw std::out_of_range("");
    }
    return *mproxy[i];
}

Matrix& Matrix::operator*= (int x) {
    for (size_t i = 0; i < nrows; i++) {
        *mproxy[i] *= x;
    }
    return *this;
}

Matrix Matrix::operator+ (const Matrix& m) const {
    if (m.getRows() != nrows || m.getColumns() != ncolumns) {
        throw std::runtime_error("");
    }
    Matrix m_sum = Matrix(nrows, ncolumns);
    for (size_t i = 0; i < nrows; i++) {
        m_sum[i] = *mproxy[i] + m[i];
    }
    return m_sum;
}

bool Matrix::operator== (const Matrix& m) const {
    if (m.getRows() != nrows || m.getColumns() != ncolumns) {
        return false;
    }
    for (size_t i = 0; i < nrows; i++) {
        if (*mproxy[i] != m[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!= (const Matrix& m) const {
    if (m.getRows() != nrows || m.getColumns() != ncolumns) {
        return true;
    }
    for (size_t i = 0; i < nrows; i++) {
        if (*mproxy[i] != m[i]) {
            return true;
        }
    }
    return false;
}

Matrix::~Matrix() {
    for (size_t i = 0; i < nrows; i++) {
        mproxy[i]->~MatrixRow();
    }
    delete [] mproxy;
}

std::ostream& operator<< (std::ostream& out, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.getRows(); i++) {
        out << matrix[i];
    }
    return out;
}

std::ostream& operator<< (std::ostream& out, const MatrixRow& row) {
    for (size_t i = 0; i < row.getSize(); i++) {
        std::cout << row[i] << " ";
    }
    std::cout << std::endl;
    return out;
}
