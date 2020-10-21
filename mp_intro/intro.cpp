#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>


void rotate(std::string inputFile, std::string outputFile) {
  
  cs225::PNG InputImage, OutputImage;
  InputImage.readFromFile(inputFile);
  OutputImage = InputImage;
  for (unsigned height = 0; height < InputImage.height(); height++) {
    for (unsigned width = 0; width < InputImage.width(); width++) {
      cs225::HSLAPixel & CurPixel = InputImage.getPixel(width, height);
      OutputImage.getPixel(InputImage.width() - width - 1, InputImage.height() - height - 1) = CurPixel;
    }
  }
  OutputImage.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  
  cs225::PNG png(width, height);
  //seed random & generate start hue from 0 to 360
  srand(time(NULL));
  int StartHue = rand() % 360;
  //set luminance
  double luminance = 0.6;
  //parse width/height to int
  int WidthAsInt = (int)width;
  int HeightAsInt = (int)height;
  std::ofstream myfile;
  myfile.open ("example.txt");
  //find euclidean distance and assign corresponding value
  for (int h = 0; h < HeightAsInt; h++) {
    for (int w = 0; w < WidthAsInt; w++) {
      //calculate euclidean distance to upper left corner
      int EucDist = sqrt(pow(h, 2) + pow(w, 2));
      //generate a new pixel and append
      cs225::HSLAPixel CurPixel((StartHue + (int)(EucDist * 0.1)) % 360, 1, luminance);
      
        myfile << (StartHue + (int)(EucDist * 0.1)) % 360 << "\n";
      png.getPixel(w, h) = CurPixel;
    }
  }

  myfile.close();
  return png;
}
