#include "Minigame.h"
#include <d2d1_3.h>
#include <Windows.h>
#include <utility>

using D2D1::Point2F;
using D2D1::Ellipse;

void Minigame::render(GlobalValues* g, PaintAccessories* p) {
	FLOAT midWidth = g->width / 2;
	FLOAT thirdHeight = g->height / 3;
	this->arrowBottom = (thirdHeight * 2) + 30;
	this->arrowTop = (thirdHeight * 2) + 120;
	FLOAT radius = midWidth < thirdHeight ? midWidth - 40 : thirdHeight - 40;
	auto center = Point2F(midWidth, thirdHeight);
	FLOAT ellipse_size_diffrence = radius / (number_of_colors * 2);
	FLOAT currentRadius = radius;
	g->d2d_render_target->FillEllipse(Ellipse(center, currentRadius + 1, currentRadius + 1), p->black_brush);
	for (size_t i = 0; i < number_of_colors; i++) {
		g->d2d_render_target->FillEllipse(Ellipse(center, currentRadius, currentRadius), p->target_brush[i]);
		currentRadius -= (ellipse_size_diffrence * 2);
	}
	if (GetAsyncKeyState(VK_LBUTTON) < 0) {
		shootArrow(g, p);
	}
	else {
		moveAndRenderArrow(g, p);
	}
}


void Minigame::moveAndRenderArrow(GlobalValues* g, PaintAccessories* p) {
	FLOAT limitLeft = g->width / 8;
	FLOAT limitRight = g->width - limitLeft;
	FLOAT arrowBottom = g->height;
	if (current_arrow_x <= 0) {
		arrow_going_right = std::rand() % 2 == 0;
		current_arrow_x = std::rand() % ((INT)limitRight - (INT)limitLeft + 1) + limitLeft;
	}
	current_arrow_x += arrow_going_right ? arrowSpeed : -1 * arrowSpeed;
	if (current_arrow_x > limitRight) {
		arrow_going_right = false;
	}
	else if (current_arrow_x < limitLeft) {
		arrow_going_right = true;
	}
	auto start = Point2F(current_arrow_x, this->arrowBottom);
	auto end = Point2F(current_arrow_x, this->arrowTop);
	g->d2d_render_target->DrawLine(start, end, p->brush, 1.0f);
}

void Minigame::setArrowSpeed(FLOAT arrowVelocity) {
	arrowSpeed = (INT)arrowVelocity % 10;
	if (arrowSpeed <= 3)
		arrowSpeed = 3;
}

void Minigame::shootArrow(GlobalValues* g, PaintAccessories* p) {

}