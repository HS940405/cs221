/**
 * @file block.cpp
 * @author your name(s)
 *
 * Implements a rectangular image portion block for CPSC 221 PA1
 *
 * COMPLETE THE FUNCTION BODIES IN THIS FILE AND SUBMIT TO PRAIRIELEARN
 */

#include "block.h"

/**
 *  Sets the values in the data attribute, based on the w x h pixels rectangular region of sourceimg
 *  with the upper-left corner at (left, upper). The orientation of the pixels in the data vector
 *  must match with the orientation of the pixels in the PNG.
 *
 *  @param w - the width (in pixels) of the rectangular subimage region
 *  @param h - the height (in pixels) of the rectangular subimage region
 *  @param upper - the y-coordinate of the subimage region's upper-left corner
 *  @param left - the x-coordinate of the subimage regions's upper-left corner
 *  @param sourceimg - the input PNG image
 *
 *  @pre upper and left (and upper + h - 1, left + w - 1) are valid vector indices
 *  @post pixels contains sourceimg's pixel data starting from (left, upper)
 */
void Block::Build(unsigned int w, unsigned int h, unsigned int upper, unsigned int left, const PNG& sourceimg) {

  for (unsigned int x = 0; x < w; x++) {
    vector<RGBAPixel> col;
    for (unsigned int y = 0; y < h; y++) {
      RGBAPixel* pixel = sourceimg.getPixel(left + x, upper + y);
      col.push_back(*pixel);
    }
    pixels.push_back(col);
  }
}

/**
 *  Writes the pixel color data into the target PNG, starting from (left, upper)
 *
 *  @pre upper, left are valid image indices
 *  @pre the rectangular region beginning at (left, upper) can completely receive all of the data attribute's color
 *  @post target PNG's subimage region has been filled with data attribute's pixel data
 */
void Block::Render(unsigned int upper, unsigned int left, PNG& targetimg) const {

  for (unsigned int x = left; x < left + pixels.size(); x++) {
    for (unsigned int y = upper; y < upper + pixels[1].size(); y++) {
      RGBAPixel* pixel = targetimg.getPixel(x, y);
      pixel->r = pixels[x-left][y-upper].r;
      pixel->g = pixels[x-left][y-upper].g;
      pixel->b = pixels[x-left][y-upper].b;
      pixel->a = pixels[x-left][y-upper].a;
    }
  }
}

/**
 *  Mirror this block's pixel data horizontally (along a vertical axis)
 *
 *  @post pixel data in this Block has been mirrored horizontally
 */
void Block::FlipHorizontal() {

  for (unsigned int x = 0; x < pixels.size() / 2; x++) {
    vector<RGBAPixel> temp = pixels[x];
    pixels[x] = pixels[pixels.size() - 1 - x];
    pixels[pixels.size() - 1 - x] = temp;
  }
}

/**
 *  Mirror this block's pixel data vertically (along a horizontal axis)
 *
 *  @post pixel data in this Block has been mirrored vertically
 */
void Block::FlipVertical() {
  for (unsigned int x = 0; x < pixels.size(); x++) {
    for (unsigned int y = 0; y < pixels[0].size() / 2; y++) {
      RGBAPixel temp = pixels[x][y];
      pixels[x][y] = pixels[x][pixels[0].size() - 1 - y];
      pixels[x][pixels[0].size() - 1 - y] = temp;
    }
  }
}

/**
 *  Returns the width (in pixels) of this Block
 *
 *  @return rectangular Block's width
 */
unsigned int Block::GetWidth() const {
  // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
  return pixels.size();
}

/**
 *  Returns the height (in pixels) of this Block
 *
 *  @return rectangular Block's height
 */
unsigned int Block::GetHeight() const {
  // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
  if (pixels.size() == 0) {  //ADDED!!!!!!!!!!!
    return 0;
  }

  return pixels[0].size();
}

/**
 *  Returns the average color of this Block, for each color channel.
 *  Use truncation for fractional values.
 *
 *  @return RGBAPixel containing the averaged color of all pixels in the Block
 */
