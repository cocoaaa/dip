#include <iostream>
#include <Eigen/Dense>

#include "print.h"
#include "arithematic.h"
#include "iterative_solvers.h"

void test_close(){
  Eigen::Matrix3f A;
  A << 1,2,3,
        4,5,6,
        7,8,9;
  Eigen::Matrix3f B(A), C(A), D(A) ;
  B.array() += 0.1;
  C(1,1) = C(1,1) + 0.1;
  dip::print("B (false) ", dip::isAllClose(A,B));
  dip::print("C (false) ", dip::isAllClose(A,C));
  dip::print("D (true) ", dip::isAllClose(A,D));

}

void test_gaussSeidel(
    const Eigen::MatrixXf &A,
    const Eigen::VectorXf &b,
    const Eigen::VectorXf &x0,
    bool isVerbose=false

)
{

  std::cout << "A: \n" << A << std::endl;
  std::cout << "b: \n" << b << std::endl;

  int n = A.rows();
  Eigen::VectorXf x(n);
  dip::gauss_seidel(A, b, x0, x, 1000, 1e-6, isVerbose);
  std::cout << "x: \n" << x << std::endl;
}

int main() {
//  test_close();
  Eigen::MatrixXf A1(4,
                     4);
  A1 << 10, -1, 2, 0,
      -1, 11, -1, 3,
      2, -1, 10, -1,
      0, 3, -1, 8;

  Eigen::VectorXf b1(4);
  b1 << 6, 25, -11, 15;
  Eigen::VectorXf x0 = Eigen::VectorXf::Ones(4);

  test_gaussSeidel(A1, b1, x0, true);


  Eigen::MatrixXf A2(2,2);
  A2 << 16, 3, 7, -11;
  Eigen::VectorXf b2(2);
  b2 << 11, 13;
  x0.resize(2); x0.fill(1);
  test_gaussSeidel(A2, b2, x0, true);

  Eigen::MatrixXf A3(2,2);
  A3 << 2,3,5,7;
  Eigen::VectorXf b3(2);
  b3 << 11, 13;
  x0(0) = 1.1;
  x0(1) = 2.3;

  test_gaussSeidel(A3, b3, x0, false);
  std::cout << "A3 is not pos definite. Convergence not gauranteed." << std::endl;

}
