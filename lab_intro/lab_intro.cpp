/**
 * @file lab_intro.cpp
 * Implementations of image manipulation functions.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using cs225::HSLAPixel;
using cs225::PNG;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {

  for (unsigned x = 0; x < image.height(); x++) {
    for (unsigned y = 0; y < image.width(); y++) {
      double EucDist = sqrt(pow(x - centerY, 2) + pow(y - centerX, 2));
      if (EucDist * 0.005 <= 0.8) {
        image.getPixel(y, x).l = image.getPixel(y, x).l * (1 - EucDist * 0.005);
      } else {
        image.getPixel(y, x).l = image.getPixel(y, x).l * 0.2; 
      }
    }
  }
  return image;
  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  //hue for illini ornage/blue
  double orange = 11;
  double blue = 216;

  //loop thru every pixel
  for (unsigned x = 0; x < image.height(); x++) {
    for (unsigned y = 0; y < image.width(); y++) {
      HSLAPixel & pixel = image.getPixel(y, x);
      double OrangeDist = abs(pixel.h - orange);
      double BlueDist = abs(pixel.h - blue);
      OrangeDist = OrangeDist >= 180 ? 360 - OrangeDist : OrangeDist;
      BlueDist = BlueDist >= 180 ? 360 - BlueDist : BlueDist;
      pixel.h = OrangeDist <= BlueDist ? orange : blue;
    }
  }
  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs to be averaged together.
* @param secondImage The second of the two PNGs to be averaged together.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {

  int HeightThreshold = firstImage.height() < secondImage.height() ? firstImage.height() : secondImage.height();
  int WidthThreshold = firstImage.width() < secondImage.width() ? firstImage.width() : secondImage.width();

  for (int x = 0; x < HeightThreshold; x++) {
    for (int y = 0; y < WidthThreshold; y++) {
      //check pixel luminance
      if (secondImage.getPixel(y, x).l == 1) {
        //increase the target image luminance
        firstImage.getPixel(y, x).l += 0.2;
        if (firstImage.getPixel(y, x).l > 1) {
          firstImage.getPixel(y, x).l = 1;
        }
      }
    }
  }
  return firstImage;
}
