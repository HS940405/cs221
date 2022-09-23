#include "rainbowColorPicker.h"
#include "cs221util/RGB_HSL.h"
#include <math.h>

using std::pair;
using std::map;

RainbowColorPicker::RainbowColorPicker(long double freq_) : iter(0), freq(freq_)
{
}

RGBAPixel RainbowColorPicker::operator()(PixelPoint p)
{
    PNGmap::iterator stored = prev.find(pair<int, int>(p.x, p.y));
    if (stored == prev.end()) {
        RGBAPixel next = NextColor();
        prev[pair<int, int>(p.x, p.y)] = next;
        return next;
    } else
        return stored->second;
}

// http://www.krazydad.com/makecolors.php
RGBAPixel RainbowColorPicker::NextColor()
{
    hslaColor ret;
    ret.a = 1.0;
    if (iter * freq > 1) iter = 0;
    ret.h = (360 * iter * freq);
    ret.s = 1.0;
    ret.l = 0.5;
    iter++;
    // convert to RGBA and return
    rgbaColor rgb = hsl2rgb(ret);
    RGBAPixel ret_rgb(rgb.r, rgb.g, rgb.b);
    return ret_rgb;
}
