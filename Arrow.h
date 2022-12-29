#ifndef ARROW
#define ARROW

#include <windows.h>
#include <d2d1_3.h>
#include "PaintAccessories.h"
#include "GlobalValues.h"

class Arrow {
	D2D1_POINT_2F start;
	D2D1_POINT_2F end;

public:
	Arrow(D2D1_POINT_2F start, D2D1_POINT_2F end);
	void paint(PaintAccessories *p, GlobalValues *g);
	void calculatePosition();
};

#endif // ARROW
