#include "ShootingTarget.h"
#include <Windows.h>
#include <d2d1_3.h>
#include "GlobalValues.h"
#include "PaintAccessories.h"
#define _USE_MATH_DEFINES
#include <math.h>

using D2D1::RadialGradientBrushProperties;
using D2D1::Point2F;
using D2D1::Ellipse;

Baloon::Baloon(FLOAT x, FLOAT y, GlobalValues *g) {
	this->center = Point2F(x, y);
	this->radiusX = 30;
	this->radiusY = 40;
}

void Baloon::render(GlobalValues *g, PaintAccessories *p) {
	if (this->ticks_popped == 0) {
		if (p->rad_stops) {
			g->d2d_render_target->CreateRadialGradientBrush(RadialGradientBrushProperties(center,
				Point2F(0, 0), 70, 70), p->rad_stops, &p->rad_brush);
			g->d2d_render_target->FillEllipse(Ellipse(center, radiusX, radiusY), p->rad_brush);
			center.y -= 2;
			p->rad_brush->Release();
		}
	}
	else {
		this->ticks_popped--;
		if (this->ticks_popped != 0)
			this->pop(g, p);
		else
			this->ticks_popped--;
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
	limitY = g->height - radiusY;
	if (goingUp) {
		center.y -= 1;
	}
	else {
		center.y += 1;
	}
	if (center.y - radiusY <= 0) {
		goingUp = false;
	}
	if (center.y + radiusY >= limitY) {
		goingUp = true;
	}
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

void ShootingRange::checkHits(FLOAT arrowX, FLOAT arrowY, GlobalValues* g, PaintAccessories* p) {
	for (auto& target : this->targets) {
		target.checkHit(arrowX, arrowY, g, p);
	}
	if (this->baloon) {
		if (this->baloon->ticks_popped == 0)
			this->baloon->checkHit(arrowX, arrowY, g, p);
		else if (this->baloon->ticks_popped < 0) {
			delete this->baloon;
			this->baloon = nullptr;
		}
	}
}

bool isInsideEllipse(FLOAT ellipseCenterX, FLOAT ellipseCenterY, FLOAT radiusX, FLOAT radiusY, FLOAT x, FLOAT y) {
	FLOAT dx = x - ellipseCenterX;
	FLOAT dy = y - ellipseCenterY;
	FLOAT distanceSquared = dx * dx / (radiusX * radiusX) + dy * dy / (radiusY * radiusY);
	return distanceSquared <= 1;
}

void Baloon::checkHit(FLOAT arrowX, FLOAT arrowY, GlobalValues* g, PaintAccessories* p) {
	if (isInsideEllipse(this->center.x, this->center.y, this->radiusX, this->radiusY, arrowX, arrowY)) {
		this->ticks_popped = g->baloon_pop_animation_length;
		this->pop(g, p);
	}
}

void ShootingTarget::checkHit(FLOAT arrowX, FLOAT arrowY, GlobalValues* g, PaintAccessories* p) {
	if (isInsideEllipse(this->center.x, this->center.y, this->radiusX, this->radiusY, arrowX, arrowY)) {
		FLOAT targetBottom = this->center.y + this->radiusY;
		FLOAT arrowRelativeY = targetBottom - arrowY;
		FLOAT arrowHitYPercent = arrowRelativeY / (2 * this->radiusY);
		this->pop(g, p, arrowHitYPercent);
	}
}

void DrawScrap(GlobalValues *g, ID2D1Brush* brush, float x, float y, float size) {
	static const D2D1_POINT_2F points[3] = {
	  D2D1::Point2F(-size / 2.0f, -size / 2.0f),
	  D2D1::Point2F(size / 2.0f, -size / 2.0f),
	  D2D1::Point2F(0.0f, size / 2.0f),
	};
	ID2D1PathGeometry* geometry = nullptr;
	g->d2d_factory->CreatePathGeometry(&geometry);
	ID2D1GeometrySink* sink;
	geometry->Open(&sink);
	sink->BeginFigure(points[0], D2D1_FIGURE_BEGIN_FILLED);
	sink->AddLines(points + 1, 2);
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();
	D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Translation(x, y);
	D2D1::Matrix3x2F original_transform;
	g->d2d_render_target->GetTransform(&original_transform);
	transform.SetProduct(transform, original_transform);
	g->d2d_render_target->SetTransform(transform);
	g->d2d_render_target->DrawGeometry(geometry, brush, 3.0f);
	g->d2d_render_target->SetTransform(original_transform);
	sink->Release();
	geometry->Release();
}

void Baloon::pop(GlobalValues *g, PaintAccessories *p) {
	g->score += 1;
	size_t number_of_scraps = 15;
	float t = (float)(this->ticks_popped) / (float)g->baloon_pop_animation_length;
	float radius = (this->radiusY) * (1.0f - t);
	FLOAT size = 2.0f * radius / number_of_scraps;
	size += 1;
	for (int j = 0; j < number_of_scraps; j++) {
		float angle = 2.0f * M_PI * (float)j / (float)number_of_scraps;
		float scrap_x = this->center.x + radius * cos(angle);
		float scrap_y = this->center.y + radius * sin(angle);
		DrawScrap(g, p->yellow_brush, scrap_x, scrap_y, size);
	}
}

void ShootingTarget::pop(GlobalValues* g, PaintAccessories* p, FLOAT arrowHitYPercent) {
	g->minigame = true;
	g->arrowHitYPercent = arrowHitYPercent;
}