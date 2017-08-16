//
// Created by HayleySong on 7/31/17.
//

#include <iostream>

#include <Eigen/Dense>
#include "Image.h"

int main(){
  dip::Image im_default;
  std::cout << "Default constructor: grayscale, 10 by 10. num of elements: "
            << im_default.nElements() << std::endl;

  dip::Image im_gray(100,100);
  std::cout << "Gray image of 100 by 100. Dim: "
            << im_gray.w() << ", " << im_gray.h() << ", " << im_gray.channels()
            << std::endl;

  dip::Image im_color(50,50,3);
  std::cout << "3channel image of 50 by 50. Dim: "
            << im_color.w() << ", " << im_color.h() << ", " << im_color.channels() << std::endl;


  // Test operator overloading
  std::cout << "ture: " << (im_default == dip::Image() ) << ", "
            << (im_gray == dip::Image(100,100)) << ", "
            << (im_color == dip::Image(50,50,3));
  //todo: check other operators

  // Test accessor and setter
  im_default(0) = 1.0f;
  std::cout << "first element is set to 1.0f: " << im_default(0) << std::endl;

  // Test image I/O



  //old---
//  std::cout << "using ()" << std::endl;
//  std::cout << im2(0,0) << ", " << im2(1,0) << std::endl;
//
//  dip::Image im3(im2);
//  std::cout << im3(0) << ", " << im3(1,0) << std::endl;
//
//  std::cout << "test operator overloading" << std::endl;
//  std::cout << "im3 == im2: " << (im3==im2) << std::endl;
//  std::cout << "im3 != im2: " << (im3!=im2) << std::endl;
//
//  std::cout << "test = assignment" << std::endl;
//  im1 = im2;
//  std::cout << "im1==im2: " << (im1==im2) << std::endl;
//  std::cout << "im1==im3: " << (im1==im3) << std::endl;


}