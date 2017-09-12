//
// Created by HayleySong on 8/22/17.
//

#ifndef DIP_IMAGEOPERATIONS_H
#define DIP_IMAGEOPERATIONS_H

#include <iostream>
#include <vector>
#include <cmath> // ceil and floor, std::abs, std::exp
#include "Image.h"
#include <Eigen/Dense>
namespace dip{
    // Overloading: scaler * Image and scaler / Image
    Image operator*(const float f, const Image &im);
    Image operator/(const float f, const Image &im);

    // Gradients
    // firstDerivOption: 0 backward, 1 centered, 2 forward

    void gradX(const Image &im, Image &out, int fistDerivOption=1, bool clamp=true);
    void gradY(const Image &im, Image &out, int firstDerivOption=1, bool clamp=true);
    void gradMag(const Image &gradX, const Image &gradY, Image &out);

    // Generate impluse image of k x k x 1 size
    Image getImpulse(int k);
    }



#endif //DIP_IMAGEOPERATIONS_H
