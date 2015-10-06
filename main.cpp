#include <iostream>
#include <cmath>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include "SMS/matrix.cpp"

//TODO(ian): Make a function to iterate through the matrices so I'm not
// Reusing so much ugly code.

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
    matrix<T> tmp(x.row, x.col, 0);
    typename std::vector<T>::iterator tmp_it = std::begin(tmp);
    typename std::vector<T>::iterator ity = y.begin();

    for(itx = x.begin(); itx < x.begin(); ++itx) {
        *tmp_it = *itx * *ity;
    }
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

template <typename T>
matrix<T> trans(matrix<T> x) {
    matrix<T> tmp(x.row, x.col, 0);

    typename std::vector<T>::iterator it;
    typename std::vector<T>::iterator it_tmp = std::begin(tmp);

    //TODO(ian): The following line contains something really hacky
    for(it = std::begin(x); it < x.end(); ++(++it)) {
        *it_tmp = *it;
        *(it_tmp + 1) = *(it - 1);

        ++(++it_tmp);
    }
    return tmp;
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
    for(it = std::begin(weights); it < weights.end(); ++it) {
        *it = 2 * roll() - 1;
    }
}

template <typename T>
matrix<T> nonlin(matrix<T> x, bool deriv=false) {
    matrix<T> tmp(x.row, x.col, 1.0);

    if(deriv) {
        matrix<T> y = x;
        y -= tmp;

        return x * y;
    }

    x = tmp + matrixExp(x);

    return (tmp / x);
}

matrix<double> trainNetwork(const matrix<double>& input,
                            matrix<double>& output,
                            matrix<double>& weights) {

    matrix<double> l0 = input;
    matrix<double> tmp(l0.row,  weights.col, 0);
    tmp = prod(l0, weights);
    tmp.printMatrix();

    matrix<double> l1 = nonlin(tmp);
    matrix<double> l1error = output - l1;

    matrix<double> result = nonlin(l1, true);
    matrix<double> l1delta = l1error * result;

    result = l0.transm();
    weights += (result * l1delta);

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

    for(int i = 0; i < 3; ++i) {
        out = trainNetwork(input, output, weights);
    }
    out.printMatrix();

    return 0;
}