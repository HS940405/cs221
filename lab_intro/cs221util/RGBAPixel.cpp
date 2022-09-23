#include "RGBAPixel.h"

namespace cs221util {
    RGBAPixel::RGBAPixel() {
        r = 255;
        g = 255;
        b = 255;
        a = 1;
    }
    
    RGBAPixel::RGBAPixel(unsigned char rVal, unsigned char gVal, unsigned char bVal) {
        r = rVal;
        g = gVal;
        b = bVal;
        a = 1;
    }
    
    RGBAPixel::RGBAPixel(unsigned char rVal, unsigned char gVal, unsigned char bVal, double aVal) {
        r = rVal;
        g = gVal;
        b = bVal;
        a = aVal;
    }
}