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
#include <sstream>
#include <string>
#include <cassert> //for assert()
#include <vector>
#include "lodepng.h"
#include "Image.h"
#include "ImageException.h"

namespace dip{
    // Constructs a black image with given dimensions
    Image::Image(int width, int height, int channels){

      init_meta(width, height, channels);
      data = std::vector<float>(nElements_,0);

    }

    // Taken from 6.865 Image class. Uses lodepng
    Image::Image(const std::string &filename){
      std::vector<uint8_t> uint8_image;
      unsigned int w;
      unsigned int h;
      unsigned int channels = 4;
      unsigned int outputchannels = 3; // throw away transparency
      unsigned  error = lodepng::decode(uint8_image, w, h, filename);
      // in column major order with packed color values

      if (error==48){
        std::cout << "file not found" << std::endl;
//        throw FileNotFoundException();
      }

      data = std::vector<float>(w*h*outputchannels, 0);
      for (unsigned int x = 0; x < w; ++x){
        for (unsigned int y = 0; y< h; ++y){
          for (unsigned int c = 0; c < outputchannels; ++c){
            data[x + y*w + c*w*h] = uint8_to_float( uint8_image[ c + x*channels + y*channels*w]);
          }
        }
      }

      init_meta(w, h, outputchannels);
    }

    Image::Image(Image &other){
      std::cout << "copy constructor" << std::endl;
//      if (nElements_ != other.nElements()){
//        throw MismatchedDimensionsException();
//      }
      std::cout << "other info -----" << std::endl;
      other.info();

      init_meta(other.w(), other.h(), other.channels());
      std::cout << "nElement to be construced vs copy obj: "
                << nElements() << ", " << other.nElements() << std::endl;
      assert(nElements_ == other.nElements());

      data.resize(nElements_);
      for (size_t i=0; i<nElements_; ++i){
        data[i] = other(i);
      }
    }


    // (private) static data member is recommended to be defined in cpp
    // to prevent double definition if in .h file
    int Image::debugnumber = 0; // note no "static" keyword used here.

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
//      assert( nElements_ == 0 || nElements_ == other.nElements());
      std::cout << "assignment operator" << std::endl;
      init_meta(other.w(), other.h(), other.channels());
      assert( nElements_ == other.nElements() );
      std::cout << "here" << std::endl;
      data.resize(nElements_);
      std::cout << "here2" << std::endl;

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

    void Image::init_meta(int w, int h, int channels){
      w_ = w; h_ = h; channels_ = channels;

      strides_[0] = 0;
      strides_[1] = 0;
      strides_[2] = 0;
      nElements_ = 0; //todo: check if this is a right way to indicate a correctly initialized image object


      if ( w < 0) 
        throw NegativeDimensionException();
      if ( h < 0)
        throw NegativeDimensionException();
      if (channels < 0)
        throw NegativeDimensionException();

      w_ = w; h_ = h; channels_ = channels;
      
      strides_[0] = 1;
      nElements_ = w;
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

    void Image::reinit_all(int w, int h, int c){
      w_ = w; h_ = h; channels_ = c;
      nElements_ = w*h*c;
      data = std::vector<float>(nElements_, 0);
    }

    void Image::info() const {
      std::cout << "w, h, channels: " << w() << ", " << h() << ", " << channels() << std::endl;
      std::cout << "nElements: " << nElements() << std::endl;
      std::cout << std::endl;
    }

    void Image::write(const std::string &filename) const {
      if (channels() != 1 && channels() != 3 && channels() != 4)
//        throw ChannelException();
        ;
      int png_channels = 4;
      std::vector<unsigned char> uint8_image(h()*w()*png_channels, 255);
      int c;
      for (int x= 0; x < w(); x++) {
        for (int y = 0; y < h(); y++) {
          for (c = 0; c < channels(); c++) {
            uint8_image[c + x*png_channels + y*png_channels*w()] = float_to_uint8(data[x+y*w()+c*w()*h()]);
          }
          for ( ; c < 3; c++) { // Only executes when there is one channel
            //todo: understand this
            uint8_image[c + x*png_channels + y*png_channels*w()] = float_to_uint8(data[x+y*w()]);
          }
        }
      }
      lodepng::encode(filename.c_str(), uint8_image, w(), h());
    }

    void Image::debugwrite() const{
      std::ostringstream ss;
      ss << "./output/" << debugnumber << ".png";
      std::string fname = ss.str();
      write(fname);
      debugnumber ++;
    }

    void Image::fill(float val){
      for (int i=0; i<nElements_; ++i){
        data[i] = val;
      }
    }

    void Image::fill(int nx, int ny, float val){
      //todo: check bounds
    }

    void Image::fill_channel(const size_t c, float val){
      if (c >= channels() ){
        throw OutofBoundsException();
      }

      for (size_t x = 0; x < w(); ++x){
        for (size_t y = 0; y < h(); ++y){
          data[x + y*w_ + c*w_*h_] = val;
        }
      }

    }

    // Helper functions for I/O
    float uint8_to_float(const uint8_t &x) {
      return ((float)x) / 255.0f;
    }

    uint8_t float_to_uint8(const float &x) {
      float out = x;
      if (x < 0)
        out = 0;
      if (x > 1)
        out = 1;
      return (uint8_t)(out * 255.0f);
    }

}