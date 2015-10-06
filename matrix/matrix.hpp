#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>

using namespace boost::numeric::ublas;

template <typename T>
matrix<T> matrixExp(matrix<T> x);

template <typename T>
matrix<T> matrixFill(size_t row, size_t col, std::vector<T> vectorData);

template <typename T>
matrix<T> matrixFillRandomReal(matrix<T> &weights);

template <typename T>
std::vector<T> matrixToVector(matrix<T> matrixIn);

template <typename T>
matrix<T> matrixSimpleDivide(const matrix<T> &x, const matrix<T> &y);

template <typename T>
matrix<T> matrixSimpleSubtract(const matrix<T> &x, const matrix<T> &y);

template <typename T>
matrix<T> matrixSimpleAddition(const matrix<T> &x, const matrix<T> &y);





template <typename T>
matrix<T> matrixExp(matrix<T> x) {
    for (unsigned i = 0; i < x.size1(); ++i) {
        for (unsigned j = 0; j < x.size2(); ++j) {
            x(i, j) = exp(-x(i, j));
        }
    }
    return x;
}

template <typename T>
matrix<T> matrixSimpleMultiply(const matrix<T> &x, const matrix<T> &y) {
    if(x.size1() == y.size1() && x.size2() == y.size2()) {
        matrix<T> tmp {x.size1(), x.size2()};
        //TODO(ian): generalize the function and determine which size to iterate through
        //TODO(ian): implement error handling on returns so g++ doesn't scream at me
        for(size_t i = 0; i < x.size1(); ++i) {
            tmp(i, 0) = x(i,0) * y(i, 0);
        }
        return tmp;
    } else {
        std::cout << "Failed to multiply due to imbalanced matrices." << std::endl;
    }
}

template <typename T>
matrix<T> matrixSimpleDivide(const matrix<T> &x, const matrix<T> &y) {
    if(x.size1() == y.size1() && x.size2() == y.size2()) {
        matrix<T> tmp {x.size1(), x.size2()};
        //TODO(ian): generalize the function and determine which size to iterate through
        for(size_t i = 0; i < x.size1(); ++i) {
            if(y(i, 0) !=  0)
                tmp(i, 0) = x(i,0) / y(i, 0);
            else
                tmp(i, 0) == 0;
        }
        return tmp;
    } else {
        std::cout << "Failed to div due to imbalanced matrices." << std::endl;
    }
}

template <typename T>
matrix<T> matrixSimpleSubtract(const matrix<T> &x, const matrix<T> &y) {
    if(x.size1() == y.size1() && x.size2() == y.size2()) {
        matrix<T> tmp {x.size1(), x.size2()};
        //TODO(ian): generalize the function and determine which size to iterate through
        for(size_t i = 0; i < x.size1(); ++i) {
            tmp(i, 0) = x(i,0) - y(i, 0);
        }
        return tmp;
    } else {
        std::cout << "Failed to subtract due to imbalanced matrices." << std::endl;
    }
}

template <typename T>
matrix<T> matrixSimpleAddition(const matrix<T> &x, const matrix<T> &y) {
    if(x.size1() == y.size1() && x.size2() == y.size2()) {
        matrix<T> tmp {x.size1(), x.size2()};
        //TODO(ian): generalize the function and determine which size to iterate through
        for(size_t i = 0; i < x.size1(); ++i) {
            tmp(i, 0) = x(i,0) + y(i, 0);
        }
        return tmp;
    } else {
        std::cout << "Failed to subtract due to imbalanced matrices." << std::endl;
    }
}

template <typename T>
std::vector<T> matrixToVector(matrix<T> matrixIn) {
    std::vector<T> vec;
    if(matrixIn.size1() == 1) {
        std::cout << " test" << std::endl;
        for(size_t j = 0; j < matrixIn.size2(); ++j) {
            vec.push_back(matrixIn(1, j));
        }
    } else if(matrixIn.size2() == 1) {
        for(int i = 0; i < matrixIn.size1(); ++i)
            vec.push_back(matrixIn(i, 1));
    } else {
        return nullptr;
    }
}

template <typename T>
matrix<T> matrixFill(size_t row, size_t col, std::vector<T> vectorData) {
    matrix<T> matrixOut {row, col};
    std::vector<double>::iterator it = std::begin(vectorData);

    for (unsigned i = 0; i < matrixOut.size1 (); ++i) {
        for (unsigned j = 0; j < matrixOut.size2 (); ++j) {
            matrixOut (i,j) = *it;
            ++it;
        }
    }
    return matrixOut;
}

template <typename T>
matrix<T> matrixFillRandomReal(matrix<T> &weights) {
    // Create the Mersenne twister and assign a uniform distribution range.
    boost::mt19937 rng;
    boost::uniform_real<> range(0.0, 1.0);
    rng.seed(1);

    boost::variate_generator<boost::mt19937, boost::uniform_real<>>
            roll(rng, range);

    for (unsigned i = 0; i < weights.size1(); ++ i) {
        for (unsigned j = 0; j < weights.size2(); ++j) {
            weights(i, j) = 2 * roll() - 1;
        }
    }
    return weights;
}

#endif