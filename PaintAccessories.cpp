#include "PaintAccessories.h"
#include "GlobalValues.h"
#include <d2d1_3.h>

using D2D1::ColorF;

D2D1_COLOR_F PaintAccessories::create_color(FLOAT r, FLOAT g, FLOAT b, FLOAT a) {
	D2D1_COLOR_F color = { .r = r, .g = g, .b = b, .a = a };
	return color;
}

void PaintAccessories::initAccessories(GlobalValues *g) {
	g->d2d_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &this->brush);
    rad_stops_data[0] =
    { .position = 0.05f, .color = ColorF(ColorF::White, 1.0f) };
    rad_stops_data[1] =
    { .position = 0.15f, .color = ColorF(ColorF::LightYellow, 1.0f) };
    rad_stops_data[2] =
    { .position = 0.7f, .color = ColorF(ColorF::Yellow, 1.0f) };
    rad_stops_data[3] =
    { .position = 0.8f, .color = ColorF(ColorF::Yellow, 1.0f) };
    rad_stops_data[4] =
    { .position = 1.0f, .color = ColorF(ColorF::LightGoldenrodYellow, 1.0f) };
    g->d2d_render_target->CreateGradientStopCollection(rad_stops_data, NUM_RAD_STOPS, &rad_stops);
    g->d2d_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &this->yellow_brush);
    g->d2d_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &this->black_brush);
    g->d2d_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &this->target_brush[4]);
    g->d2d_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &this->target_brush[3]);
    g->d2d_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightBlue, 1.0f), &this->target_brush[2]);
    g->d2d_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &this->target_brush[1]);
    g->d2d_render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &this->target_brush[0]);
    g->d2d_render_target->CreateGradientStopCollection(rad_stops_data, NUM_RAD_STOPS, &rad_stops);
}

void PaintAccessories::destroyValues() {
    if (black_brush) black_brush->Release();
    if (brush) brush->Release();
    if (yellow_brush) yellow_brush->Release();
    if (rad_stops) rad_stops->Release();
}