#include "Filter.h"
#include <vector>
#include <cmath>
#include <iostream>

namespace dip{
	class Guassian : public Filter{
		Guassian(){ };
		Gaussian(int w, int h, float sigma);

	private:
		float sigma_;
	};

}

