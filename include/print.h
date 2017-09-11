//
// Created by HayleySong on 8/21/17.
//

#ifndef DIP_PRINT_H
#define DIP_PRINT_H

#include <iostream>
#include <vector>
#include <cassert>

namespace dip {
    template <typename T>
    void printN(const std::vector<T> &vec, size_t n) {
      // print N elements of the vector from the 0th index
      assert(n <= vec.size());
      for (size_t i = 0; i < n-1; ++i) {
        std::cout << vec[i] << ", ";
      }
      std::cout << vec[n-1] << std::endl;
    }

    template <typename T>
    void printInRange(const std::vector<T> &vec, size_t start, size_t end) {
      //print out vec[start], ... vec[end] inclusively.
      assert(start < vec.size() && end < vec.size());
      for (size_t i = start; i < end ; ++i) {
        std::cout << vec[i] << ", ";
      }
      std::cout << vec[end] << std::endl;

    }

    template <typename T>
    void print(const std::string &name, const T &val){
      std::cout << "--- " << name << ": " << val << std::endl;
    }

    template <typename T1, typename T2>
    void print(const std::string &name1, const T1 &val1,
               const std::string &name2, const T2 &val2){
      print(name1, val1);
      print(name2, val2);
    };

}

#endif //DIP_PRINT_H
