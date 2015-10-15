#include "matrix.hpp"
template <typename T>
int verifyMatricesSymmetry(const matrix<T>& mat1, const matrix<T>& mat2) {
    if(mat1.row == mat2.row && mat1.col == mat2.col)
        return 1;
    else
        return 0;
}

template <typename T>
bool verifyMatricesOperate(const matrix<T>& x, const matrix<T>& y) {
    return x.col == y.row;
}


