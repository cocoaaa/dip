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
#include "Image.h"

namespace dip{

    Image::Image(int width, int height, int depth): _w(width), _h(height), _d(depth){
      data = new float[width*height*depth];
    }

    Image::Image(Image &other){
      std::cout << "copy constructor" << std::endl;
      int n = other.size();
      _w = other.w();
      _h = other.h();
      _d = other.d();
      data = new float[n];
      for (size_t i=0; i<n; ++i){
        data[i] = other(i);
      }
    }

    float& Image::operator()(size_t i){
      assert(data!=NULL && 0 <=i && i<this->size());
      return data[i];
    }

    const float& Image::operator()(size_t i) const{
      assert(data!=NULL && 0 <=i && i<this->size());
      return data[i];
    }
    
    float& Image::operator()(size_t r, size_t c) {
      assert(0<=r && r<this->h());
      assert(0<=c && c<this->w());
      return data[r*this->w()+c];
    }

    //for const object. still not sure why I need this?
    const float& Image::operator()(size_t r, size_t c) const{
      assert(0<=r && r<this->h());
      assert(0<=c && c<this->w());
      return data[r*this->w()+c];
    }

    Image & Image::operator=(const Image &other){
      assert( this->size()==0 || this->size() == other.size());
      if (this->size()==0){
        data = new float[other.size()];
      }
      _w = other.w();
      _h = other.h();
      _d = other.d();

      size_t n = other.size();
      for (size_t i=0; i<n; ++i ){
        data[i] = other(i);
      }
      return *this;
    }

    bool Image::operator==(const Image &other) const{
      if (this->size() != other.size()){
        return false;
      }
      size_t n = other.size();
      for (size_t i=0; i<n; ++i){
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


}