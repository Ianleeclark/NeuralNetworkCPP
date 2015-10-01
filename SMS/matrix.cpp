#include "matrix.hpp"

template <typename Container, typename ConstIterator>
typename Container::iterator remove_constness(Container& c, ConstIterator it) {
    // See
    // http://stackoverflow.com/questions/765148/how-to-remove-constness-of-const-iterator

    return c.erase(it, it);
}

template <typename T>
int verifyMatricesSymmetry(const matrix<T>& mat1, const matrix<T>& mat2) {
    if(mat1.row == mat2.row && mat1.col == mat2.col)
        return 1;
    else
        return 0;
}

template <typename T>
typename std::vector<T>::iterator matrix<T>::begin() {
    return std::begin(this->__baseMatrix);
}

template <typename T>
typename std::vector<T>::iterator matrix<T>::end() {
    return std::end(this->__baseMatrix);
}

template <typename T>
typename std::vector<T>::iterator matrix<T>::begin() const{
    return std::begin(this->__baseMatrix);
}

template <typename T>
typename std::vector<T>::iterator matrix<T>::end() const {
    return std::end(this->__baseMatrix);
}


template <typename T>
matrix<T>::matrix(const unsigned int rows,
                  const unsigned int cols,
                  std::vector<T> matrixin) {
    if(matrixin.empty())
        throw std::invalid_argument("Input matrix is empty.");
    if(rows <= 0 || cols <= 0)
        throw std::invalid_argument("Row and col must be greater than 0.");
    if(rows * cols != matrixin.size()) {
        throw std::invalid_argument("Vector too small.");
    }


    this->row = rows;
    this->col = cols;

    typename std::vector<T>::iterator it;

    for(it = std::begin(matrixin); it < std::end(matrixin); ++it) {
        __baseMatrix.push_back(*it);
    }
}

template <typename T>
matrix<T>::matrix(const unsigned int row,
                  const unsigned int col,
                  const int matrixvalue) {
    if(matrixvalue == 0)
        throw std::invalid_argument("Input matrix is empty.");
    if(row <= 0 || col <= 0)
        throw std::invalid_argument("Row and column must be greater than 0.");

    this->row = row;
    this->col = col;

    for(int x = 0; x <= row; ++x) {
        for(int y = 0; y <= col; ++y) {
            __baseMatrix.push_back(matrixvalue);
        }
    }
}

template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& mat) {
    if(this->__baseMatrix != mat.__baseMatrix)
        this->__baseMatrix = mat.__baseMatrix;
    return *this;
}

template <typename T>
inline std::ostream& matrix<T>::operator<<(std::ostream& os) {
    //TODO(ian): Print whole vector -- Maybe done
    typename std::vector<T>::iterator it;
    
    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it)
        os << *it;
    return os;
}

template <typename T>
void matrix<T>::printMatrix() {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        std::cout << *it << std::endl;
    }
}

template <typename T>
T& matrix<T>::operator[](const std::pair<const unsigned int,
                         const unsigned int> Index) {
    if(col == 0) {
        return this->__baseMatrix[Index.first];

    } else
        return this->__baseMatrix[Index.first * Index.second -1];
}

template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& mat2) {
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
void matrix<T>::operator+=(const T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it += x;
    }
}

template <typename T>
void matrix<T>::operator+=(const matrix<T>& x) {

    typename std::vector<T>::iterator it;
    typename std::vector<T>::iterator it2 = std::begin(x);

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it += *it2;

        ++it2;
    }
}

template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& mat2) {
    if(!verifyMatricesSymmetry(*this, mat2))
        throw std::runtime_error("Matrices are not symmetrical.");

    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = std::begin(this->__baseMatrix);
    typename std::vector<T>::iterator it2 = std::begin(mat2);
    typename std::vector<T>::iterator it;

    for(it = std::begin(mat_out); it < std::end(mat_out); ++it) {
        *it = *it1 - *it2;

        ++it1;
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
matrix<T> matrix<T>::operator/(const matrix<T>& mat2) {
    if(!verifyMatricesSymmetry(*this, mat2))
        throw std::runtime_error("Matrices are not symmetrical.");

    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = std::begin(this->__baseMatrix);
    typename std::vector<T>::iterator it2 = std::begin(mat2);
    typename std::vector<T>::iterator it;

    for(it = std::begin(mat_out); it < mat_out.end(); ++it) {
        *it = *it1 / *it2;

        ++it1;
        ++it2;
    }
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
    if(!verifyMatricesSymmetry(*this, mat2))
        throw std::runtime_error("Matrices are not symmetrical.");

    matrix<T> mat_out(mat2.row, mat2.col, 0);

    typename std::vector<T>::iterator it1 = this->begin();
    typename std::vector<T>::iterator it2;
    typename std::vector<T>::iterator it;

    /*
    for(it = mat_out.begin(); it < mat_out.end(); ++it) {
        *it = *it1 * *it2;

        ++it1;
        ++it2;
    }
    */

    std::transform(this->begin(), this->end(), mat2.begin(), mat_out.begin());

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
void matrix<T>::operator*=(const T x) {
    typename std::vector<T>::iterator it;

    for(it = std::begin(this->__baseMatrix);
        it < std::end(this->__baseMatrix); ++it) {
        *it *= x;
    }
}