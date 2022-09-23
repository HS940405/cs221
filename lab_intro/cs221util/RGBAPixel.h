#ifndef CS221UTIL_RGBAPixel_H
#define CS221UTIL_RGBAPixel_H

using namespace std;

namespace cs221util {
    class RGBAPixel {
        public:
        unsigned char r;
        unsigned char g;
        unsigned char b;
        double a;

        //default constructor
        RGBAPixel();

        //set r, g, b with full opacity
        RGBAPixel(unsigned char rVal, unsigned char gVal, unsigned char bVal);

        //set r, g, b, a
        RGBAPixel(unsigned char rVal, unsigned char gVal, unsigned char bVal, double aVal);
    };
}

#endif