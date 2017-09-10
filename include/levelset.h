//
// Created by HayleySong on 9/10/17.
//

#ifndef DIP_LEVELSET_H
#define DIP_LEVELSET_H
#include <cmath>
#include "Image.h"

namespace dip{
    void initialize_phi(Image &grid, float radius=1.0f);
    Image getLevelSet(const Image &grid, float zlevel=0.0f, float threshold=std::exp(6));
    Image gradX(const Image &im, int discreteOption=1, bool clamp=true);
    Image gradY(const Image &im, int discreteOption=1, bool clamp=true);
    // discreteOption: 0 backward, 1 centered, 2 forward
    Image gradMag(const Image &gradX, const Image &gradY);

    }

#endif //DIP_LEVELSET_H
