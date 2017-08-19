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
  im_gray.fill_channel(0, 0.5f);
  std::cout << "Gray image of 100 by 100. Dim: "
            << im_gray.w() << ", " << im_gray.h() << ", " << im_gray.channels()
            << std::endl;

  dip::Image im_red(50,50,3), im_blue(50,50,3), im_green(50,50,3);
  im_red.fill_channel(0, 1.0f);
  im_green.fill_channel(1, 1.0f);
  im_blue.fill_channel(2, 1.0f);

  std::cout << "3channel image of 50 by 50. Dim: "
            << im_red.w() << ", " << im_red.h() << ", " << im_red.channels() << std::endl;


  // Test operator overloading
  std::cout << "true: " << (im_default == dip::Image() ) << ", "
            << (im_gray == dip::Image(100,100)) << ", "
            << (im_red == dip::Image(50,50,3));
  //todo: check other operators

  // Test accessor and setter
  im_default(0) = 1.0f;
  std::cout << "first element is set to 1.0f: " << im_default(0) << std::endl;

  // Test image I/O
  im_default.write("default");
  im_default.debugwrite();
  im_gray.write("./output/gray.png");
  im_red.write("./output/red.png");
  im_blue.write("./output/blue.png");
  im_green.write("./output/green.png");

  dip::Image im_loaded("../data/lenna.png");
  im_loaded.write("./output/l.png");



}