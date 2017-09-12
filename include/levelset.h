//
// Created by HayleySong on 9/10/17.
//

#ifndef DIP_LEVELSET_H
#define DIP_LEVELSET_H
#include <cmath>
#include "Image.h"

namespace dip{
    void getLevelSet(const Image &grid,
                     Image &out,
                     float zlevel=0.0f,
                     float threshold=std::exp(6));
    }

#endif //DIP_LEVELSET_H
