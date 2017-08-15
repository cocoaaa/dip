//
// Created by HayleySong on 7/31/17.
//

#include <iostream>

#include <Eigen/Dense>
#include "Image.h"

int main(){
  dip::Image im1;
  std::cout << im1.size() << std::endl;

  dip::Image im2(10,10);
  std::cout << "originally all zeros: " << im2(10) << std::endl;
  im2(0) = 1;
  im2(10) = 11;
  std::cout << "set to 1 and 11: " << im2(0) << ", " << im2(10) << std::endl;

  std::cout << "using ()" << std::endl;
  std::cout << im2(0,0) << ", " << im2(1,0) << std::endl;

  dip::Image im3(im2);
  std::cout << im3(0) << ", " << im3(1,0) << std::endl;

  std::cout << "test operator overloading" << std::endl;
  std::cout << "im3 == im2: " << (im3==im2) << std::endl;
  std::cout << "im3 != im2: " << (im3!=im2) << std::endl;

  std::cout << "test = assignment" << std::endl;
  im1 = im2;
  std::cout << "im1==im2: " << (im1==im2) << std::endl;
  std::cout << "im1==im3: " << (im1==im3) << std::endl;


}