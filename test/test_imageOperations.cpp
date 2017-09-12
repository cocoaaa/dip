//
// Created by HayleySong on 8/22/17.
//

#include "Image.h"
#include "imageOperations.h"
#include "print.h"

int main(){
  dip::Image im_r(10,10,3), im_g(10,10,3), im_b(10,10,3);
  im_r.fill_channel(0,1.0f);
  im_g.fill_channel(1, 1.0f);
  im_b.fill_channel(2, 1.0f);

  im_r.debugwrite();
  im_g.debugwrite();
  im_b.debugwrite();

  std::vector<float> vec(im_r.nElements());
  im_r.copyToVec(vec);
  dip::Image im_r_copy(vec, im_r.w(), im_r.h(), im_r.channels());
  im_r_copy.write("./output/rcopy.png");

  int k = 11;
  dip::Image impulse;
  impulse = dip::getImpulse(k);
  impulse.write("./output/impulse.png");
//

}

