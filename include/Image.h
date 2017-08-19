//
// Created by HayleySong on 7/28/17.
//
// todo: template for the pixel type. currently set to float
// lesson: don't put {} at the end of the function declaration.
#ifndef DIP_IMAGE_H
#define DIP_IMAGE_H

#include <string>
#include <vector>
#include "ImageException.h"

namespace dip {

    class Image {
    private:
      std::vector<float> data;
      int w_;
      int h_;
      int channels_; //1: grayscale 3: rgb 4: rgba //todo: enum
      long long nElements_; 
      unsigned int strides_[3];
      void init_meta(int w, int h, int c);
    public:
      Image(int width=10, int height=10, int channels=1);
      Image(Image &other);//copy constructor
      ~Image(){ } // nothing to clean up 

      int w() const {return w_;}
      int h() const {return h_;}
      int channels() const {return channels_;}
      long long nElements() const {return nElements_;}

      float& operator()(size_t i);
      float& operator()(size_t x, size_t y, size_t c);
      const float& operator()(size_t i) const;
      const float& operator()(size_t x, size_t y, size_t c) const; // for constant objects. still don't know why we need this

      Image & operator=(const Image &other);
      bool operator==(const Image &other) const;
      bool operator!=(const Image &other) const;

      // Fill functions
      void fill(float val=0.0f);
      void fill(int x0, int nx, int y0, int ny, float val=0.0f); // fills all channels of the image in [x0,x0+nx-1] by [y0,y0+nx-1]

      void fill(int nx, int ny, float val=0.0f); // fills all channles of the image in [0, nx) by [0, ny)
      void fill_channel(int cidx, float val=0.0f);

      // load and write images
      Image & load_jpg(const std::string &fname);

      };
}

#endif //DIP_IMAGE_H