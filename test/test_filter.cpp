#include <iostream>
#include "Image.h"
#include "imageOperations.h"
#include "Filter.h"

using namespace dip;
int main(){
	Image im;
	im = getImpulse(500);
	im.write("./output/impulse.png");
	
	// Test constructors
	std::vector<float> vec {1/9.f,1/9.f,1/9.f,1/9.f,1/9.f,1/9.f,1/9.f,1/9.f,1/9.f};
	Filter box, box1(11,11), box2(vec,3,3);
	Eigen::VectorXf boxValue(121);
	boxValue.setOnes();
	boxValue.normalize();
	box1.setKernel( std::vector<float>(boxValue.data(), boxValue.data() + 121), 11, 11);

	// Test convolve
	Image convolved1, convolved2;

	convolved1 = box1.convolve(im);
	convolved2 = box2.convolve(im);

	convolved1.write("./output/c1.png");
	convolved2.write("./output/c2.png");

	Image b1(box1.kernel, box1.w_, box1.h_,0);
	Image b2(box2.kernel, box2.w_, box2.h_,0);
	b1.write("./output/b1.png");
	b2.write("./output/b2.png");

	// Test Guassian filter
	Gaussian gFilter(11,11,1);
	Gaussian gFilter_big(101,101,10);

	Image img_gFilter(gFilter.kernel, 11, 11, 1);
	img_gFilter.write("./output/g_11x11.png");

	Image img_gFilter_big(gFilter_big.kernel, 101, 101, 1);
	img_gFilter_big.write("./output/g_101x101.png");

	Image gOut1, gOut2;
	gOut1 = gFilter.convolve(im);
	gOut1.write("./output/gOut1.png");

	gOut2 = gFilter.convolve(im);
	gOut2.write("./output/gOut2.png");

  //Test Second gaussian filter constructor
  float sigma = 3.0f;
  Gaussian g(sigma);
	Image img_g(g.kernel, g.w_, g.h_, 1);
  Image out3;
  out3 = g.convolve(im);
  out3.write("./output/out3.png");
	img_g.write("./output/g_3f.png");

  float sigma2 = 10.f;
  Gaussian g2(sigma2);
	Image img_g2(g2.kernel, g2.w_, g2.h_, 1);
	img_g2.write("./output/g_10f.png");
  Image out4;
  out4 = g2.convolve(im);
  out4.write("./output/out4.png");


}