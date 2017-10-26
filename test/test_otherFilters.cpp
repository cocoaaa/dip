//
// Created by HayleySong on 9/14/17.
//

#include "Image.h"
#include "Filter.h"



    void test1(){
      dip::Image im(101,101,1);
      im.fill(50, 101, 1.0f );
      im.write("./output/half.png");
    }





int main(){
  test1();
//  test2();
//  test3();

}
