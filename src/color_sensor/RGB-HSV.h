typedef struct {
    float h; // Hue [0, 360]
    float s; // Saturation [0, 100]
    float v; // Value [0, 100]
} HSVColor;

void RGBtoHSV(int r, int g, int b, HSVColor* hsv);