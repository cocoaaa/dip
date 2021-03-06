//
// Created by HayleySong on 7/31/17.
//

#include <iostream>

#include <Eigen/Dense>
#include "Image.h"
#include "imageOperations.h"

void test_neighbors_diag(){
  dip::Image im(3,2);
  std::cout << "im construced: " << im.nElements() << std::endl;
  std::vector<std::set<int> > diags = im.neighbors_diag(true);
  std::cout << "size of diags vec should be " << im.nElements() << ":" << diags.size() << std::endl;
  for (int i=0; i<diags.size(); ++i ){
    std::cout << "\npixel " << i << ": ";
    for (auto elem: diags[i]){
      std::cout << elem << ", ";
    }
  }
  std::cout << std::endl;
}

void test_neighbors_adjacent(){
  dip::Image im(5,5);
  std::cout << "im construced: " << im.nElements() << std::endl;
  std::vector<std::set<int> > adjs = im.neighbors_adjacent(true);
  std::cout << "size of vec should be " << im.nElements() << ":" << adjs.size() << std::endl;
  for (int i=0; i<adjs.size(); ++i ){
    std::cout << "\npixel " << i << ": ";
    for (auto elem: adjs[i]){
      std::cout << elem << ", ";
    }
  }
  std::cout << std::endl;
}

void test_basic(){

  dip::Image im_default;
  std::cout << "Default constructor: everything set by default "
            << im_default.nElements() << std::endl;

  dip::Image im_1d(100);
  im_1d.write("./output/1d_100.png");

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

  // Test copy constructor
  dip::Image im_red2(im_red);
  im_red2.write("./output/red2.png");

  // Test return of copy constructed object
  std::cout << "----------" << std::endl;
  dip::Image im_green2(im_green); // no error. but error if dip::Image(im_green) -- why?
  std::cout << "copy constructed: green" << std::endl;

  std::cout << "----------test: anonymous object" << std::endl;
  dip::Image im_test;
  im_test.write("./output/myimg.png");

  im_test.fill_channel(0,1.0f); im_test.write("./output/myimg_white.png");
  (im_test*0.5f).write("./output/myimg_gray.png");
  (0.5f*im_test).write("./output/myimg_gray2.png");

  //todo: check other operators
}

void test_imToVec(){
  std::vector<float> d;
  for (int i = 0; i<10; ++i){
    d.push_back(i);
  }

  dip::Image im(d, 5,2,1);
  for (int y=0; y<im.h(); ++y){
    for (int x=0; x<im.w(); ++x ){
      std::cout << im(x,y,0) << ",";
    }
    std::cout << std::endl;
  }

  std::vector<float> d2;
  im.copyToVec(d2);

  for (int i=0; i<d2.size(); ++i){
    std::cout << d2[i] << ", ";
  }
  std::cout << std::endl;


}

int main(){

//  test_neighbors_diag();
//  test_neighbors_adjacent();
  test_imToVec();

}