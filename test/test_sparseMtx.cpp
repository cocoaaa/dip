#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/SparseCore>


using SpMat = Eigen::SparseMatrix<float>;
using T = Eigen::Triplet<float>;

void test_basic(){
  int nr{10};
  int nc{20};
  std::vector<T> tripletList;
  tripletList.reserve(10);

  for (int i=0; i<10; ++i){
    tripletList.push_back(T(i,i,1));
    tripletList.push_back(T(i,i,1));//this will result in summing up duplicate entries
  }

  SpMat spMat(nr, nc);
  spMat.setFromTriplets(tripletList.begin(), tripletList.end());
  std::cout << spMat << std::endl;

  spMat.coeffRef(0,0) = 5;
  std::cout << "Replace value from 1 to 5 at (0,0) using coeffRef: \n" << spMat << std::endl;

  spMat.coeffRef(9,9) += 3;
  std::cout << "Increased (9,9) by 3 using coeffRef: \n" << spMat << std::endl;

  spMat.insert(9,19) = 10;
  std::cout << "Can use insert if the sparse matrix doesn't already have a value at (i,j)\n";
  std::cout << "Inserted 10 to (9,19)\n" << spMat << std::endl;
}

void test_access(){
  int nr = 10;
  int nc = 20;
  SpMat mat(nr, nc);
  std::cout << "Colmwise---" << std::endl;
  std::cout << "nr, nc: " << mat.rows() << "," << mat.cols() << std::endl;
  std::cout << "innerSize, outerSize: " << mat.innerSize() << ", " << mat.outerSize() << std::endl;

}

int main(){
//  test_basic();
//  test_access();


}