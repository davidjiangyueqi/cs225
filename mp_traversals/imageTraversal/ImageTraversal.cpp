#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal() {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start)
            : traversal(traversal), start(start) {
              current = traversal->peek();
            }

// ImageTraversal::Iterator::~Iterator() {
//   /** @todo [Part 1] */
//   //if (traversal != nullptr) delete traversal;
// }

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  PNG* png = traversal->getPNG();
  Point cur = traversal->pop();
  traversal->setVisit(cur);
  Point right(cur.x + 1, cur.y);
  Point below(cur.x, cur.y + 1);
  Point left(cur.x - 1, cur.y);
  Point above(cur.x, cur.y - 1);

  HSLAPixel& startPixel = png->getPixel(start.x, start.y);
  double tolerance = traversal->getTolerance();
  //check right
  if (right.x < png->width()) {
    HSLAPixel& pixel = png->getPixel(right.x, right.y);
    double delta = calculateDelta(startPixel, pixel);
    //add to visit
    if (delta < tolerance && !traversal->getVisit(right)) {
      traversal->add(right);
    }
  }
  //check below
  if (below.y < png->height()) {
    HSLAPixel& pixel = png->getPixel(below.x, below.y);
    double delta = calculateDelta(startPixel, pixel);
    if (delta < tolerance && !traversal->getVisit(below)) {
      traversal->add(below);
    }
  }

  //left
  if (left.x < png->width()) {
    HSLAPixel& pixel = png->getPixel(left.x, left.y);
    double delta = calculateDelta(startPixel, pixel);
    if (delta < tolerance && !traversal->getVisit(left)) {
      traversal->add(left);
    }
  }

  //above
  if (above.y < png->height()) {
    HSLAPixel& pixel = png->getPixel(above.x, above.y);
    double delta = calculateDelta(startPixel, pixel);
    if (delta < tolerance && !traversal->getVisit(above)) {
      traversal->add(above);
    }
  }
  while (!traversal->empty() && (traversal->getVisit(traversal->peek()))) {
    traversal->pop();
  }
  if (traversal->empty()) {
    traversal = nullptr;
    return *this;
  }
  current = traversal->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  // if (other.traversal == nullptr && traversal == nullptr) return false;
  // if (other.traversal == nullptr && traversal != nullptr) return true;
  // if (other.traversal != nullptr && traversal == nullptr) return true;

  // return traversal != other.traversal;
  //return !(end_ && other.end_);
  if (!traversal && other.traversal) {
    return false;
  } else if (traversal || other.traversal) {
    return true;
  }
  return traversal != other.traversal;
}

