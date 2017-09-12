//
// Created by HayleySong on 9/12/17.
//
#include "Image.h"
#include "Filter.h"
namespace dip{

    Filter::Filter(): w_(0), h_(0), ksize(w_h){ }

    Filter::Filter(int w, int h): w_(w), h_(h), ksize(w*h){
      kernel = std::vector<float>(w*h, 0);
    }

    Filter::Filter(std::vector<float> vec, int w, int h): w_(w), h_(h){
      assert(w*h == vec.size());
      kernel = vec; //deep copy; resizes implicitly if needed
    }

    // todo: check this 
    Filter::Filter(Eigen::Matrix<float> mtx, int w, int h): w_(w), h_(h){
      assert(w*h == mtx.size());
      kernel = mtx.vector(); // todo: something like this. 
      // make sure the mtx data is put into the vector in the rowwise order
    }

    void Filter::setKernel(std::vector<float> vec, int w, int h){
      assert(ksize == w*h); //todo: Make a dimension mismatch exception
      kernel = vec;
    }

    const float Filter::operator()(int x, int y) const{
      return kernel(x + y*w_);
    }

    float Filter::operator()(int x, int y){
      return kernel(x + y*w_);
    }

    //given a filter of size w and h with values
    //return the same size image output after convolution
    Image Filter::convolve(const Image &im, bool clamp=true) const{
      Image out(im.w(), im.h(), im.c());
      int fCenterX= floor(im.w()/2);
      int fCenterY = floor(im.h()/2);

      for (size_t c = 0; c < im.channels(); ++c){
        for (size_t y = 0; y < im.h(); ++y){
          for (size_t x = 0; x < im.w(); ++x){
            // loop through the filter
            for (size_t j=0; j < h_; ++j){
              int dy = j - fCenterY;
              for (size_t i=0; i< w_; ++i){
                int dx = i - fCenterX;
                out(x, y, c) += im.smartAccessor(x+dx, y+dy, c) * kernel(i + j*w_);
              }
            }
          }
        }
      }

      return out;
    }

    void info() const{
      std::cout << "==== Kernel ====" << std::endl;
      for (size_t j=0; j<h_; ++j){
        for (size_t i=0; i<w_; ++i){
          std::cout << kernel(i + j*w_) << " ";
        }
        std::cout << std::endl;
      }
      std::cout << "================" << std::endl;
    }




}
