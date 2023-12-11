#include <stdio.h>
#include "RGB-HSV.h"


void RGBtoHSV(int r, int g, int b, HSVColor* hsv) {
    float r_ = r / 255.0f;
    float g_ = g / 255.0f;
    float b_ = b / 255.0f;
    
    float max = (r_ > g_) ? ((r_ > b_) ? r_ : b_) : ((g_ > b_) ? g_ : b_);
    float min = (r_ < g_) ? ((r_ < b_) ? r_ : b_) : ((g_ < b_) ? g_ : b_);
    float delta = max - min;
    
    // Calculate Hue
    if (delta == 0) {
        hsv->h = 0;
    } else if (max == r_) {
        hsv->h = 60 * ((g_ - b_) / delta);
    } else if (max == g_) {
        hsv->h = 60 * ((b_ - r_) / delta) + 120;
    } else {
        hsv->h = 60 * ((r_ - g_) / delta) + 240;
    }
    
    if (hsv->h < 0) {
        hsv->h += 360;
    }
    
    // Calculate Saturation
    if (max == 0) {
        hsv->s = 0;
    } else {
        hsv->s = (delta / max) * 100;
    }
    
    // Calculate Value
    hsv->v = max * 100;
}

