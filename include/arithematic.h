//
// Created by HayleySong on 10/24/17.
//

#ifndef DIP_ARITHEMATIC_H
#define DIP_ARITHEMATIC_H

#include <Eigen/Dense>
namespace dip{

    template <typename Derived1, typename Derived2>
    bool isAllClose(
        const Eigen::DenseBase<Derived1>& A,
        const Eigen::DenseBase<Derived2>& B,
        const float precision=1e-6){
      assert(A.size() == B.size());
      for (int i=0; i<B.size(); ++i){
        if( abs(A(i) - B(i)) > precision ){
          return false;
        }
      }
      return true;
    }

}


#endif //DIP_ARITHEMATIC_H
