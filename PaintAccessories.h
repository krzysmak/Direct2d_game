#ifndef PAINT_ACCESSORIES
#define PAINT_ACCESSORIES

#include <windows.h>
#include <d2d1_3.h>
#include "GlobalValues.h"
#include "PaintAccessories.h"

class PaintAccessories {
public:
    D2D1_COLOR_F const clear_color = { .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f };
    FLOAT const brush_width = 3.0f;
    ID2D1SolidColorBrush* brush;
    ID2D1SolidColorBrush* black_brush;
    const static size_t number_of_colors_target = 5;
    ID2D1SolidColorBrush* target_brush[number_of_colors_target];
    ID2D1RadialGradientBrush* rad_brush = nullptr;
    static const size_t NUM_RAD_STOPS = 5;
    D2D1_GRADIENT_STOP rad_stops_data[NUM_RAD_STOPS];
    ID2D1GradientStopCollection* rad_stops = nullptr;
    D2D1_COLOR_F create_color(FLOAT r, FLOAT g, FLOAT b, FLOAT a);
    void initAccessories(GlobalValues *g);
};

#endif // PAINT_ACCESSORIES
