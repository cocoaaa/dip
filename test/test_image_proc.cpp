//
// Created by HayleySong on 7/31/17.
//
// ref: https://stackoverflow.com/questions/2076475/reading-an-image-file-in-c-c

#include <iostream>
#include <sstream> // std::stringstream
#include <string>
#include "proc.h"
#include "Image.h"

int main(int argc,  char** argv){
  // default params
  float midpoint = 0.1;
  float factor = 0.3;
  std::string fname("../data/Boston_low_contrast.png");
  dip::Image im(fname);

  std::stringstream convert;
  for (size_t i=1; i<argc; ++i){
    convert << argv[i];
  }

  if (argc >= 3) { //1.main,2. midpoint, 3. factor, 4.fname
    convert >> midpoint;
    convert >> factor;
  }
//  else if (argc >= 4){
//    convert >> fname;
//  }
  std::cout << "midpoint, factor, fname: "
            << midpoint << ", " << factor << ", " << fname << std::endl;
//  if (!fname.empty()){
//    im = dip::Image(fname);
//  }

  std::cout << "debug im ----" << std::endl;
  im.info();

  dip::Image im_contrasted;
  float mean = 0.0f;
  for (int i=0; i<im.nElements(); ++i){
    mean += im(i);
  }
  mean /= im.nElements();
  std::cout << "mean: " << mean << std::endl;
  dip::contrast(im, im_contrasted, mean, factor);


  im.write("./output/im.png");
  im_contrasted.write("./output/imcontrasted.png");
}
