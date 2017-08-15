#include <iostream>
#include <string>
#include <array>
#include <dlib/pixel.h>
#include <dlib/image_io.h>
#include "histogram.h"

namespace dlib{
    template< typename P, int maxVal>
    std::array<P, maxVal> & get_histogram(const dlib::array2d<P> &img){

      // Assumes a depth 1 image.
      P size = img.nr()*img.nc();
      std::array<P, maxVal> hist;
      for (P &val : img){
        hist[val]++;
      }
      return hist;
    }
}