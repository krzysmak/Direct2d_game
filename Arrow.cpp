#include "Arrow.h"
#include "PaintAccessories.h"
#include "GlobalValues.h"

void Arrow::paint(PaintAccessories *p, GlobalValues *g) {
	g->d2d_render_target->DrawLine(this->start, this->end, p->brush, 1.0f);
}

void Arrow::calculatePosition() {

}

Arrow::Arrow(D2D1_POINT_2F start, D2D1_POINT_2F end, ArrowPath* path) {
	this->start = start;
	this->end = end;
	this->path = path;
}