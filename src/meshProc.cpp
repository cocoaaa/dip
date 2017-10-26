#include "meshProc.h"
#include <iostream>

namespace dip {


    Eigen::Vector3f cart2bary(
        const Eigen::Matrix3f &tri,
        const Eigen::Vector3f &point) {

      return tri.transpose() * point;

    }

    Eigen::Vector3f bary2cart(
        const Eigen::Matrix3f &tri,
        const Eigen::Vector3f &point_bary) {

      Eigen::MatrixXd H(4, 3);
      H.block<3, 3>(0, 0) = tri.transpose();
      H.row(3) << 1, 1, 1;

      Eigen::Vector4f p;
      p << point_bary, 1;

      Eigen::FullPivLU<Eigen::MatrixXd> lu(H);

      std::cout << "H:" << std::endl;
      std::cout << H << std::endl;
      std::cout << "lu decomposition of H: \n";
      std::cout << lu.matrixLU() << std::endl;
      std::cout << "rank of H: " << lu.rank() << std::endl;

      std::cout << "----------" << std::endl;
      std::cout << "\n b: \n";
      std::cout << b << std::endl;

      return lu.solve(b);

    }

}