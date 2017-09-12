//
// Created by HayleySong on 9/10/17.
//

#include "Grid.h"
#include <cmath>

namespace dip {
    Grid::Grid(size_t w, size_t h)
        : Image(w,h,1){
      //Initialize im_gradX and im_gradY
      data_gradX = std::vector<float>(nElements(),0.0f);
      data_gradY = std::vector<float>(nElements(),0.0f);
      data_gradMag = std::vector<float>(nElements(),0.0f);
      //todo: velocity
    }

    void Grid::init_phi(float radius) {
      //todo: copy from levelset.cpp
      float magnitude;
      for (size_t y = 0; y < h_; ++y){
        for (size_t x = 0; x < w_; ++x){
          magnitude = sqrt(x*x + y*y);
          if ( magnitude > radius){
            data[x + y*w_] = magnitude - radius;
          }
          else {
            data[x + y*w_] = radius - magnitude;
          }
        }
      }
    }

    void Grid::update_phi(const Image &v_field, const float dt) {
      // uses the current gradient magnitude, dt, velocity field to
      // update the phi on the grid

    }

    void Grid::update_gradX(bool clamp){
      // Recalculates the gradient of the current grid in x-direction

    }
    void Grid::update_gradMag(){
      for (size_t i = 0; i < nElements_; ++i){
        data_gradMag[i] = sqrt( pow(data_gradX[i],2) + pow(data_gradY[i],2) );
      }
    }


}