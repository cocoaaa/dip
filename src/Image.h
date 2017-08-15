//
// Created by HayleySong on 7/28/17.
//
// todo: template for the pixel type. currently set to float
// lesson: don't put {} at the end of the function declaration.
#ifndef DIP_IMAGE_H
#define DIP_IMAGE_H

#include <string>

namespace dip {

    class Image {
    private:
      float *data;
      int _w;
      int _h;
      int _d; //1: grayscale 2: rgb 3: rgba //todo: enum
    public:
      Image(int width=0, int height=0, int depth=1);
      Image(Image &other);//copy constructor
      ~Image(){ if (data != NULL){delete[] data;} }
      int w() const {return _w;}
      int h() const {return _h;}
      int d() const {return _d;}
      int size() const {return _w*_h*_d;}

      float& operator()(size_t i);
      const float& operator()(size_t i) const;
      float& operator()(size_t r, size_t c);
      const float& operator()(size_t r, size_t c) const; // for constant objects. still don't know why we need this

      Image & operator=(const Image &other);
      bool operator==(const Image &other) const;
      bool operator!=(const Image &other) const;

      Image & load_jpg(const std::string &fname);

      };
}

#endif //DIP_IMAGE_H
