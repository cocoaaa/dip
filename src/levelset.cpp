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

    void getLevelSet(const Image &grid, Image &out, float zlevel, float threshold){
      //Both are gray images
      // threshold is for the difference subtraction numerical stability
      out.reinit_all(grid.w(), grid.h(), grid.channels());
      for (size_t i = 0 ; i < grid.nElements(); ++i){
        if ( std::abs(grid(i) - zlevel) < threshold){ out(i) = 0.f; }
        else { out(i) = 1.f; }
      }
    }

}
