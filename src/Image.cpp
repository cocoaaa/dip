//
// Created by HayleySong on 7/28/17.
//
// todo: use template for the pixel type. Currently it's set to float
// todo: operator overloading
// read: how to correctly implement double square bracket to access 2D array
//       https://stackoverflow.com/questions/2533235/operator-c
// Default parameter only delong in the declaration in the header file, not in the implementation in the cpp file.
// Ref:  http://www.scratchapixel.com/lessons/digital-imaging/simple-image-manipulations
#include <iostream>
#include <string>
#include <cassert> //for assert()
#include <vector>
#include "Image.h"

namespace dip{
    // Constructs a black image with given dimensions
    Image::Image(int width, int height, int channels): 
            w_(width), 
            h_(height), 
            channels_(channels){

      init_meta(width, height, channels);
      data = std::vector<float>(nElements_,0);
    }

    Image::Image(Image &other){
      std::cout << "copy constructor" << std::endl;
      if (nElements_ != other.nElements()){
        throw MismatchedDimensionsException();
      }
      nElements_ = other.nElements();
      w_ = other.w();
      h_ = other.h();
      channels_ = other.channels();
      strides_[0] = 1;
      strides_[1] = w_;
      strides_[2] = w_*h_;

      for (size_t i=0; i<nElements_; ++i){
        data[i] = other(i);
      }
    }

    float& Image::operator()(size_t i){
      if (i<0 || i>=nElements_)
        throw OutofBoundsException();
      return data[i];
    }
    
    float& Image::operator()(size_t x, size_t y, size_t c) {
      return data.at(x + y*strides_[1] + c*strides_[2]);
    }

    //for const object. still not sure why I need this?
    const float& Image::operator()(size_t i) const{
      if (i<0 || i >= nElements_)
        throw OutofBoundsException();
      return data[i];
    }
    
    const float& Image::operator()(size_t x, size_t y, size_t c) const {
      return data.at(x + y*strides_[1] + c*strides_[2]);
    }

    Image & Image::operator=(const Image &other){
      assert( nElements_ ==0 || nElements_ == other.nElements());
      w_ = other.w();
      h_ = other.h();
      channels_ = other.channels();
      nElements_ = other.nElements();

      for (size_t i=0; i<nElements_; ++i ){
        data[i] = other(i);
      }
      return *this;
    }

    bool Image::operator==(const Image &other) const{
      if ( nElements_ != other.nElements()){
        return false;
      }
      for (size_t i=0; i<nElements_; ++i){
        if (data[i] != other(i)){
          return false;
        }
      }
      return true;
    }

    bool Image::operator!=(const Image &other) const{
      return !(*this == other);
    }

    // File IO
    Image & Image::load_jpg(const std::string &fname){

    }

    void Image::init_meta(int w, int h, int channels){
      strides_[0] = 0;
      strides_[1] = 0;
      strides_[2] = 0;
      nElements_ = 1;

      if ( w < 0) 
        throw NegativeDimensionException();
      if ( h < 0)
        throw NegativeDimensionException();
      if (channels < 0)
        throw NegativeDimensionException();

      w_ = w; h_ = h; channels_ = channels;
      
      strides_[0] = 1;
      nElements_ *= w;
      if (h>0){
        strides_[1] = w;
        nElements_ *= h;
      } else{
        return;
      }

      if (channels > 0){
        strides_[2] = w*h;
        nElements_ *= channels;
      } else{
        return;
      }
      
    }

    void Image::fill(float val){
      for (int i=0; i<nElements_; ++i){
        data[i] = val;
      }
    }

    void Image::fill(int nx, int ny, float val){
      //todo: check bounds
    }

    void Image::fill_channel(int c, float val) {
      assert(0 < c && c < channels());
      int n = this->w() * this->h();
      for (int x = strides_[1]*c; x< n; ++x){
        data[x] = val;
      }
    }

}