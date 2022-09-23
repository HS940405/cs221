/*
* File:        testStats.cpp
*/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"

#include "stats.h"

using namespace std;

TEST_CASE("Stats::constructor") {
  cout << "Testing Stats Constructor..." << endl;

  PNG image;
  image.readFromFile("originals/kkkk-kmnn-960x540.png");

  unsigned long expectedR = 0;
  unsigned long expectedG = 0;
  unsigned long expectedB = 0;
  double expectedA = 0;

  for (unsigned int x = 0; x <= image.width(); x++) {
      for (unsigned int y = 0; y <= image.height(); y++) {
          RGBAPixel pix = image.getPixel(x, y);
          expectedR += pix.r;
          expectedG += pix.g;
          expectedB += pix.b;
          expectedA += pix.a;
      }
  }

  Stats stat = Stats(&image);
  unsigned long resultR = stat.sumR[image.width()][image.height()];
  unsigned long resultG = stat.sumG[image.width()][image.height()];
  unsigned long resultB = stat.sumB[image.width()][image.height()];
  double resultA = stat.sumA[image.width()][image.height()] / 255.0;

  REQUIRE(expectedA == resultA);
  REQUIRE(expectedG == resultG);
  REQUIRE(expectedB == resultB);
  REQUIRE(expectedR == resultR);

