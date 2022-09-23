/*
*  @file blendTileColorPicker.h
*  Definition of an edge tile color picker.
*
*/
#ifndef _EDGECOLORPICKER_H_
#define _EDGECOLORPICKER_H_

#include "colorPicker.h"

/*
*  edgeColorPicker: a functor that determines the color that should be used
*  given a point which may or may not be on the boundary of a color region.
*  Note that the physical boundaries of the image will qualify as a region boundary.
*/
class EdgeColorPicker : public ColorPicker
{
public:
  /*
  *  Constructs a new EdgeColorPicker.
  *
  *  @param inputimage - original image to be colored
  *  @param b_color - color of the border
  *  @param width - width of the border to be painted
  *  @param s - seed point from flood fill configuration, must include original image color
  *  @param tol - tolerance threshold from flood fill configuration
  */
  EdgeColorPicker(PNG& inputimage, RGBAPixel b_color, unsigned int width, PixelPoint s, double tol);

  /*
  *  Picks the color for pixel (x, y).
  *  First determines whether p is a border pixel or not.
  * 
  *  A border pixel is one which is within (<=) borderwidth of a non-fillable pixel
  *  (i.e. at least one of the pixels within borderwidth of p will not be reached by
  *  the filling algorithm.
  * 
  *  A border pixel will be colored using the bordercolor.
  * 
  *  A fillable non-border pixel will take the average color of all pixels within 
  *  borderwidth of p. Make sure that you are averaging from the original
  *  image colors!
  *
  *  @param  p - The point for which you're picking a color
  *  @return The color chosen for (p).
  */
  virtual RGBAPixel operator()(PixelPoint p);

  bool isBorderPixel(PixelPoint p);

private:
  PNG referenceimg; // original image used in the flood fill algorithm
  RGBAPixel bordercolor;
  unsigned int borderwidth;
  PixelPoint seed; // seed point from flood fill configuration
  double tolerance; // tolerance from flood fill configuration
};

#endif
