//
// Created by HayleySong on 8/21/17.
//

#include "print.h"
#include <vector>
#include <string>
#include <iostream>

int main(){
  std::vector<int> vecInt;
  std::vector<float> vecFloat;

  for (int i=0; i <10; ++i){
    vecInt.push_back(i);
    vecFloat.push_back(i*10.f);
  }

  std::cout << "\nTEST1: vecInt" << std::endl;
  dip::printN(vecInt, 10);
  std::cout << "---" << std::endl;
  dip::printInRange(vecInt, 1, 3);

  std::cout << "\nTEST2: vecFloat" << std::endl;
  dip::printN(vecFloat, 10);
  std::cout << "---" << std::endl;
  dip::printInRange(vecFloat, 1, 3);

//   ---------
  std::cout << "\nTEST3: print name, val pair(s)" << std::endl;
  dip::print("n1", 10);
  dip::print("n1", 0.01);


  dip::print ("n1", 10, "n2", 20 );
  dip::print ("n1", 10, "n2", 20.0f );
  dip::print ("n1", 10.3, "n2", 20.2f );





}
