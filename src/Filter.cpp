//
// Created by HayleySong on 9/12/17.
//
#include "Image.h"
#include "Filter.h"
namespace dip{

    Filter::Filter(): w_(0), h_(0), ksize(w_h){

    }

    Filter::Filter(int w, int h, bool clamp=true): w_(w), h_(h), ksize(w*h){
      kernel = std::vector<float>()
    }


    //given a filter of size w and h with values
    //return the same size image output after convolution
    Image Filter::convolve(const Image &im) const{
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




}
