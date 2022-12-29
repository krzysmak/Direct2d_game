#include "PaintAccessories.h"
#include "GlobalValues.h"

D2D1_COLOR_F PaintAccessories::create_color(FLOAT r, FLOAT g, FLOAT b, FLOAT a) {
	D2D1_COLOR_F color = { .r = r, .g = g, .b = b, .a = a };
	return color;
}

void PaintAccessories::initAccessories(GlobalValues *g) {
	g->d2d_render_target->CreateSolidColorBrush(this->black_color, &this->brush);
}