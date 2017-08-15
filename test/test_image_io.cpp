//
// Created by HayleySong on 7/31/17.
//
// ref: https://stackoverflow.com/questions/2076475/reading-an-image-file-in-c-c

#include <iostream>

#include <Eigen/Dense>
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


int main(){
  enum class Quality{
    LOW = 1,
    MID = 50,
    HIGH = 100
  };

  int width, height, bpp;
  uint8_t *rgb_image = stbi_load("../data/boston1.jpeg", &width, &height, &bpp, 0);
//  stbi_image_free(rgb_image);

  std::cout << "width, height, bpp: " << width << ", " << height << ", " << bpp << std::endl;

  // Write
//  stbi_write_png("out.png", width, height, 3, rgb_image, width*3);
  stbi_write_jpg("out.jpg", width, height, bpp, rgb_image, static_cast<int>(Quality::HIGH));

  std::cout << "written." << std::endl;
}
