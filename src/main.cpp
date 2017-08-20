// ref: https://stackoverflow.com/questions/2076475/reading-an-image-file-in-c-c

#include <iostream>
#include <pangolin/pangolin.h>
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

  int w, h, bpp;
  unsigned char *rgb_image1 = stbi_load("../data/boston1.jpeg", &w, &h, &bpp, 0);
  unsigned char *rgb_image2 = stbi_load("../data/boston10.jpeg", &w, &h, &bpp, 0);

//  uint8_t *rgb_image = stbi_load("../data/boston1.jpeg", &w, &h, &bpp, 0);
//  stbi_image_free(rgb_image);
  std::cout << "width, height, bpp: " << w << ", " << h << ", " << bpp << std::endl;

  // Create OpenGL window in single line
  pangolin::CreateWindowAndBind("Main",640,480);

  // 3D Mouse handler requires depth testing to be enabled
  glEnable(GL_DEPTH_TEST);


  pangolin::View& d_image1 = pangolin::Display("image1")
      .SetAspect(640/480.0f);

  pangolin::View& d_image2 = pangolin::Display("image2")
      .SetAspect(640/480.0f);


  // LayoutEqual is an EXPERIMENTAL feature - it requires that all sub-displays
  // share the same aspect ratio, placing them in a raster fasion in the
  // viewport so as to maximise display size.
  pangolin::Display("multi")
      .SetBounds(0.0, 1.0, 0.0, 1.0)
      .SetLayout(pangolin::LayoutEqual)
      .AddDisplay(d_image1)
      .AddDisplay(d_image2);

  pangolin::GlTexture
      imageTexture1(w,h,GL_RGB,false,0,GL_RGB,GL_UNSIGNED_BYTE),
      imageTexture2(w,h,GL_RGB,false,0,GL_RGB,GL_UNSIGNED_BYTE);

  //upload image data to GPU
  imageTexture1.Upload(rgb_image1,GL_RGB,GL_UNSIGNED_BYTE);
  imageTexture2.Upload(rgb_image2,GL_RGB,GL_UNSIGNED_BYTE);

  // Default hooks for exiting (Esc) and fullscreen (tab).
  while(!pangolin::ShouldQuit())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //display the image
    d_image1.Activate();
    glColor3f(1.0,1.0,1.0);
    imageTexture1.RenderToViewport();

    //display the image
    d_image2.Activate();
    glColor3f(1.0,1.0,1.0);
    imageTexture2.RenderToViewport();

    pangolin::FinishFrame();
  }

  delete[] rgb_image1;
  delete[] rgb_image2;

  return 0;


}
