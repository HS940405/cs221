/*
*  @file edgeColorPicker.cpp
*  Implements the edge color picker for CPSC 221 PA2.
*
*/

#include "edgeColorPicker.h"

/*
 *  Constructs a new EdgeColorPicker.
 *
 *  @param inputimage - original image to be colored
 *  @param b_color - color of the border
 *  @param width - width of the border to be painted
 *  @param s - seed point from flood fill configuration, must include original image color
 *  @param tol - tolerance threshold from flood fill configuration
 */
EdgeColorPicker::EdgeColorPicker(PNG& inputimage, RGBAPixel b_color, unsigned int width, PixelPoint s, double tol)
{
  referenceimg = inputimage;
  bordercolor = b_color;
  borderwidth = width;
  seed = s;
  tolerance = tol;
}

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
RGBAPixel EdgeColorPicker::operator()(PixelPoint p)
{
  double totalr = 0;
  double totalb = 0;
  double totalg = 0;
  double totala = 0;
  int totalpixels = 0;
  // Determine if p is border pixel or not

  for (int x = p.x - (int)borderwidth; x <= (int)p.x + (int)borderwidth; x++) {
    for (int y = p.y - (int)borderwidth; y <= (int)p.y + (int)borderwidth; y++) {
      double diagonal = sqrt((p.x - (double)x) * (p.x - (double)x) + (p.y - (double)y) *(p.y - (double)y));

      if (x < 0 || x >= (int)referenceimg.width() || y < 0 || y >= (int)referenceimg.height() && diagonal <= borderwidth) {
        // if any of the pixels within borderwidth of p is out of bounds
        return bordercolor;

      } else if (referenceimg.getPixel(x,y)->dist(seed.color) > tolerance && diagonal <= borderwidth){   // if pixel is within bounds but its colordist with seed > tolerance
        return bordercolor;

      } else if (diagonal <= borderwidth) {
        RGBAPixel* originalpixel = referenceimg.getPixel(x,y);  // pointer to pixel from original image to add up rgb values
        totalr += originalpixel->r;
        totalb += originalpixel->b;
        totalg += originalpixel->g;
        totala += originalpixel->a;
        totalpixels++;
      }
    }
  }

  int avgr = (int) (totalr / totalpixels);
  int avgb = (int) (totalb / totalpixels);
  int avgg = (int) (totalg / totalpixels);
  double avga = totala / totalpixels;
  return RGBAPixel(avgr, avgg, avgb, avga);
}



  /*if (isBorderPixel(p)) {       // not going through here??
    p.color = bordercolor;

  } else {   
    if (p.color.dist(seed.color) <= tolerance) {     // if p is a FILLABLE non-border pixel (aka. is a pixel with color distance from seed <= tolerance)
    int totalr = 0;
    int totalg = 0;
    int totalb = 0;
    int numpixels = 0;

    for (int x = borderwidth + 1; x < referenceimg.width() - borderwidth; x++) 
    {
      for (int y = borderwidth + 1; y < referenceimg.height() - borderwidth; y++) 
      {
        RGBAPixel* original = referenceimg.getPixel(x, y);
        totalr += original->r;
        totalg += original->g;
        totalb += original->b;
        numpixels++;
      }
    }

    int totalpixels = borderwidth * referenceimg.height();
    p.color.r = totalr/numpixels;
    p.color.g = totalg/numpixels;
    p.color.b = totalb/numpixels;
    }

    return p.color;
  }    */
  

// RGBAPixel EdgeColorPicker::operator()(PixelPoint p)
// {
//   if (isBorderPixel(p)) {       // not going through here??
//     p.color = bordercolor;

//   } else {   
//     int totalr = 0;
//     int totalg = 0;
//     int totalb = 0;
//     int numpixels = 0;

//     //for (int x = p.x - borderwidth; x < p.x + borderwidth; x++) ?????
//     for (int x = borderwidth + 1; x < referenceimg.width() - borderwidth; x++) 
//     {
//       for (int y = borderwidth + 1; y < referenceimg.height() - borderwidth; y++) 
//       {
//         RGBAPixel* original = referenceimg.getPixel(x, y);
//         if (original->dist(seed.color) <= tolerance) {
//           totalr += original->r;
//           totalg += original->g;
//           totalb += original->b;
//           numpixels++;
//         }
//       }
//     }
//     p.color.r = totalr/numpixels;
//     p.color.g = totalg/numpixels;
//     p.color.b = totalb/numpixels;
//   }

//   return p.color;
//   // if (inBorder(p) || seed.color.dist(*referenceimg.getPixel(p.x, p.y)) > tolerance) {
//   //   p.color = bordercolor;
//   //   if (p.x == 50, p.y == 50) {
//   //     cout << seed.color.dist(*referenceimg.getPixel(p.x, p.y)) << endl;
//   //   }
//   // } else {
//   //   int totalr = 0;
//   //   int totalg = 0;
//   //   int totalb = 0;
//   //   int numpixels = 0;

//   //   for (int x = borderwidth + 1; x < referenceimg.width() - borderwidth; x++) 
//   //   {
//   //     for (int y = borderwidth + 1; y < referenceimg.height() - borderwidth; y++) 
//   //     {
//   //       RGBAPixel* original = referenceimg.getPixel(x, y);
//   //       totalr += original->r;
//   //       totalg += original->g;
//   //       totalb += original->b;
//   //       numpixels++;
//   //     }
//   //   }

//   //   int totalpixels = borderwidth * referenceimg.height();
//   //   p.color.r = totalr/numpixels;
//   //   p.color.g = totalg/numpixels;
//   //   p.color.b = totalb/numpixels;
//   // }
  
//   // return p.color;
  
// }

bool EdgeColorPicker::isBorderPixel(PixelPoint p) {
  if (p.x <= borderwidth || referenceimg.width() - p.x <= borderwidth ||
  p.y <= borderwidth || referenceimg.height() - p.y <= borderwidth) {
    return true;
  } else {
    RGBAPixel* originalpixel = referenceimg.getPixel(p.x, p.y);
    return originalpixel->dist(seed.color) > tolerance;
    // for (int x = 1; x <= referenceimg.width() - borderwidth; x++) {
    //   for (int y = 1; y <= referenceimg.height() - borderwidth; y++) {
    //     RGBAPixel* originalpixel = referenceimg.getPixel(x,y);

    //     if (originalpixel->dist(seed.color) > tolerance) {
    //       return true;
    //     }
    //   }
    // }
  }
}
