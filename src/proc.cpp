//
// Created by HayleySong on 8/18/17.
//

#include <iostream>
#include <vector>
#include "Image.h"

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
//todo: make it as a member of Image class?
    void histogram(const Image &im, std::vector<int> &counts, float binWidth ){
      std::cout << "binWidth: " << binWidth << std::endl;
      // resize counts and set values to zero
      int nBins =  ceil(1/binWidth);
      if (counts.size() != nBins){
        std::vector<int>(nBins).swap(counts);
      } else{
        std::fill(counts.begin(), counts.end(), 0);
      }

      // if val is in [0+binWidth*i, 0+binWidth*(i+1)), val is assigned to ith bin
      // that is, i = integer part of (val/binWidth)
      for (int i=0; i<im.nElements(); ++i){
        counts[ floor(im(i)/binWidth) ] ++;
      }
    }

    void equalize_histogram(const Image &im, Image &im_out, std::vector<int> &hist_out){
      float binWidth = 0.1;//todo
      std::vector<int> in; //todo rename it to hist1
      histogram(im, in, binWidth );
      std::vector<int>(in.size()).swap(out);

      //todo: set im_out ready for the output
      if (im_out.nElements() != im.nElements()){
        im_out.reinit_all(im.w(), im.h(), im.c());
      }
      std::vector<int> accum(in.size(),0);

      accum[0] = in[0];
      for (int i = 1; i< in.size(); ++i){
        accum[i] = accum[i-1] + in[i];
      }

      for (int i = 0; i< im.nElements(); ++i){
        im_out(i) = accum[ floor(im(i)/binWidth) ];
      }

      histogram(im_out, hist_out, binWidth); //todo: return im_out and hist_out by reference?

    }


}
