#include "ArrowPath.h"

ArrowPath::ArrowPath(FLOAT a, FLOAT b, FLOAT c) {
	this->a = a;
	this->b = b;
	this->c = c;
}
ArrowPath::ArrowPath(D2D1_POINT_2F first, D2D1_POINT_2F last, FLOAT power) {

}

FLOAT ArrowPath::calculateY(FLOAT x) {
	FLOAT result = c;
	result += x * b;
	result += (x * x) * a;
	return result;
}