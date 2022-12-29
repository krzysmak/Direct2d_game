#include "Arrow.h"
#include "PaintAccessories.h"
#include "GlobalValues.h"

void Arrow::paint(PaintAccessories *p, GlobalValues *g) {
	g->d2d_render_target->DrawLine(this->start, this->end, p->brush, 1.0f);
}

void Arrow::calculatePosition() {
	this->start = D2D1_POINT_2F(this->start.x + 1.2, this->path->calculateY(this->start.x + 1.2));
	this->end = D2D1_POINT_2F(this->end.x + 1.2, this->path->calculateY(this->end.x + 1.2));
}

Arrow::Arrow(D2D1_POINT_2F start, D2D1_POINT_2F end, ArrowPath* path) {
	this->start = start;
	this->end = end;
	this->path = path;
}