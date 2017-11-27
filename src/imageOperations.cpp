//
// Created by HayleySong on 8/22/17.
//

#include <iostream>
#include <cmath> // ceil and floor, std::abs, std::exp

#include "Image.h"
#include "ImageException.h"
#include "imageOperations.h"

//todo: check if pixel values are in range of [0,1] after operations
namespace dip{

  Image operator+(const float f, const Image &im){
    Image out(im.w(), im.h(), im.channels());
    for (size_t i=0; i < im.nElements(); ++i){
      out(i) = im(i) + f;
    }
    return out;
  }

  Image operator-(const float f, const Image &im){

    Image out(im.w(), im.h(), im.channels());
    for (size_t i=0; i < im.nElements(); ++i){
      out(i) = im(i) - f;
    }
    return out;
  }

  Image operator*(const float f, const Image &im){

    Image out(im.w(), im.h(), im.channels());
    for (size_t i=0; i < im.nElements(); ++i){
      out(i) = im(i)*f;
    }
    return out;
  }

  Image operator/(const float f, const Image &im){
    if ( std::abs(f) < std::exp(10))
      throw DivideByZeroException();

    Image out(im.w(), im.h(), im.channels());
    for (size_t i=0; i < im.nElements(); ++i){
      out(i) = im(i)/f;
    }
    return out;
}

  void gradX(const Image &im, Image &out, int firstDerivOption, bool clamp){
    // axis = 0 for x direction, axis = 1 for y direction
    // forward means forward gradient,
    // todo: boundary conditions: clamp
    out.reinit_all(im.w(), im.h(), im.channels());
    for (size_t c = 0; c < im.channels(); ++c){
      for (size_t y = 0; y < im.h(); ++y){
        for (size_t x = 0; x < im.w(); ++x){
          out(x,y,c) = 0.5*(im.smartAccessor(x+1,y,c,clamp) - im.smartAccessor(x-1, y, c, clamp));
        }
      }
    }
  }

  void gradY(const Image &im, Image &out, int firstDerivOption, bool clamp){
    // axis = 0 for x direction, axis = 1 for y direction
    // forward means forward gradient,
    // todo: boundary conditions
    out.reinit_all(im.w(), im.h(), im.channels());
    for (size_t c = 0; c < im.channels(); ++c){
      for (size_t y = 0; y < im.h(); ++y){
        for (size_t x = 0; x < im.w(); ++x){
          out(x,y,c) = 0.5*(im.smartAccessor(x,y+1,c, clamp) - im.smartAccessor(x,y-1,c, clamp));
        }
      }
    }
  }

  void gradMag(const Image &gradX, const Image &gradY, Image &out){
    assert( gradX.w() == gradY.w() &&
            gradX.h() == gradY.h() &&
            gradX.channels() == gradY.channels());
    out.reinit_all(gradX.w(), gradX.h(), gradX.channels());
    for (size_t i = 0; i < gradX.nElements(); ++i){
      out(i) = sqrt(pow(gradX(i),2) + pow(gradY(i),2));
    }
  }

  Image getImpulse(int k){
    Image impulse(k, k, 1);
    impulse.info();
    int mid = floor(k/2);
    impulse(mid, mid, 0) = 1.0f;
    return impulse;
    std::cout << "impulse created" << std::endl;
  }


}

