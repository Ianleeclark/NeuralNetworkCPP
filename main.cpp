#include <iostream>
#include <cmath>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include "SMS/matrix.cpp"

//TODO(ian): Make a function to iterate through the matrices so I'm not 
// Reusing so much ugly code.

template <typename T>
matrix<T> matrixExp(matrix<T> x) {
    //TODO(ian): Iterator instead of ugly for loops.
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
matrix<T> kroneckerProduct(const matrix<T>& x, const matrix<T>& y) {
    //TODO(ian): Finish this function C(i,j) = A(i,j)B for all A & B
    matrix<T> tmp(1,1,0);
    return tmp;
}

template <typename T, typename X>
matrix<T> prod(matrix<T>& x, X& y) {
    if(verifyMatricesSymmetry(x, y))
        return hadamardProduct(x, y);
    else 
        kroneckerProduct(x, y);
    return x;
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
    matrix<T> y = x;
    std::vector<T> vec_out = {1.0, 1.0, 1.0, 1.0};
    matrix<T> tmp(x.row, x.col, vec_out[0]);
    if(deriv) {
        y -= tmp;
        return x * y;
    }
    x = tmp + matrixExp(x);
    return (tmp / x);
}

matrix<double> trainNetwork(const matrix<double> &input,
                            matrix<double> &output,
                            matrix<double> &weights) {
    matrix<double> l0 = input; // size: 12 (4, 3)
    matrix<double> tmp = l0 * weights; // 12 (4,3) * 4 (4, 1)
    matrix<double> l1 = nonlin(tmp); // 12 (4, 3) * 4 (4, 1)
    matrix<double> l1error = output - l1; // 4 (4, 1) -
    matrix<double> result = nonlin(l1, true);
    matrix<double> l1delta = prod(l1error, result);

    result = trans(l0);
    weights.operator+=(prod(result, l1delta));

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
    input.printMatrix();
    input.transm().printMatrix();

    matrix<double> weights{3, 1, 0};
    matrix<double> out{4, 1, 0};

    /*matrixFillRandomReal(weights);

    for(int i = 0; i < 10000; ++i) {
        out = trainNetwork(input, output, weights);
    }
    out.printMatrix();
*/
    return 0;
}