RGBAPixel Block::GetAverageColor() const {
  // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
  //return RGBAPixel();
  // this has :sourceimg (PNG), use getPixel(x,y)...
  int totalRed = 0;
  int totalGreen = 0;
  int totalBlue = 0;
  int totalPixels = GetHeight() * GetWidth();
  for (unsigned int x = 0; x <= GetWidth() - 1; x++) {
    for (unsigned int y = 0; y <= GetHeight() - 1; y++) {
      RGBAPixel currPixel = pixels[x][y];
      totalRed = totalRed + currPixel.r;
      totalBlue = totalBlue + currPixel.b;
      totalGreen = totalGreen + currPixel.g;
    }
  }
  int avgRed = totalRed / totalPixels;
  int avgBlue = totalBlue / totalPixels;
  int avgGreen = totalGreen / totalPixels;
  RGBAPixel avgPixel(avgRed, avgGreen, avgBlue);
  return avgPixel;
}

/**
 *  Overwrites the color of every pixel in this Block with the average color of this Block
 *
 *  @post every pixel in the data attribute contains the average color of the entire Block
 */
void Block::MakeAverage() {
  // COMPLETE YOUR IMPLEMENTATION BELOW

  RGBAPixel average = this->GetAverageColor(); //I added this sentence to get correct answer
                                              //Why is it necessary?

  for (unsigned int x = 0; x <= GetWidth() - 1; x++) {
    for (unsigned int y = 0; y <= GetHeight() - 1; y++) {
      RGBAPixel* pixel = &pixels[x][y];
      *pixel = average;
    }
  }
}

/**
 *  Swaps the values of two (or more) color channels in every pixel in this Block
 *
 *  @param order - number in the range of [0,5] to specify which channels get swapped
 *  @pre order is a valid number between 0 and 5
 *  @post every pixel has the values of its color channels swapped according to specified order
 *
 *    new channel value ->  R   G   B
 *              order   |
 *    -----------------------------------
 *                0     |   R   B   G     <- old channel values
 *                1     |   G   R   B
 *                2     |   G   B   R
 *                3     |   B   R   G
 *                4     |   B   G   R
 *                5     |   R   G   B  (no change)
 *
 *  Example: order = 2, a pixel's initial RGB values are (1, 2, 3).
 *           After calling SwapChannels(2), the pixel's new RGB values are (2, 3, 1)
 *           and all pixels in this block will have their channel values swapped similarly.
 */
void Block::SwapChannels(unsigned int order) {
  if (order == 0) {
    for (unsigned int x = 0; x <= GetWidth() - 1; x++) {
      for (unsigned int y = 0; y <= GetHeight() - 1; y++) {
        RGBAPixel* pixel = &pixels[x][y];
        int newGreen = pixel->g;
        int newBlue = pixel->b;
        pixel->g = newBlue;
        pixel->b = newGreen;
      }
    }
  }
  if (order == 1) {
    for (unsigned int x = 0; x <= GetWidth() - 1; x++) {
      for (unsigned int y = 0; y <= GetHeight() - 1; y++) {
        RGBAPixel* pixel = &pixels[x][y];
        int newGreen = pixel->g;
        int newRed = pixel->r;
        pixel->g = newRed;
        pixel->r = newGreen;
      }
    }
  }
  if (order == 2) {
    for (unsigned int x = 0; x <= GetWidth() - 1; x++) {
      for (unsigned int y = 0; y <= GetHeight() - 1; y++) {
        RGBAPixel* pixel = &pixels[x][y];
        int newRed = pixel->r;
        int newGreen = pixel->g;
        int newBlue = pixel->b;
        pixel->g = newBlue;
        pixel->b = newRed;
        pixel->r = newGreen;
      }
    }
  }
  if (order == 3) {
    for (unsigned int x = 0; x <= GetWidth() - 1; x++) {
      for (unsigned int y = 0; y <= GetHeight() - 1; y++) {
        RGBAPixel* pixel = &pixels[x][y];
        int newRed = pixel->r;
        int newGreen = pixel->g;
        int newBlue = pixel->b;
        pixel->b = newGreen;
        pixel->r = newBlue;
        pixel->g = newRed;
      }
    }
  }
  if (order == 4) {
    for (unsigned int x = 0; x <= GetWidth() - 1; x++) {
      for (unsigned int y = 0; y <= GetHeight() - 1; y++) {
        RGBAPixel* pixel = &pixels[x][y];
        int newRed = pixel->r;
        int newBlue = pixel->b;
        pixel->b = newRed;
        pixel->r = newBlue;
      }
    }
  }

  if (order == 5) {
    return;
  }

}