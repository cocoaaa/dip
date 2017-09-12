//
// Created by HayleySong on 9/12/17.
//

#ifndef DIP_FILTER_H
#define DIP_FILTER_H

#include <vector>
#include <cmath>

namespace dip{
    class Filter {

    Filter(){};
    Filter(int w, int h, bool clamp=ture);

    Image convolve(const Image &im) const;

    private:
      int w_, h_;
      int ksize;
      std::vector<float> kernel;
    };



}



#endif //DIP_FILTER_H
