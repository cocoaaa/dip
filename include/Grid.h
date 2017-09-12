//
// Created by HayleySong on 9/10/17.
//

#ifndef DIP_GRID_H
#define DIP_GRID_H

#include "Image.h"
#include <iostream>
#include <vector>

namespace dip {
    class Grid : public Image {

      Grid(size_t w, size_t h=0);

      void init_phi(float radius=1);
      void update_phi(const Image &v_field, const float dt);
      void update_gradX(bool clamp=true);
      void update_gradY(bool clamp=true);
      void update_gradMag();
      void update_velocity();

    private:
      std::vector<float> data_gradX;
      std::vector<float> data_gradY;
      std::vector<float> data_gradMag;
      std::vector<float> data_vField;

    };
}

#endif //DIP_GRID_H
