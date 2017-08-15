//
// Created by HayleySong on 7/15/17.
//
#include <dlib/pixel.h>
#include <dlib/image_io.h>

#ifndef DIP_HISTOGRAM_H
#define DIP_HISTOGRAM_H


namespace dlib{

    template< typename P, int maxVal>
    std::array<P, maxVal> & get_histogram(const dlib::array2d<P> &img);



}



#endif //DIP_HISTOGRAM_H
