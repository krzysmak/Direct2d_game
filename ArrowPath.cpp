#include "ArrowPath.h"

ArrowPath::ArrowPath(FLOAT a, FLOAT b, FLOAT c) {
	this->a = a;
	this->b = b;
	this->c = c;
}
ArrowPath::ArrowPath(D2D1_POINT_2F first, D2D1_POINT_2F last, FLOAT power) {
	FLOAT x2 = (first.x + last.x) / 2;
	FLOAT y2 = first.y > last.y ? first.y / 2 : last.y / 2;

	// Calculate differences
	FLOAT y12 = first.y - y2;
	FLOAT y23 = y2 - last.y;
	FLOAT x12 = first.x - x2;
	FLOAT x23 = x2 - last.x;

	// Calculate second differences
	FLOAT y12_2 = y12 - y23;
	FLOAT x12_2 = x12 - x23;

	// Solve for a, b, and c
	this->a = (y12_2 * x12 - y12 * x12_2) / (x12_2 * x12 * x12 - x12 * x12_2 * x12);
	this->b = (y12 - this->a * x12 * x12 - this->a * first.x * first.x) / x12;
	this->c = first.y - this->a * first.x * first.x - this->b * first.x;
}

FLOAT ArrowPath::calculateY(FLOAT x) {
	FLOAT result = c;
	result += x * b;
	result += (x * x) * a;
	return result;
}