#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
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
  // TODO: Part 3

  return png;
}
