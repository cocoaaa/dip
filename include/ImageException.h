//
// Created by HayleySong on 8/16/17.
// Replication of the code from class 6.838 for learning purpose
//

#ifndef DIP_IMAGEEXCEPTION_H
#define DIP_IMAGEEXCEPTION_H

#include <stdexcept>
#include <stdio.h>

class DivideByZeroException : public std::runtime_error {
public:
  DivideByZeroException(): std::runtime_error("Division by zero."){}
};

class MismatchedDimensionsException : public std::runtime_error{
public:
  MismatchedDimensionsException(): std::runtime_error("Image dimensions are not the same."){}
};

class NegativeDimensionException: public std::runtime_error{
public:
  NegativeDimensionException(): std::runtime_error("Image dimensions must be nonnegative."){}
};

class OutofBoundsException: public std::runtime_error{
public:
OutofBoundsException(): std::runtime_error("Image index is out of bounds."){}
};

class BinWidthException: public std::runtime_error{
public:
  BinWidthException(): std::runtime_error("Bin Width must be in [0,1] range.\n"){}
};

class PixelValueException: public std::runtime_error{
public:
  PixelValueException(): std::runtime_error("Float pixel Value must be in [0,1] range.\n"){}
};
#endif //DIP_IMAGEEXCEPTION_H
