//
// Created by HayleySong on 7/31/17.
//
// ref: https://stackoverflow.com/questions/2076475/reading-an-image-file-in-c-c

#include <iostream>
#include <sstream> // std::stringstream
#include <cmath> // floor, ceil
#include <string>
#include "proc.h"
#include "Image.h"

int main(int argc,  char** argv){
  // default params
//  float midpoint = 0.1;
//  float factor = 0.3;
//  std::string fname("../data/Boston_low_contrast.png");
//  dip::Image im(fname);
//
//  std::stringstream convert;
//  for (size_t i=1; i<argc; ++i){
//    convert << argv[i];
//  }
//
//  if (argc >= 3) { //1.main,2. midpoint, 3. factor, 4.fname
//    convert >> midpoint;
//    convert >> factor;
//  }
////  else if (argc >= 4){
////    convert >> fname;
////  }
//  std::cout << "midpoint, factor, fname: "
//            << midpoint << ", " << factor << ", " << fname << std::endl;
////  if (!fname.empty()){
////    im = dip::Image(fname);
////  }
//
//
//
//  dip::Image im_contrasted;
//  float mean = 0.0f;
//  for (int i=0; i<im.nElements(); ++i){
//    mean += im(i);
//  }
//  mean /= im.nElements();
//  std::cout << "mean: " << mean << std::endl;
//  dip::contrast(im, im_contrasted, mean, factor);
//
//
//  im.write("./output/im.png");
//  im_contrasted.write("./output/imcontrasted.png");

  // Test histogram, equalize_histogram
  //----------------------------------------------------------------
  std::cout << "---Test: histogram, equalize histogram" <<std::endl;
//  dip::Image im_gray(10,10,1);
//  im_gray.fill(5,5,1.0f);
//  im_gray.write("./output/imgray.png");
  dip::Image im_gray("../data/breast3.png");
  float width = 0.001;
  int nBins = std::floor(1.0f/width) + 1;

  std::vector<int> hist(nBins,0);
  im_gray.histogram(hist, width);
  for (int i=0; i<hist.size(); ++i){
    std::cout << "i, count: " << i << ", " << hist[i] <<std::endl;
  }

  std::vector<int> hist_equalized(nBins, 0);
  dip::Image im_out;
  dip::equalize_histogram(im_gray, im_out, hist_equalized, width);
  for (int i=0; i<hist_equalized.size(); ++i){
    std::cout << "i, count: " << i << ", " << hist_equalized[i] <<std::endl;
  }

  im_out.write("./output/equalized3.png");
}
