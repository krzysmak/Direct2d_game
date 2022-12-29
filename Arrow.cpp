#include "Arrow.h"
#include "PaintAccessories.h"
#include "GlobalValues.h"
#include <math.h>
#include <d2d1_3.h>

using D2D1::Point2F;

void Arrow::paint(PaintAccessories *p, GlobalValues *g) {
	g->d2d_render_target->DrawLine(this->start, this->end, p->brush, 1.0f);
}

void Arrow::calculatePosition(FLOAT mouse_x, FLOAT mouse_y, GlobalValues* g) {
	if (this->isFlying) {

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