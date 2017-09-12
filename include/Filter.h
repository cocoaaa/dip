//
// Created by HayleySong on 9/12/17.
//

#ifndef DIP_FILTER_H
#define DIP_FILTER_H

#include <vector>
#include <cmath>

namespace dip{
    class Filter {

    Filter();
    Filter(int w, int h);
    Filter(std::vector<float> vec, int w, int h);
    ~Filter() { };

    // Convolution
    Image convolve(const Image &im, bool clamp=true) const;

    // Kernel access function
    const float operator()(int x, int y) const;
    float operator()(int x, int y);

    // Show kernel
    void info() const;



    // protected:
      int w_, h_;
      int ksize;
      std::vector<float> kernel;



    };

}



#endif //DIP_FILTER_H
