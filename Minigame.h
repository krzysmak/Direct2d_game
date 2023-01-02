#ifndef MINIGAME
#define MINIGAME

#include "GlobalValues.h"
#include "PaintAccessories.h"

class Minigame {
	const size_t number_of_colors = 5;
	FLOAT current_arrow_x = -1;
	bool arrow_going_right;
	FLOAT arrowSpeed;
	FLOAT arrowBottom;
	FLOAT arrowTop;
public:
	void render(GlobalValues *g, PaintAccessories *p);
	void moveAndRenderArrow(GlobalValues* g, PaintAccessories* p);
	void setArrowSpeed(FLOAT arrowVelocity);
	void shootArrow(GlobalValues* g, PaintAccessories* p);
};

#endif // !MINIGAME
