#ifndef DIP_OPTICAL_FLOW_H
#define DIP_OPTICAL_FLOW_H

#include <iostream>
#include <vector>
#include <Eigen/Sparse>

using SpMat = Eigen::SparseMatrix<float>
using T = Eigen::Triplet<float>

namespace dip {
    void buildProblem(
        std::vector<T>& coeffs,
        Eigen::VectorXd& b,
        int n);


}





#endif //DIP_OPTICAL_FLOW_H
