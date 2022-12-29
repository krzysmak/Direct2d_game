#ifndef PAINT_ACCESSORIES
#define PAINT_ACCESSORIES

#include <windows.h>
#include <d2d1_3.h>
#include "GlobalValues.h"

class PaintAccessories {
public:
    D2D1_COLOR_F const clear_color = { .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };
    D2D1_COLOR_F const black_color = { .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f };
    FLOAT const brush_width = 3.0f;
    ID2D1SolidColorBrush* brush;

    D2D1_COLOR_F create_color(FLOAT r, FLOAT g, FLOAT b, FLOAT a);
    void initAccessories(GlobalValues *g);
};

#endif // PAINT_ACCESSORIES
