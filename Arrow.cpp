#include "Arrow.h"
#include "PaintAccessories.h"
#include "GlobalValues.h"
#include <math.h>
#include <d2d1_3.h>
#include <utility>

using D2D1::Point2F;

void Arrow::paint(PaintAccessories *p, GlobalValues *g) {
	g->d2d_render_target->DrawLine(this->start, this->end, p->brush, 1.0f);
}

void applyRatio(FLOAT &x, FLOAT ratio, GlobalValues *g, bool reversed = false) {
	if (reversed) {
		x *= ratio;
		x *= -1;
	}
	else {
		x *= ratio;
	}
}

void Arrow::calculatePosition(FLOAT mouse_x, FLOAT mouse_y, GlobalValues* g) {
	if (this->isFlying) {
		FLOAT heightModifier = this->reachedTop ? this->velocity : -1 * this->velocity;
		FLOAT widthModifier = this->velocity;
		applyRatio(widthModifier, tiltRatioX, g);
		applyRatio(heightModifier, tiltRatioY, g, true);
		this->start = Point2F(this->start.x + widthModifier, this->start.y + heightModifier);
		this->end = Point2F(this->end.x + widthModifier, this->end.y + heightModifier);
		velocity += reachedTop ? 0.01 : -0.02;
		if (velocity <= 0.6 && !this->reachedTop) {
			if (this->start.y < this->end.y) {
				velocity += 0.3;
			}
			else {
				this->reachedTop = true;
				std::swap(this->start.y, this->end.y);
			}
		}
	}
	else if (this->isDrawing) {
		velocity += 0.04;
	}
	else {
		if (mouse_x == -1)
			return;
		FLOAT distance = sqrt(pow((mouse_x - g->archer_center_x), 2) + pow((mouse_y - g->archer_center_y), 2));
		FLOAT ratioStart = distance / g->arrow_distance_from_archer_center;
		FLOAT ratioEnd = distance / (g->arrow_distance_from_archer_center + g->arrow_length);
		FLOAT start_x = (mouse_x - g->archer_center_x) / ratioStart;
		FLOAT start_y = (mouse_y - g->archer_center_y) / ratioStart;
		FLOAT end_x = (mouse_x - g->archer_center_x) / ratioEnd;
		FLOAT end_y = (mouse_y - g->archer_center_y) / ratioEnd;
		this->start = Point2F(start_x + g->archer_center_x, start_y + g->archer_center_y);
		this->end = Point2F(end_x + g->archer_center_x, end_y + g->archer_center_y);
	}
}

Arrow::Arrow(D2D1_POINT_2F start, D2D1_POINT_2F end) {
	this->start = start;
	this->end = end;
	this->isFlying = false;
}

Arrow::Arrow(GlobalValues* g) {
	this->start = Point2F(g->archer_center_x + g->arrow_distance_from_archer_center, g->archer_center_y);
	this->end = Point2F(g->archer_center_x + g->arrow_distance_from_archer_center + g->arrow_length, g->archer_center_y);
	this->isFlying = false;
}

void Arrow::onKeyUp() {
	if (this->isDrawing) {
		this->isFlying = true;
	}
}

void Arrow::onKeyDown(GlobalValues *g) {
	if (!this->isDrawing) {
		this->isDrawing = true;
		FLOAT x = this->end.x - g->archer_center_x;
		FLOAT y = this->end.y - g->archer_center_y;
		FLOAT perfectRatio = sqrt(2) * (g->arrow_distance_from_archer_center + g->arrow_length);
		this->tiltRatioX = x / perfectRatio;
		this->tiltRatioY = y / perfectRatio;
	}
}

bool Arrow::checkIfLanded(GlobalValues* g) {
	return (start.x >= g->width || end.y >= g->ground_level);
}