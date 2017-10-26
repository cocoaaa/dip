//
// Created by HayleySong on 9/15/17.
//

#include <iostream>
#include <Eigen/Dense>
#include "meshProc.h"


using namespace std;
using namespace Eigen;
int main()
{
  Matrix3f V = Matrix3f::Random(3,3);
  Vector3f p_bary;
  p_bary << 1.0f, 0.0f, 0.0f;

  std::cout << "should return " << V.row(0) << std::endl;
  std::cout << dip::bary2cart(V, p_bary) << std::endl;
}