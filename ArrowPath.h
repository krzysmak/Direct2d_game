#ifndef ARROW_PATH
#define ARROW_PATH

#include <windows.h>
#include <d2d1_3.h>

class ArrowPath {
	// y = ax^2 + bx + c
	FLOAT a;
	FLOAT b;
	FLOAT c;

public:
	ArrowPath(FLOAT a, FLOAT b, FLOAT c);
	ArrowPath(D2D1_POINT_2F first, D2D1_POINT_2F last, FLOAT power);
	FLOAT calculateY(FLOAT x);
};

#endif // ARROW_PATH
