/**
 *  @file stats.cpp
 *  @description implementation of a stats class for rapid calculation of color averages
 *   and total color differences in CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "stats.h"

 /**
  *  Computes/retrieves the sum of a single color channel in a defined rectangular region
  *  @pre channel is a valid channel identifier
  *  @pre upper, left, lower, and right are valid image coordinates
  *  @param channel - one of 'r', 'g', or 'b'
  *  @param upper - y-coordinate of the upper edge of the rectangular region
  *  @param left - x-coordinate of the left side of the rectangular region
  *  @param lower - y-coordinate of the lower edge of the rectangular region
  *  @param right - x-coordinate of the right side of the rectangular region
  *  @return the sum of the appropriate color channel values in the defined rectangular area
  */
unsigned long Stats::GetColorSum(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
 

  switch (channel)
  {
    case 'r':
      if (left == 0 && upper == 0) {
        return sumR[right][lower];
      } else if (left == 0) {
        return sumR[right][lower] - sumR[right][upper - 1];
      } else if (upper == 0) {
        return sumR[right][lower] - sumR[left - 1][lower];
      } else {
        return sumR[right][lower] - sumR[right][upper - 1] - sumR[left - 1][lower] + sumR[left - 1][upper - 1];
      }
    case 'g':
      if (left == 0 && upper == 0) {
        return sumG[right][lower];
      } else if (left == 0) {
        return sumG[right][lower] - sumG[right][upper - 1];
      } else if (upper == 0) {
        return sumG[right][lower] - sumG[left - 1][lower];
      } else {
        return sumG[right][lower] - sumG[right][upper - 1] - sumG[left - 1][lower] + sumG[left - 1][upper - 1];
      }
    case 'b':
      if (left == 0 && upper == 0) {
        return sumB[right][lower];
      } else if (left == 0) {
        return sumB[right][lower] - sumB[right][upper - 1];
      } else if (upper == 0) {
        return sumB[right][lower] - sumB[left - 1][lower];
      } else {
        return sumB[right][lower] - sumB[right][upper - 1] - sumB[left - 1][lower] + sumB[left - 1][upper - 1];
      }
  }
}

/**
 *  Computes/retrieves the sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSum(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  if (left == 0 && upper == 0) {
    return sumA[right][lower]; 
  } else if (left == 0) {
    return (sumA[right][lower] - sumA[right][upper - 1]); 
  } else if (upper == 0) {
    return (sumA[right][lower] - sumA[left - 1][lower]);
  } else {
    return (sumA[right][lower] - sumA[right][upper - 1] - sumA[left - 1][lower] + sumA[left - 1][upper - 1]);
  }
}

/**
 *  Computes/retrieves the squared sum of a single color channel in a defined rectangular region
 *  @pre channel is a valid channel identifier
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param channel - one of 'r', 'g', or 'b'
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the appropriate color channel values in the defined rectangular area
 */
unsigned long Stats::GetColorSumSq(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  switch (channel)
  {
    case 'r':
      if (left == 0 && upper == 0) {
        return sumSqR[right][lower];
      } else if (left == 0) {
        return sumSqR[right][lower] - sumSqR[right][upper - 1];
      } else if (upper == 0) {
        return sumSqR[right][lower] - sumSqR[left - 1][lower];
      } else {
        return sumSqR[right][lower] - sumSqR[right][upper - 1] - sumSqR[left - 1][lower] + sumSqR[left - 1][upper - 1];
      }
    case 'g':
      if (left == 0 && upper == 0) {
        return sumSqG[right][lower];
      } else if (left == 0) {
        return sumSqG[right][lower] - sumSqG[right][upper - 1];
      } else if (upper == 0) {
        return sumSqG[right][lower] - sumSqG[left - 1][lower];
      } else {
        return sumSqG[right][lower] - sumSqG[right][upper - 1] - sumSqG[left - 1][lower] + sumSqG[left - 1][upper - 1];
      }
    case 'b':
      if (left == 0 && upper == 0) {
        return sumSqB[right][lower];
      } else if (left == 0) {
        return sumSqB[right][lower] - sumSqB[right][upper - 1];
      } else if (upper == 0) {
        return sumSqB[right][lower] - sumSqB[left - 1][lower];
      } else {
        return sumSqB[right][lower] - sumSqB[right][upper - 1] - sumSqB[left - 1][lower] + sumSqB[left - 1][upper - 1];
      }
  }
}

/**
 *  Computes/retrieves the squared sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSumSq(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  if (left == 0 && upper == 0) {
    return sumSqA[right][lower];
  } else if (left == 0) {
    return (sumSqA[right][lower] - sumSqA[right][upper - 1]);
  } else if (upper == 0) {
    return (sumSqA[right][lower] - sumSqA[left - 1][lower]);
  } else {
    return (sumSqA[right][lower] - sumSqA[right][upper - 1] - sumSqA[left - 1][lower] + sumSqA[left - 1][upper - 1]);
  }
}

/**
 *  Simple function to compute the number of pixels in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the area of the defined rectangular area, in pixels
 */
unsigned int Stats::GetRectangleArea(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  return (right - left + 1) * (lower - upper + 1);
}

