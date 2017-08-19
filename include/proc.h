//
// Created by HayleySong on 8/18/17.
//

#ifndef DIP_PROC_H
#define DIP_PROC_H

#include "Image.h"

namespace dip{
    Image& contrast(const Image &im,
                    Image &out,
                    const float midpoint,
                    const float factor);



}






#endif //DIP_PROC_H
