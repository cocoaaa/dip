#ifndef DIP_GAUSS_SEIDEL_H
#define DIP_GAUSS_SEIDEL_H

#include <Eigen/Dense>
#include <iostream>
#include "arithematic.h"


namespace dip {

    template <typename VecT, typename MatT>
    void gauss_seidel(
        const Eigen::MatrixBase<MatT> &A,
        const Eigen::MatrixBase<VecT> &b,
        const Eigen::MatrixBase<VecT> &x0,
        Eigen::MatrixBase<VecT> &x,
        const int maxIter=10000,
        const float precision=1e-6)
    {
      assert( A.rows() == A.cols() );
      int n = A.rows();
      Eigen::MatrixBase<VecT> x_new(n), diffs(n), zeros(n);
      x_new.fill(0);
      zeros.fill(0);
      diffs.fill(1e+7);

      x = x0;
      for (int iter=0; iter<maxIter; ++iter){
        if (iter >0 && dip::isAllClose(diffs, zeros, precision)){
          std::cout << "precision reached" << std::endl;
          break;
        }
        for (int i=0; i < A.rows(); ++i){
          float s(0.0f);
          for (int j=0; j < A.cols(); ++j){
            if (j<i){
              s += A(i,j) * x_new(j);
            } else if (j > i){
              s += A(i,j) * x(j);
            }
          }
          x_new(i) = (b(i) - s)/A(i,i);
        }

        std::cout << "\n---Iter: " << iter << std::endl;
        std::cout << "x_new: " << x_new.transpose() << std::endl;

//        diffs = (x_new.template - x);
        diffs = (x_new - x);
        x = x_new;
      }

      std::cout << "diff: " << diffs.transpose() << std::endl;
    }
}
#endif //DIP_GAUSS_SEIDEL_H
