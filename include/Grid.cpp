//
// Created by HayleySong on 9/10/17.
//

#include "Grid.h"
namespace dip {
    Grid::Grid(size_t w, size_t h){
      //Initialize im_gradX and im_gradY
      data_gradX.resize(w*h,0.0f);
      data_gradY.resize(w*h,0.0f);
      data_gradMag.resize(w*h, 0.0f);
      //todo: velocity
    }

    void Grid::init_phi() {
      //todo: copy from levelset.cpp
    }

    void Grid::update_phi(float velocity) {

    }

    void update_gradMag(){
      for (size_t i = 0; i < num_elements; ++i){
        data_gradMag(i) = sqrt( pow(data_gradX(i),2) + pow(data_gradY(i),2) );
      }
    }


}