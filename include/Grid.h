//
// Created by HayleySong on 9/10/17.
//

#ifndef DIP_GRID_H
#define DIP_GRID_H

#include <iostream>
namespace dip {
    class Grid : public Image {

      Grid(size_t w=0, size_t h=0): Image(w,h,1){
        std::cout << "Grid created. w,h,c: " << w << ", " << h << std::endl;
      }

      void init_phi();
      void update_phi();
      void update_gradX(bool clamp=true);
      void update_gradY(bool clamp=true);
      void update_gradMag();
      void update_velocity();

    private:
      std::vector<float> data_gradX;
      std::vector<float> data_gradY;
      std::vector<float> data_gradMag;
      float velocity;

    };
}

#endif //DIP_GRID_H
