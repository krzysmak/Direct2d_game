#include "PaintAccessories.h"
#include "GlobalValues.h"
#include <d2d1_3.h>

using D2D1::ColorF;

D2D1_COLOR_F PaintAccessories::create_color(FLOAT r, FLOAT g, FLOAT b, FLOAT a) {
	D2D1_COLOR_F color = { .r = r, .g = g, .b = b, .a = a };
	return color;
}

void PaintAccessories::initAccessories(GlobalValues *g) {
	g->d2d_render_target->CreateSolidColorBrush(this->black_color, &this->brush);
    rad_stops_data[0] =
    { .position = 0.2f, .color = ColorF(1.0f, 1.0f, 1.0f, 1.0f) };
    rad_stops_data[1] =
    { .position = 0.4f, .color = ColorF(0.0f, 0.0f, 0.0f, 1.0f) };
    rad_stops_data[2] =
    { .position = 0.6f, .color = ColorF(0.0f, 1.0f, 1.0f, 1.0f) };
    rad_stops_data[3] =
    { .position = 0.8f, .color = ColorF(1.0f, 0.0f, 0.0f, 1.0f) };
    rad_stops_data[4] =
    { .position = 1.0f, .color = ColorF(1.0f, 1.0f, 0.0f, 1.0f) };
    g->d2d_render_target->CreateGradientStopCollection(rad_stops_data, NUM_RAD_STOPS, &rad_stops);
}