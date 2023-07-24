#ifndef QS_MATRIX_H
#define QS_MATRIX_H

#include <vector>
#include <cassert>

template <typename T>
class QSMatrix {
private:
    std::vector<std::vector<T> > mat;
    unsigned rows;
    unsigned cols;

public:
    QSMatrix(unsigned _rows, unsigned _cols, const T& _initial);
    QSMatrix(const QSMatrix<T>& rhs);
    virtual ~QSMatrix();

    QSMatrix<T>& operator=(const QSMatrix<T>& rhs);
    QSMatrix<T> operator+(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator+=(const QSMatrix<T>& rhs);
    QSMatrix<T> operator-(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator-=(const QSMatrix<T>& rhs);
    QSMatrix<T> operator*(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator*=(const QSMatrix<T>& rhs);
    QSMatrix<T> operator+(const T& rhs);
    QSMatrix<T> operator-(const T& rhs);
    QSMatrix<T> operator*(const T& rhs);
    QSMatrix<T> operator/(const T& rhs);

    std::vector<T> operator*(const std::vector<T>& rhs);
    std::vector<T> diag_vec();

    T& operator() (const unsigned& row, const unsigned& col);
    const T& operator() (const unsigned& row, const unsigned& col) const;

    unsigned get_rows() const;
    unsigned get_cols() const;

};


template<typename T>
QSMatrix<T>::QSMatrix(unsigned _rows, unsigned _cols, const T& _initial) {
    mat.resize(_rows);
    for (auto &row : mat) {
        row.resize(_cols, _initial);
    }
    rows = _rows;
    cols = _cols;
}

template<typename T>
QSMatrix<T>::QSMatrix(const QSMatrix<T>& rhs) : mat(rhs.mat), rows(rhs.rows), cols(rhs.cols) {}

template<typename T>
QSMatrix<T>::~QSMatrix() {}

template<typename T>
QSMatrix<T>& QSMatrix<T>::operator=(const QSMatrix<T>& rhs) {
    if (&rhs == this)
        return *this;

    mat = rhs.mat;
    rows = rhs.rows;
    cols = rhs.cols;

    return *this;
}

template<typename T>
QSMatrix<T> QSMatrix<T>::operator+(const QSMatrix<T>& rhs) {
    assert(rows == rhs.rows && cols == rhs.cols);

    QSMatrix result(rows, cols, 0.0);
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] + rhs(i,j);
        }
    }
    return result;
}

template<typename T>
QSMatrix<T>& QSMatrix<T>::operator+=(const QSMatrix<T>& rhs) {
    assert(rows == rhs.rows && cols == rhs.cols);

    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            this->mat[i][j] += rhs(i,j);
        }
    }
    return *this;
}


template<typename T>
QSMatrix<T> QSMatrix<T>::operator*(const T& rhs) {
    QSMatrix result(rows, cols, 0.0);
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] * rhs;
        }
    }
    return result;
}

template<typename T>
QSMatrix<T> QSMatrix<T>::operator/(const T& rhs) {
    assert(rhs != 0);
    QSMatrix result(rows, cols, 0.0);
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] / rhs;
        }
    }
    return result;
}

template<typename T>
std::vector<T> QSMatrix<T>::operator*(const std::vector<T>& rhs) {
    assert(cols == rhs.size());
    std::vector<T> result(rhs.size(), 0.0);
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result[i] += this->mat[i][j] * rhs[j];
        }
    }
    return result;
}

template<typename T>
std::vector<T> QSMatrix<T>::diag_vec() {
    std::vector<T> result(rows, 0.0);
    for (unsigned i=0; i<rows; i++) {
        result[i] = this->mat[i][i];
    }
    return result;
}

template<typename T>
T& QSMatrix<T>::operator()(const unsigned& row, const unsigned& col) {
    return this->mat[row][col];
}

template<typename T>
const T& QSMatrix<T>::operator()(const unsigned& row, const unsigned& col) const {
    return this->mat[row][col];
}

template<typename T>
unsigned QSMatrix<T>::get_rows() const {
    return this->rows;
}

template<typename T>
unsigned QSMatrix<T>::get_cols() const {
    return this->cols;
};


#endif
