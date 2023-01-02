#ifndef ARROW
#define ARROW

#include <windows.h>
#include <d2d1_3.h>
#include "PaintAccessories.h"
#include "GlobalValues.h"

class Arrow {
	D2D1_POINT_2F start;
	D2D1_POINT_2F end;
	bool isFlying = false;
	bool isDrawing = false;
	bool reachedTop = false;
	FLOAT velocity = 1;
	FLOAT tiltRatioX = 0.0f;
	FLOAT tiltRatioY = 0.0f;


public:
	Arrow(D2D1_POINT_2F start, D2D1_POINT_2F end);
	Arrow(GlobalValues *g);
	FLOAT getArrowEndX() { return end.x; }
	FLOAT getArrowEndY() { return end.y; }
	void paint(PaintAccessories *p, GlobalValues *g);
	void calculatePosition(FLOAT mouse_x, FLOAT mouse_y, GlobalValues* g);
	void onKeyDown(GlobalValues* g);
	void onKeyUp();
	bool checkIfLanded(GlobalValues *g);
	FLOAT getVelocity() { return velocity; }
};

#endif // ARROW
