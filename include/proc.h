//
// Created by HayleySong on 8/18/17.
//

#ifndef DIP_PROC_H
#define DIP_PROC_H

#include "Image.h"

namespace dip{
    void contrast(const Image &im, Image &out, const float midpoint, const float factor);

    void equalize_histogram(
        const Image &im,
        Image &im_out,
        std::vector<int> &hist_out,
        float binWidth = 0.01);


}






#endif //DIP_PROC_H
