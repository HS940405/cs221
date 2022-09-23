/**
 * @file block.h
 * @author CPSC 221
 * 
 * Defines a rectangular image portion block for CPSC 221 PA1
 * 
 * DO NOT MODIFY THIS FILE
 * THIS FILE WILL NOT BE SUBMITTED FOR GRADING
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"

#include <vector>

using namespace cs221util;
using namespace std;

class Block {
  public:

    /** 2D container for pixel data
     *  Be aware that a newly declared vector has a size of 0
     *  Also be aware that your choice of row-major vs column-major order
     *  affects how you will perform your horizontal or vertical flips.
     */
    vector<vector<RGBAPixel>> pixels;

  public:

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
    void Build(unsigned int w, unsigned int h, unsigned int upper, unsigned int left, const PNG& sourceimg);

    /**
     *  Writes the pixel color data into the target PNG, starting from (left, upper)
     *
     *  @pre upper, left are valid image indices
     *  @pre the rectangular region beginning at (left, upper) can completely receive all of the data attribute's color
     *  @post target PNG's subimage region has been filled with data attribute's pixel data
     */
    void Render(unsigned int upper, unsigned int left, PNG& targetimg) const;

    /**
     *  Mirror this block's pixel data horizontally (along a vertical axis)
     * 
     *  @post pixel data in this Block has been mirrored horizontally
     */
    void FlipHorizontal();

    /**
     *  Mirror this block's pixel data vertically (along a horizontal axis)
     *
     *  @post pixel data in this Block has been mirrored vertically
     */
    void FlipVertical();

    /**
     *  Returns the width (in pixels) of this Block
     * 
     *  @return rectangular Block's width
     */
    unsigned int GetWidth() const;

    /**
     *  Returns the height (in pixels) of this Block
     *
     *  @return rectangular Block's height
     */
    unsigned int GetHeight() const;

    /**
     *  Returns the average color of this Block, for each color channel.
     *  Use truncation for fractional values.
     * 
     *  @return RGBAPixel containing the averaged color of all pixels in the Block
     */
    RGBAPixel GetAverageColor() const;

    /**
     *  Overwrites the color of every pixel in this Block with the average color of this Block
     * 
     *  @post every pixel in the data attribute contains the average color of the entire Block
     */
    void MakeAverage();

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
    void SwapChannels(unsigned int order);
};

#endif
