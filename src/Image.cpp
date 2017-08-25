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
#include <cmath> // ceil and floor, std::abs, std::exp
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

    // Operator overloading
    // -------------------------------------------------------------------------
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
      data.resize(nElements_);

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

    Image Image::operator+(const Image &other) const{
      if (w_ != other.w() ||
          h_ != other.h() ||
          channels_ != other.channels()){
        throw MismatchedDimensionsException();
      }

      Image out(w_, h_, channels_);
      for (size_t i=0; i < channels_; ++i){
        out(i) = data[i] + other(i);
      }

      return out;
    }

    Image Image::operator*(const float f) const{
      //todo: use typedef to generalize float
      Image out(w_, h_, channels_);
      for (int i=0; i< nElements_; ++i){
        out(i) = f*data[i];
      }
      return out;
    }

    Image Image::operator-(const Image &other) const{
      //debug
      Image out;
      out = other * -1.0f;
      std::cout << "--- DEBUG OPERATOR -" << std::endl;
      out.info();
      return out;
      // remove until here
//      return this->operator+(other * -1.0f);
    }

    Image Image::operator/(const float f) const{
      if (std::abs(f) < std::exp(10))
        throw DivideByZeroException();
      Image out;
      out = this->operator*(1/f);
      return out;
    }

    // Smart Accessor
    float Image::smartAccessor(int x, int y, int c, bool clamp) const{

      if (x <0 || x > w_-1 || y < 0 || y > h_-1 || c < 0 || c > channels_){
        int x_offset(0), y_offset(0);

        // access out of bound pixels
        if (clamp){
          // return the "closest" pixel value
          if (std::abs(-x) < std::abs(w_-1 - x)){ x_offset = -x; }
          else{ x_offset = w_-1 - x; }

          if (std::abs(-y) < std::abs(h_-1 - y)){ y_offset = -y; }
          else{ y_offset = h_-1 - y; }

          x += x_offset;
          y += y_offset;
        }
        else{
          // otherwise zero-padding
          return 0.0f;
        }
      }
      return data[ x + y*w_ + c*w_*h_];
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
      std::cout << "--IMAGE INFO--" << std::endl;
      std::cout << "w, h, channels: " << w() << ", " << h() << ", " << channels() << std::endl;
      std::cout << "nElements: " << nElements_ << std::endl;
      std::cout << "--------------" << std::endl;
    }

    // Write functions
    //--------------------------------------------------------------------------
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


    // Fill functions
    //--------------------------------------------------------------------------
    void Image::fill(const float val){
      for (int i=0; i<nElements_; ++i){
        data[i] = val;
      }
    }

    void Image::fill(const size_t nx, const size_t ny, const float val){
      //todo: check bounds
      if ( val < 0 || val > 1)
        throw PixelValueException();
      if ( nx > w_ || ny > h_)
        throw OutofBoundsException();
      for (int c=0; c < channels_; ++c) {
        for (int y=0; y < ny; ++y) {
          for (int x=0; x < nx; ++x) {
            data[x + y*w_ + c*w_*h_] = val;
          }
        }
      }

    }

    void Image::fill_channel(const size_t c, const float val){
      if (c >= channels() ){
        throw OutofBoundsException();
      }

      for (size_t x = 0; x < w(); ++x){
        for (size_t y = 0; y < h(); ++y){
          data[x + y*w_ + c*w_*h_] = val;
        }
      }

    }

    // Histogram
    //--------------------------------------------------------------------------
    void Image::histogram(std::vector<int> &counts, float binWidth) const {
      // Assumes all pixel values are in [0,1]
      if (binWidth < 0 || binWidth > 1){
        throw BinWidthException();
      }
      std::cout << "binWidth: " << binWidth << std::endl;
      int nBins =  std::floor(1.0f/binWidth) + 1; // last bin for value of 1.0f

      // resize counts and set values to zero
      if (counts.size() != nBins){
        std::vector<int>(nBins).swap(counts);
      } else{
        std::fill(counts.begin(), counts.end(), 0);
      }

      // if val is in [0+binWidth*i, 0+binWidth*(i+1)), val is assigned to ith bin
      // that is, i = integer part of (val/binWidth)
      for (int i=0; i< nElements(); ++i){
        counts[ floor(data[i]/binWidth) ] ++;
      }
    }

    // Helper functions for I/O
    //--------------------------------------------------------------------------
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