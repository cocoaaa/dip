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

    public:

      Image();
      // Constructor to initialize an image of size width_*height_*channels_
      // If height_ and channels_ are zero, the image will be one dimensional
      // If channels_ is zero, the image will be two dimensional
      Image(int width, int height=0, int channels=0);
      Image(const std::string &filename);
      Image(const std::vector<float> &data, const int w, const int h, const int c);
      Image(Image &other);//copy constructor
      ~Image(){ } // nothing to clean up 

      int w() const {return w_;}
      int h() const {return h_;}
      int channels() const {return channels_;}
      long long nElements() const {return nElements_;}


      // Pixel accessors
      // -----------------------------------------------------------------------
      float& operator()(size_t i);
      float& operator()(size_t x, size_t y, size_t c);
      const float& operator()(size_t i) const;
      const float& operator()(size_t x, size_t y, size_t c) const;
      // for constant objects. still don't know why we need this
      float smartAccessor(int x, int y, int c, bool clamp=true) const;
      std::vector< std::vector<int> > neighbors_diag();
      std::vector< std::vector<int> > neighbors_adj();


        // Operator overloading
      // -----------------------------------------------------------------------
      Image & operator=(const Image &other);
      bool operator==(const Image &other) const;
      bool operator!=(const Image &other) const;

      Image operator+(const Image &other) const;
      Image operator*(const Image &other) const;
      Image operator-(const Image &other) const;
      Image operator/(const Image &other) const;

      Image operator*(const float f) const;
      Image operator/(const float f) const;


      // Fill functions
      // -----------------------------------------------------------------------
      void fill(float val=1.0f);
      void fill(int x0, int nx, int y0, int ny, float val=0.0f); // fills all channels of the image in [x0,x0+nx-1] by [y0,y0+nx-1]
      void fill(int nx, int ny, float val=1.0f); // fills all channles of the image in [0, nx) by [0, ny)
      void fill_channel(int c, float val);

      // Histogram
      void histogram(std::vector<int> &counts, float binWidth) const;

      // Load and write images
      void write(const std::string &filename) const;
      void debugwrite() const;
      Image & load_jpg(const std::string &fname);
      void copyToVec(std::vector<float> &vec) const;

      // Meta info
      void info() const;

      // Reinitilize both meta and data(to new size and zero)
      void reinit_all(int w, int h, int c);


    protected:
      std::vector<float> data;
      int w_;
      int h_;
      int channels_; //1: grayscale 3: rgb 4: rgba
      long long nElements_;
      unsigned int strides_[3];
      void init_meta(int w, int h, int c);

      // Debug
      static int debugnumber;

      };

    // Helper function for I/O
    // -------------------------------------------------------------------------
    float uint8_to_float(const uint8_t &x);
    uint8_t float_to_uint8(const float &x);
}

#endif //DIP_IMAGE_H
