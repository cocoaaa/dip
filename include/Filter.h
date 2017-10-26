//
// Created by HayleySong on 9/12/17.
//

#ifndef DIP_FILTER_H
#define DIP_FILTER_H

#include <vector>
#include <cmath>
#include "Image.h"
#include <Eigen/Dense>


namespace dip{
    class Filter {
    public:
      Filter();
      Filter(int w, int h);
      Filter(const std::vector<float> &vec, int w, int h);
      Filter(const Eigen::MatrixXf &mtx, int w, int h);
      ~Filter() { };

      void setKernel(const std::vector<float> &vec, int w, int h);
    // Convolution
    Image convolve(const Image &im, bool clamp=true) const;

    // Kernel access function
    const float operator()(int x, int y) const;
    float operator()(int x, int y);

    // Show kernel
    void info() const;

    // protected:
    void reInit(int w, int h, int ksize);

      int w_, h_;
      int ksize;
      std::vector<float> kernel;

    };

    // Gaussian Filter
    class Gaussian : public Filter{
    public:
      Gaussian(){ };
      Gaussian(int w, int h, float sigma, float truncate=3.0f);
      Gaussian(float sigma, float truncate=3.0f);


    private:
      float sigma_;
    };


    // Gradients
    std::vector<float> gaussian_1d_values(float sigma, float truncate=3.0f);
    std::vector<float> gaussian_2d_values(float sigma, float truncate=3.0f);


}



#endif //DIP_FILTER_H
