//
// Created by HayleySong on 8/19/17.
//

#include <iostream>
#include <algorithm> // minmax of std::vector

#include <pangolin/pangolin.h>


#include "Image.h"
#include "proc.h"
#include "print.h"

int main(/*int argc, char* argv[]*/)
{
  // Get an image's histogram
  dip::Image im(10,10,1);
  im.fill(5,5,0.5f);

  float binWidth = 0.01f;
  std::vector<int> hist;
  im.histogram(hist, binWidth);

  int nBins = hist.size();
  auto minmax_pair = std::minmax_element(hist.begin(), hist.end());
  int minCount = *minmax_pair.first, maxCount = *minmax_pair.second;
  float padding = 1.5f; // for padding on the right(top) of the x-axis(y-axis)

  dip::print("binWidth", binWidth);
  dip::print("number of bins", nBins);
  dip::print("min count", minCount, "max count", maxCount);
  dip::print("padding", padding);

//todo: drawHistogram(hist);
  //hist conversion for datalog
  std::vector<float> hist_float;
  for (int i=0; i<hist.size(); ++i){
    hist_float.push_back( (float)hist[i] );
  }

  // Create OpenGL window in single line
  pangolin::CreateWindowAndBind("Main",640,480);

  // Data logger object
  pangolin::DataLog log(im.nElements());
  dip::print("number of im elements", im.nElements());
  dip::print("number of samples in log", log.Samples());
  log.Log(hist_float);
  dip::print("number of samples in log", log.Samples());



//
  const float tinc = 1.f;
//
//  // OpenGL 'view' of data. We might have many views of the same data.
  pangolin::Plotter plotter(&log,0.0f, (float)nBins + padding, 0.0f,  maxCount + padding, binWidth, 1.0f);
//  plotter.SetBounds(0.0, nBins+padding , 0.0, maxCount+padding);

  plotter.Track("$i"); //todo: index of hist?

  // Add some sample annotations to the plot
//  plotter.AddMarker(pangolin::Marker::Vertical,   -1000, pangolin::Marker::LessThan, pangolin::Colour::Blue().WithAlpha(0.2f) );
//  plotter.AddMarker(pangolin::Marker::Horizontal,   100, pangolin::Marker::GreaterThan, pangolin::Colour::Red().WithAlpha(0.2f) );
//  plotter.AddMarker(pangolin::Marker::Horizontal,    10, pangolin::Marker::Equal, pangolin::Colour::Green().WithAlpha(0.2f) );

  pangolin::DisplayBase().AddDisplay(plotter);

  float t(0.0f);
  // Default hooks for exiting (Esc) and fullscreen (tab).

  glEnableClientState(GL_VERTEX_ARRAY);

  while( !pangolin::ShouldQuit())

  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINES);

    t += tinc;

    // Render graph, Swap frames and Process Events
    pangolin::FinishFrame();
  }

  return 0;
}