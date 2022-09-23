/**
 * @file negativeColorPicker.h
 * Definition of a negative color picker.
 *
 */
#ifndef _NEGATIVECOLORPICKER_H_
#define _NEGATIVECOLORPICKER_H_

#include "colorPicker.h"

 /**
  * NegativeColorPicker: a functor that determines the color that should be
  * used given an x and y coordinate using a negative pattern. You can create
  * private helper functions inside this class, as well as local storage, if
  * necessary. Remember to overload a destructor if you need to.
  *
  */
class NegativeColorPicker : public ColorPicker
{
public:
  /**
   * Constructs a new NegativeColorPicker.
   *
   * @param inputimg - the original image.
   */
  NegativeColorPicker(PNG& inputimg);

  /**
   * Picks the color for pixel (x, y).
   *
   * Returns the a RGBAPixel which uses the negation on all RGB channels (alpha stays the same)
   * of the color at point p in the original image.
   * Refer to the RGBA documentation in lab_intro to determine an appropriate meaning of
   * "negation" for each RGB channel.
   */
  virtual RGBAPixel operator()(PixelPoint p);

private:
  /**
   * @todo Define any additional private member variables or helper
   *	functions here as you see fit.
   */
  PNG referenceimg; // original image used in the flood fill algorithm
};

#endif
