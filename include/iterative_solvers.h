//
// Created by HayleySong on 10/25/17.
//

#ifndef DIP_ITERATIVE_SOLVERS_H
#define DIP_ITERATIVE_SOLVERS_H

#include <Eigen/Dense>
#include <iostream>
#include "arithematic.h"

//todo: move implementation to .cpp file
//    : use #include NAME.cpp at the end of this header  if
//      using templates


namespace dip {

    void gauss_seidel(
        const Eigen::MatrixXf &A,
        const Eigen::VectorXf &b,
        const Eigen::VectorXf &x0,
        Eigen::VectorXf &x,
        const int maxIter=10000,
        const float precision=1e-6,
        bool isVerbose=false)
    {
      assert( A.rows() == A.cols() );
      int n = A.rows();
      Eigen::VectorXf x_new(n), diffs(n), zeros(n);
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

        if (isVerbose) {
          std::cout << "\n---Iter: " << iter << std::endl;
          std::cout << "x_new: " << x_new.transpose() << std::endl;
        }

        diffs = (x_new - x);
        x = x_new;
      }

      std::cout << "diff: " << diffs.transpose() << std::endl;
    }
}











#endif //DIP_ITERATIVE_SOLVERS_H
