#include "ShootingTarget.h"
#include <Windows.h>
#include <d2d1_3.h>
#include "GlobalValues.h"
#include "PaintAccessories.h"

using D2D1::RadialGradientBrushProperties;
using D2D1::Point2F;
using D2D1::Ellipse;

Baloon::Baloon(FLOAT x, FLOAT y, GlobalValues *g) {
	this->center = Point2F(x, y);
	this->radiusX = 30;
	this->radiusY = 40;
}

void Baloon::render(GlobalValues *g, PaintAccessories *p) {
	g->d2d_render_target->CreateGradientStopCollection(p->rad_stops_data, p->NUM_RAD_STOPS, &p->rad_stops);
	if (p->rad_stops) {
		g->d2d_render_target->CreateRadialGradientBrush(RadialGradientBrushProperties(center,
			Point2F(0, 0), 70, 70), p->rad_stops, &p->rad_brush);
		g->d2d_render_target->FillEllipse(Ellipse(center, radiusX, radiusY), p->rad_brush);
		center.y -= 1;
	}
}

ShootingTarget::ShootingTarget(FLOAT x, FLOAT y, GlobalValues* g, bool going_up) {
	this->center = Point2F(x, y);
	this->goingUp = going_up;
	this->radiusX = 30;
	this->radiusY = 60;
	this->limitY = g->height - this->radiusY;
}

void ShootingTarget::render(GlobalValues* g, PaintAccessories* p) {
	FLOAT ellipse_size_diffrence_x = radiusX / (number_of_colors * 2);
	FLOAT ellipse_size_diffrence_y = radiusY / (number_of_colors * 2);
	FLOAT currentRadiusX = radiusX;
	FLOAT currentRadiusY = radiusY;
	g->d2d_render_target->FillEllipse(Ellipse(center, currentRadiusX + 1, currentRadiusY + 1), p->black_brush);
	for (size_t i = 0; i < number_of_colors; i++) {
		g->d2d_render_target->FillEllipse(Ellipse(center, currentRadiusX, currentRadiusY), p->target_brush[i]);
		currentRadiusX -= (ellipse_size_diffrence_x * 2);
		currentRadiusY -= (ellipse_size_diffrence_y * 2);
	}
}

void ShootingRange::addTarget(FLOAT x, FLOAT y, GlobalValues* g, bool goingUp) {
	this->targets.push_back(ShootingTarget(x, y, g, goingUp));
}

void ShootingRange::renderTargets(GlobalValues* g, PaintAccessories* p) {
	for (auto& target : this->targets) {
		target.render(g, p);
	}
}

bool Baloon::isOutsideTheScreen() {
	if (this->center.y + this->radiusY <= 0)
		return true;
	return false;
}

void ShootingRange::renderBaloon(GlobalValues* g, PaintAccessories* p) {
	if (!baloon) {
		INT width = std::rand() % ((INT)g->width - 250) + 200;
		this->baloon = new Baloon(width, g->height - 50, g);
	}
	if (this->baloon->isOutsideTheScreen()) {
		delete this->baloon;
		this->baloon = nullptr;
	}
	else {
		this->baloon->render(g, p);
	}
}