/**
 *  Parameterized constructor
 *  Builds the channel sum and squared sum vectors from the supplied input image.
 *  Each channel sum vector's entry (x,y) will contain the sum of their respective
 *  color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *  Likewise, each channel squared sum vector's entry (x,y) will contain the squared sum of their
 *  respective color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *
 *  ***DON'T FORGET TO PRE-MULTIPLY THE ALPHA CHANNEL***
 * 
 *  @param img - input image from which the channel sum vectors will be populated
 */
Stats::Stats(const PNG& img) {

  for (unsigned int x = 0; x < img.width(); x++) {

    vector<unsigned long> xR;
    vector<unsigned long> xG;
    vector<unsigned long> xB;
    vector<double> xA;

    vector<unsigned long> sqXR;
    vector<unsigned long> sqXG;
    vector<unsigned long> sqXB;
    vector<double> sqXA;

    unsigned long currSumR = 0;
    unsigned long currSumG = 0;
    unsigned long currSumB = 0;
    double currSumA = 0;

    unsigned long currSumSqR = 0;
    unsigned long currSumSqG = 0;
    unsigned long currSumSqB = 0;
    double currSumSqA = 0;

    for (unsigned int y = 0; y < img.height(); y++) {
      RGBAPixel* pixel = img.getPixel(x, y);

        currSumR += pixel->r;
        currSumG += pixel->g;
        currSumB += pixel->b;
        currSumA += (pixel->a * 255.0);

        currSumSqR += (pixel->r) * (pixel->r);
        currSumSqG += (pixel->g) * (pixel->g);
        currSumSqB += (pixel->b) * (pixel->b);
        currSumSqA += ((pixel->a) * (pixel->a) * 255.0 * 255.0);

      if (x == 0) {
        
        xR.push_back(currSumR);
        xG.push_back(currSumG);
        xB.push_back(currSumB);
        xA.push_back(currSumA);

        sqXR.push_back(currSumSqR);
        sqXG.push_back(currSumSqG);
        sqXB.push_back(currSumSqB);
        sqXA.push_back(currSumSqA);

      } else {

        xR.push_back(currSumR + sumR[x-1][y]);
        xG.push_back(currSumG + sumG[x-1][y]);
        xB.push_back(currSumB + sumB[x-1][y]);
        xA.push_back(currSumA + sumA[x-1][y]);

        sqXR.push_back(currSumSqR + sumSqR[x-1][y]);
        sqXG.push_back(currSumSqG + sumSqG[x-1][y]);
        sqXB.push_back(currSumSqB + sumSqB[x-1][y]);
        sqXA.push_back(currSumSqA + sumSqA[x-1][y]);
      }
    }

    sumR.push_back(xR);
    sumG.push_back(xG);
    sumB.push_back(xB);
    sumA.push_back(xA);

    sumSqR.push_back(sqXR);
    sumSqG.push_back(sqXG);
    sumSqB.push_back(sqXB);
    sumSqA.push_back(sqXA);
  }

}

/**
 *  Computes/retrieves the average color of all pixels contained in the rectangle
 *  bounded by upper, left, lower, and right. Fractional values should be
 *  truncated/rounded down for assignment into integer variables.
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return pixel containing the average color of the pixels in the defined rectangle
 */
RGBAPixel Stats::GetAvg(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {

  unsigned int area = GetRectangleArea(upper, left, lower, right);

  int averageR = (int) round((GetColorSum('r', upper, left, lower, right) / (unsigned long) area));
  int averageG = (int) round((GetColorSum('g', upper, left, lower, right) / (unsigned long) area));
  int averageB = (int) round((GetColorSum('b', upper, left, lower, right) / (unsigned long) area));
  double averageA = GetAlphaSum(upper, left, lower, right) / ((double)area) / 255;  // CHANGED by irene: divide by 255

  return RGBAPixel(averageR, averageG, averageB, averageA); // REPLACE THIS STUB
}

/**
 *  Computes the total sum squared difference from the mean, for the specified rectangle.
 *  Each channel's sum squared difference is computed separately, and then added to form the total.
 *
 *  Note that using the GetAvg function in computing the sum squared difference will result in
 *  accumulation of error especially with larger rectangles.
 *  You should use more precise computation of the average color for this function's intermediate steps.
 * 
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return total sum of squared deviations from the mean, over all color channels.
 */
double Stats::GetSumSqDev(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {

  int area = GetRectangleArea(upper,left,lower,right);

  double sumSqR = GetColorSumSq('r',upper,left,lower,right);
  double sumSqG = GetColorSumSq('g',upper,left,lower,right);
  double sumSqB = GetColorSumSq('b',upper,left,lower,right);
  double sumSqA = GetAlphaSumSq(upper,left,lower,right);

  double squaredSumsR = GetColorSum('r', upper,left,lower,right) * GetColorSum('r', upper,left,lower,right);
  double squaredSumsG = GetColorSum('g', upper,left,lower,right) * GetColorSum('g', upper,left,lower,right);
  double squaredSumsB = GetColorSum('b', upper,left,lower,right) * GetColorSum('b', upper,left,lower,right);
  double squaredSumsA = GetAlphaSum(upper,left,lower,right) * GetAlphaSum (upper,left,lower,right);

  double sumsqdevR = sumSqR - (squaredSumsR / area);
  double sumsqdevG = sumSqG - (squaredSumsG / area);
  double sumsqdevB = sumSqB - (squaredSumsB / area);
  double sumsqdevA = sumSqA - (squaredSumsA / area);

  return sumsqdevR + sumsqdevG + sumsqdevB + sumsqdevA;

}