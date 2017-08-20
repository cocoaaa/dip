//
// Created by HayleySong on 8/18/17.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "Image.h"
#include "proc.h"

namespace dip{

    void contrast(const Image &im, Image &out, const float midpoint, const float factor){
      if (out.nElements() != im.nElements()){
        out.reinit_all(im.w(), im.h(), im.channels());
      }

      for (int i=0; i < im.nElements(); ++i){
        out(i) = factor*(im(i) - midpoint) + midpoint;
        if (out(i) < 0)
          out(i) = 0;
        if (out(i) > 1)
          out(i) = 1;
      }
    }

    void equalize_histogram(const Image &im,
                            Image &im_out,
                            std::vector<int> &hist_out,
                            float binWidth){
      std::vector<int> in; //todo rename it to hist1
      im.histogram( in, binWidth );
      std::vector<int>(in.size()).swap(hist_out);

      // set im_out ready for the output
      if (im_out.nElements() != im.nElements()){
        im_out.reinit_all(im.w(), im.h(), im.channels());
      }
      std::vector<int> accum(in.size(),0);

      accum[0] = in[0];
      for (int i = 1; i< in.size(); ++i){
        accum[i] = accum[i-1] + in[i];
      }
//      std::cout << "---accumulator---" << std::endl;
//      for (int i=0; i<accum.size(); ++i){
//        std::cout << accum[i] << ", ";
//      }
//
//      std::cout << "\n----------------------------" << std::endl;


      for (int i = 0; i< im.nElements(); ++i){
        im_out(i) = (255.0f/256) * ( accum[std::floor(im(i)/binWidth)]/float(im.nElements()) ) ;
      }//todo: check if L-1 in Sapiro's note corresponds to 255/256.f

      im_out.histogram(hist_out, binWidth);
    }


}
