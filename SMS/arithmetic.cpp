#include "matrix.hpp"
#include "helpers.cpp"

template <typename T>
matrix<T> matrix<T>::operator+(matrix<T> mat2) {
    if(!verifyMatricesSymmetry(*this, mat2))
        throw std::runtime_error("Matrices are not symmetrical.");

    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = std::begin(this->__baseMatrix);
    typename std::vector<T>::iterator it2 = std::begin(mat2);
    typename std::vector<T>::iterator it;

    for(it = std::begin(mat_out); it < mat_out.end(); ++it) {
        *it = *it1 + *it2;

        ++it1;
        ++it2;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator+(const T) {
    typename std::vector<T>::iterator it;

    typename std::vector<T>::iterator it2 = std::begin(this->__baseMatrix);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it += *it2;
        ++it2;
    }
    return *this;
}

template <typename T>
void matrix<T>::operator+=(T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(x.__basematrix);
        it < std::end(x.__basematrix); ++it) {
        *it += x;
    }
}

template <typename T>
matrix<T> matrix<T>::operator+=(matrix<T> x) {
    typename std::vector<T>::iterator it;
    typename std::vector<T>::iterator it2 = x.begin();

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it += *it2;

        ++it2;
    }

    return *this;
}

template <typename T>
matrix<T> matrix<T>::operator-(matrix<T>& mat2) {
    if(!verifyMatricesSymmetry(*this, mat2))
        throw std::runtime_error("Matrices are not symmetrical.");

    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = std::begin(this->__baseMatrix);
    typename std::vector<T>::const_iterator it2 = mat2.begin();

    typename std::vector<T>::iterator it;

    for(it = std::begin(mat_out); it < std::end(mat_out); ++it) {
        *it = *it1 - *it2;

        ++it1;
        if(it2 == mat2.end())
            it2 = mat2.begin();
        else
            ++it2;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator-(const T) {
    typename std::vector<T>::iterator it;

    typename std::vector<T>::iterator it2 = std::begin(this->__baseMatrix);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it -= *it2;
        ++it2;
    }
    return *this;
}

template <typename T>
void matrix<T>::operator-=(const T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it -= x;
    }
}
template <typename T>
void matrix<T>::operator-=(matrix<T> x) {

    typename std::vector<T>::iterator it;
    typename std::vector<T>::iterator it2 = x.begin();

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it -= *it2;

        ++it2;
    }
}

template <typename T>
matrix<T> matrix<T>::operator/(matrix<T>& mat2) {
    if(!verifyMatricesOperate(*this, mat2)) {
        typename std::vector<T>::iterator it = std::begin(this->__baseMatrix);
        typename std::vector<T>::iterator it2 = mat2.begin();

        while(it != std::end(this->__baseMatrix)) {
            *it /= *it2;
            ++it;
            ++it2;
        }

        return *this;
    }
    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = std::begin(this->__baseMatrix);
    typename std::vector<T>::iterator it2 = mat2.begin();
    typename std::vector<T>::iterator it;

    for(it = std::begin(mat_out); it < mat_out.end(); ++it) {
        *it = *it1 / *it2;

        ++it1;
        ++it2;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator/(const T) {
    typename std::vector<T>::iterator it;

    typename std::vector<T>::iterator it2 = std::begin(this->__baseMatrix);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it /= *it2;
        ++it2;
    }
    return *this;
}

template <typename T>
void matrix<T>::operator/=(const T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it /= x;
    }
}
template <typename T>
matrix<T> matrix<T>::operator*(matrix<T> mat2) {
    if(!verifyMatricesOperate(*this, mat2)) {
        typename std::vector<T>::iterator it = std::begin(this->__baseMatrix);
        typename std::vector<T>::iterator it2 = mat2.begin();

        while(it != std::end(this->__baseMatrix)) {
            *it *= *it2;
            ++it;
            if(it2 == mat2.end())
                it2 = mat2.begin();
            else
                ++it2;
        }

        return *this;
    }

    matrix<T> mat_out(this->row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = this->begin();
    typename std::vector<T>::iterator it2 = mat2.begin();
    typename std::vector<T>::iterator it;

    for(it = mat_out.begin(); it < mat_out.end(); ++it) {
        *it = *it1 * *it2;

        ++it1;
        if(it2 == mat2.end())
            it2 = mat2.begin();
        else
            ++it2;
    }

    return mat_out;
}

template <typename T>
matrix<T> matrix<T>::operator*(const T) {
    typename std::vector<T>::iterator it;

    typename std::vector<T>::iterator it2 = std::begin(this->__baseMatrix);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it *= *it2;
        ++it2;
    }
    return *this;
}

template <typename T>
matrix<T> matrix<T>::operator*=(const T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it *= x;
    }

    return *this;
}
