#include <iostream>
#include "matrix/matrix.hpp"

template <typename T>
matrix<T> nonlin(matrix<T> x, bool deriv=false) {
    matrix<T> y = x;
    std::vector<T> vec_out = {1.0, 1.0, 1.0, 1.0};
    matrix<T> tmp = matrixFill(x.size1(), x.size2(), vec_out);
    if(deriv) {
        y = matrixSimpleSubtract(tmp, y);
        return matrixSimpleMultiply(x, y);
    }
    x = matrixSimpleAddition(tmp, matrixExp(x));
    return matrixSimpleDivide(tmp, x);
}

matrix<double> trainNetwork(const matrix<double> &input, const matrix<double> &output, matrix<double> &weights) {
    matrix<double> l0 = input;
    matrix<double> tmp = prod(l0, weights);
    matrix<double> l1 = nonlin(tmp);
    matrix<double> l1error = output - l1;
    matrix<double> l1delta = element_prod(l1error, nonlin(l1, true));

    weights += prod(trans(l0), l1delta);
    return l1;
}

int main() {
    std::vector<double> vec = {0.0,0.0,1.0, 0.0,1.0,1.0, 1.0,0.0,1.0, 1.0,1.0,1.0};
    std::vector<double> vec_out = {0,0,1,1};

    const matrix<double> output = matrixFill(4, 1, vec_out);
    const matrix<double> input = matrixFill(4, 3, vec);

    matrix<double> weights {3, 1};
    matrix<double> out {4,1};

    matrixFillRandomReal(weights);

    for(int i = 0; i < 10000; ++i) {
        out = trainNetwork(input, output, weights);
    }
    std::cout << out << std::endl;

    return 0;
}