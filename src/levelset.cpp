//
// Created by HayleySong on 9/10/17.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "Image.h"
#include "levelset.h"

namespace dip{
    void initialize_phi(Image &grid, float radius){
      // Assumes a grayscale grid
      assert (grid.channels() == 1);
      float magnitude;
      for (size_t y = 0; y < grid.h(); ++y){
        for (size_t x = 0; x < grid.w(); ++x){
          magnitude = std::sqrt(x*x + y*y);
          grid(x,y,1) = magnitude - radius;

          if ( magnitude < radius) {
            grid(x,y,1) = -grid(x,y,1);
          }
        }
      }
    }

    Image getLevelSet(const Image &grid, float zlevel, float threshold){
      //Both are gray images
      // threshold is for the difference subtraction numerical stability
      Image out(grid.w(), grid.h(), grid.channels());
      for (size_t i = 0 ; i < grid.nElements(); ++i){
        if ( std::abs(grid(i) - zlevel) < threshold){ out(i) = 0.f; }
        else { out(i) = 1.f; }
      }
    }

    Image gradX(const Image &im, int discreteOption, bool clamp){
      // axis = 0 for x direction, axis = 1 for y direction
      // forward means forward gradient,
      // todo: boundary conditions: clamp
      Image grad(im.w(), im.h(), im.channels());
      for (size_t c = 0; c < im.channels(); ++c){
        for (size_t y = 0; y < im.h(); ++y){
          for (size_t x = 0; x < im.w(); ++x){
            grad(x,y,c) = 0.5*(im.smartAccessor(x-1,y,c,clamp) + im.smartAccessor(x+1, y, c, clamp));
          }
        }
      }
    }

    Image gradY(const Image &im, int discreteOption, bool clamp){
      // axis = 0 for x direction, axis = 1 for y direction
      // forward means forward gradient,
      // todo: boundary conditions
      Image grad(im.w(), im.h(), im.channels());
      for (size_t c = 0; c < im.channels(); ++c){
        for (size_t y = 0; y < im.h(); ++y){
          for (size_t x = 0; x < im.w(); ++x){
            grad(x,y,c) = 0.5*(im.smartAccessor(x,y-1,c, clamp) + im.smartAccessor(x,y+1,c, clamp));
          }
        }
      }
    }

    Image gradMag(const Image &gradX, const Image &gradY){
      assert( gradX.w() == gradY.w() &&
              gradX.h() == gradY.h() &&
              gradX.channels() == gradY.channels());
      Image out(gradX.w(), gradX.h(), gradX.channels());
      for (size_t i = 0; i < gradX.nElements(); ++i){
        out(i) = sqrt(pow(gradX(i),2) + pow(gradY(i),2));
      }
    }

}
