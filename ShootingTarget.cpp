#include "ShootingTarget.h"
#include <Windows.h>
#include <d2d1_3.h>
#include "GlobalValues.h"
#include "PaintAccessories.h"

using D2D1::RadialGradientBrushProperties;
using D2D1::Point2F;
using D2D1::Ellipse;

ShootingTarget::ShootingTarget(FLOAT x, FLOAT y, GlobalValues *g, bool going_up) {
	this->center = Point2F(x, y);
	this->goingUp = goingUp;
	this->radiusX = 30;
	this->radiusY = 60;
	this->limitY = g->height - this->radiusY;
}

void ShootingTarget::render(GlobalValues *g, PaintAccessories *p) {
	g->d2d_render_target->CreateGradientStopCollection(p->rad_stops_data, p->NUM_RAD_STOPS, &p->rad_stops);
	if (p->rad_stops) {
		g->d2d_render_target->CreateRadialGradientBrush(RadialGradientBrushProperties(center,
			Point2F(0, 0), 70, 70), p->rad_stops, &p->rad_brush);
	}
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(center.x, center.y), radiusX, radiusY);
	g->d2d_render_target->FillEllipse(Ellipse(center, radiusX, radiusY), p->rad_brush);
}

void ShootingRange::addTarget(FLOAT x, FLOAT y, GlobalValues* g, bool goingUp) {
	this->targets.push_back(ShootingTarget(x, y, g, goingUp));
}

void ShootingRange::renderTargets(GlobalValues* g, PaintAccessories* p) {
	for (auto& target : this->targets) {
		target.render(g, p);
	}
}