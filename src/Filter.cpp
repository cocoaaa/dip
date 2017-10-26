//
// Created by HayleySong on 9/12/17.
//
#include "Image.h"
#include "Filter.h"
#include <Eigen/Dense>
#include <iostream>

namespace dip{

    Filter::Filter(): w_(0), h_(0), ksize(0){
//      kernel = std::vector<float>(0);
    }

    Filter::Filter(int w, int h): w_(w), h_(h), ksize(w*h){
      kernel = std::vector<float>(w*h, 0);
    }

    Filter::Filter(const std::vector<float> &vec, int w, int h): w_(w), h_(h), ksize(w*h){
      assert(w*h == vec.size());
      kernel = vec; //deep copy; resizes implicitly if needed
    }

    Filter::Filter(const Eigen::MatrixXf &mtx, int w, int h): w_(w), h_(h), ksize(w*h){
      assert(w*h == mtx.size());
//      kernel = mtx.array(); // todo: something like this.
      // make sure the mtx data is put into the vector in the rowwise order
    }

    void Filter::setKernel(const std::vector<float> &vec, int w, int h){
      assert(ksize == w*h); //todo: Make a dimension mismatch exception
      kernel = vec;
    }

    const float Filter::operator()(int x, int y) const{
      return kernel[x + y*w_];
    }

    float Filter::operator()(int x, int y){
      return kernel[x + y*w_];
    }

    //given a filter of size w and h with values
    //return the same size image output after convolution
    Image Filter::convolve(const Image &im, bool clamp) const{
      Image out(im.w(), im.h(), im.channels());
      int fCenterX= floor(w_/2);
      int fCenterY = floor(h_/2);

      for (size_t c = 0; c < im.channels(); ++c){
        for (size_t y = 0; y < im.h(); ++y){
          for (size_t x = 0; x < im.w(); ++x){

            // loop through the filter
            for (size_t j=0; j < h_; ++j){
              int dy = j - fCenterY;
              for (size_t i=0; i< w_; ++i){
                int dx = i - fCenterX;
                out(x, y, c) += im.smartAccessor(x+dx, y+dy, c, clamp) * kernel[i + j*w_];
              }
            }

          }
        }
      }
      return out;
    }

    void Filter::info() const{
      std::cout << "==== Kernel ====" << std::endl;
      for (size_t j=0; j<h_; ++j){
        for (size_t i=0; i<w_; ++i){
          std::cout << kernel[i + j*w_] << " ";
        }
        std::cout << std::endl;
      }
      std::cout << "================" << std::endl;
    }

    void Filter::reInit(int w, int h, int ksize){
      w_ = w; h_ = h;
      kernel = std::vector<float>(w*h,ksize);
    }

    //Gaussian Filter
    Gaussian::Gaussian(int w, int h, float sigma, float truncate)
        : Filter(w,h), sigma_(sigma){

      int centerX = floor(w/2);
      int centerY = floor(h/2);

      float normalizer = 0.0f;
      for (int y=0; y<h; ++y ) {
        for (int x = 0; x < w; ++x) {
          float sqDist = pow(x - centerX, 2) + pow(y - centerY, 2);
          float val = std::exp(-sqDist / (2 * sigma * sigma));

          if (sqrt(sqDist) > truncate * sigma) {
            val = 0.f;
          }
          kernel[x + y*w_] = val;
          normalizer += val;
        }
      }

      // Normalize
      for (size_t i=0; i<kernel.size(); ++i){
        kernel[i] /= normalizer;
      }
    }

    // Constructor for a symmetric Gaussian
    Gaussian::Gaussian(float sigma, float truncate): sigma_(sigma){

      int center = ceil(sigma*truncate);
      int w = 2*center + 1;
      int filterSize = w*w;

      reInit(w, w, filterSize);

      float normalizer = 0.0f;
      for (int y = 0; y < w; ++y ) {
        for (int x = 0; x < w; ++x) {
          float sqDist = pow(x - center, 2) + pow(y - center, 2);
          float val = std::exp(-sqDist / (2 * sigma * sigma));

          if (sqrt(sqDist) > truncate * sigma) {
            val = 0.f;
          }
          kernel[x + y*w] = val;
          normalizer += val;
        }
      }

      // Normalize
//      for (size_t i=0; i<kernel.size(); ++i){
//        kernel[i] /= normalizer;
//      }
    }

}
