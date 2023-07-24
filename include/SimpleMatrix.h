#ifndef SIMPLEMATRIX_H
#define SIMPLEMATRIX_H

#include <vector>
#include <complex>

template <typename Type = double> class SimpleMatrix {
    private:
        std::vector<std::vector<Type> > mat; // Use a vector of vector to store values

    public:
        SimpleMatrix(); //Default constructor
        SimpleMatrix(const int& rows, const int& cols, const Type& val);
        SimpleMatrix(const SimpleMatrix<Type>& _rhs); //Copy constructor

        SimpleMatrix<Type>& operator= (const SimpleMatrix<Type>& _rhs); //Assignment operator overloaded

        virtual ~SimpleMatrix(); //Destructor

        //Access to the matrix values directly, via row and col indices
        std::vector<std::vector<Type> > get_mat() const;
        Type& value(const int& row, const int& col);

};

/* Template definition */

//Default constructor
template <typename Type>
SimpleMatrix<Type>::SimpleMatrix(){}

//Constructor spe
template <typename Type>
SimpleMatrix<Type>::SimpleMatrix(const int& rows, const int& cols,
                                 const Type& val) {
    for (int i=0; i<rows; i++) {
        std::vector<Type> col_vec (cols, val);
        mat.push_back(col_vec);
    }
}

//Copy constructor
template <typename Type>
SimpleMatrix<Type>::SimpleMatrix(const SimpleMatrix<Type>& _rhs) {
    mat = _rhs.get_mat();
}

//Overloaded assignment operator
template <typename Type>
SimpleMatrix<Type>& SimpleMatrix<Type>::operator= (const SimpleMatrix<Type>& _rhs) {
    if (this == &_rhs) return *this;
    mat = _rhs.get_mat();
    return *this;
}

//Destructor
template <typename Type>
SimpleMatrix<Type>::~SimpleMatrix() {}

//Matrix access
template <typename Type>
SimpleMatrix<Type> SimpleMatrix<Type>::get_mat() const {
    return mat;
}

template <typename Type>
Type& SimpleMatrix<Type>::value(const int& row, const int& col) {
    return mat[row][col];
}

#endif // SIMPLEMATRIX_H
