#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <cmath>
using namespace cs225;

//custom constructor to read in a png file
MyColorPicker::MyColorPicker(std::string file) {
  png.readFromFile(file);
}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  srand(time(NULL));
  int StartHue = rand() % 360;
  //set luminance
  double luminance = 0.6;
  //parse width/height to int
  // int WidthAsInt = (int)png.width();
  // int HeightAsInt = (int)png.height();
  int EucDist = sqrt(pow(x, 2) + pow(y, 2));
  //generate a new pixel and append
  cs225::HSLAPixel CurPixel((StartHue + (int)(EucDist * 0.6)) % 360, 1, luminance);
  return CurPixel;
}
