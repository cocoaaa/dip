#include <iostream>
#include "Image.h"
#include "imageOperations.h"
#include "Filter.h"

using namespace dip;
int main(){
	Image im;
	im = getImpulse(100);
	
	// Test constructors
	std::vector<float> vec {1/9.f,1/9.f,1/9.f,1/9.f,1/9.f,1/9.f,1/9.f,1/9.f,1/9.f}
	Filter box, box1(10,10), box2(vec);
	box1.info();
	box2.info();

	// Test convolve
	Image convolved1 = box1.convolve(im);
	Image convolved2 = box2.convolve(im);

	convolved1.write("./output/c1.png");
	convolved2.write("./output/c2.png");

	// Test Guassian filter
	Gaussian gFilter(11,11,3), gFilter_big(101,101,1);

	Image img_gFilter(gFilter.kernel, 11, 11, 1);
	img_gFilter.write("./output/gFilter_11x11.png");

	Image img_gFilter_big(gFilter_big, 101, 101, 1);
	img_gFilter_big.write("./output/gFilter_101x101.png");


}