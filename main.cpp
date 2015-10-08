#include <iostream>
#include <cmath>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include "SMS/matrix.cpp"

template <typename T>
matrix<T> matrixExp(matrix<T> x) {
    typename std::vector<T>::iterator it;
    for(it = std::begin(x); it < std::end(x); ++it) {
        *it = exp(-*it);
    }
    return x;
}

template <typename T>
matrix<T> hadamardProduct(matrix<T>& x, matrix<T>& y) {
    //TODO(ian): Fix all this nonsense. We don't need to make tmp and tmp_int
    typename std::vector<T>::iterator itx;
    matrix<T> tmp(x.row, y.col, 0);
    typename std::vector<T>::iterator tmp_it = std::begin(tmp);
    typename std::vector<T>::iterator ity = y.begin();

    for(itx = x.begin(); itx != x.begin(); ++itx) {
        *tmp_it = *itx * *ity;
        std::cout << *tmp_it << std::endl;
        ++tmp_it;
        ++ity;
    }
    //tmp.printMatrix();
    return tmp;
}

template <typename T>
matrix<T> kroneckerProduct(matrix<T>& x, matrix<T>& y) {
    //TODO(ian): Finish this function C(i,j) = A(i,j)B for all A & B

    matrix<T> mat_out(x.row, y.col, 0);
    typename std::vector<T>::iterator it_x = x.begin();
    typename std::vector<T>::iterator it_m = mat_out.begin();

    while(it_m != mat_out.end()) {
        *it_m = y.operator*(*it_x);

        ++it_m;
        ++it_x;
    }
    return mat_out;
}

template <typename T>
matrix<T> prod(matrix<T>& x, matrix<T>& y) {
    if(verifyMatricesSymmetry(x, y))
        return hadamardProduct(x, y);
    else
        return simpleMultiply(x, y);
}

/*
This function is used to create a matrix with a uniform range (0,1]
Which will be used for the creation of the initial weights.
*/
template <typename T>
void matrixFillRandomReal(matrix<T>& weights) {
    // Create the Mersenne twister and assign a uniform distribution range.
    boost::mt19937 rng;
    boost::uniform_real<> range(0.0, 1.0);
    rng.seed(1);

    boost::variate_generator<boost::mt19937,
            boost::uniform_real<>> roll(rng, range);

    typename std::vector<T>::iterator it;
    for(it = weights.begin(); it < weights.end(); ++it) {
        *it = 2 * roll() - 1;
    }
}

template <typename T>
matrix<T> nonlin(matrix<T> x, bool deriv=false) {
    matrix<T> tmp(x.row, x.col, 1.0);

    if(deriv) {
        matrix<T> y = x;
        return x * (tmp - x);

        return x * y;
    }

    x = tmp + matrixExp(x);

    return (tmp / x);
}

template <typename T>
matrix<T> trainNetwork(const matrix<T>& input,
                            matrix<T>& output,
                            matrix<T>& weights) {

    matrix<T> l0 = input;

    matrix<T> l1 = nonlin(prod(l0, weights));
    matrix<T> l1error = output - l1;

    matrix<T> l1delta = l1error * nonlin(l1, true);

    matrix<T> result = l0.transm();
    weights += prod(result, l1delta);

    return l1;
}

int main() {
    std::vector<double> vec = {0.0,0.0,1.0,
                               0.0,1.0,1.0,
                               1.0,0.0,1.0,
                               1.0,1.0,1.0};

    std::vector<double> vec_out = {0,
                                   0,
                                   1,
                                   1};

    matrix<double> output(4, 1, vec_out);
    matrix<double> input(4, 3, vec);

    matrix<double> weights{3, 1, 0};
    matrix<double> out{4, 1, 0};

    matrixFillRandomReal(weights);

    for(int i = 0; i < 10000; ++i) {
        out = trainNetwork(input, output, weights);
    }
    out.printMatrix();

    return 0;
}