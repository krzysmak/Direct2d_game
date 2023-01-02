#ifndef SHOOTING_TARGET
#define SHOOTING_TARGET

#include <Windows.h>
#include <d2d1_3.h>
#include "GlobalValues.h"
#include <vector>
#include "PaintAccessories.h"

// TODO je¿eli starczy czasu - dziedziczenie klas, Balon i Target jako objekt - cel.

class Baloon {
	D2D1_POINT_2F center;
	FLOAT radiusX;
	FLOAT radiusY;

public:
	int ticks_popped = 0; // 0 if baloon is alive
	Baloon(FLOAT x, FLOAT y, GlobalValues* g);
	void render(GlobalValues* g, PaintAccessories* p);
	bool isOutsideTheScreen();
	void checkHit(FLOAT arrowX, FLOAT arrowY, GlobalValues* g, PaintAccessories* p);
	void pop(GlobalValues* g, PaintAccessories* p);
};

class ShootingTarget {
	const size_t number_of_colors = 5;
	D2D1_POINT_2F center;
	bool goingUp;
	FLOAT limitY;
	FLOAT radiusX;
	FLOAT radiusY;

public:
	ShootingTarget(FLOAT x, FLOAT y, GlobalValues* g, bool going_up = false);
	void render(GlobalValues* g, PaintAccessories* p);
	void checkHit(FLOAT arrowX, FLOAT arrowY, GlobalValues* g, PaintAccessories* p);
	void pop(GlobalValues* g, PaintAccessories* p);
};

class ShootingRange {
	std::vector<ShootingTarget> targets;
	Baloon *baloon;
	size_t targets_count;

public:
	void renderTargets(GlobalValues* g, PaintAccessories* p);
	void addTarget(FLOAT x, FLOAT y, GlobalValues* g, bool going_up = false);
	void renderBaloon(GlobalValues* g, PaintAccessories* p);
	size_t howManyTargets() { return targets_count; }
	void checkHits(FLOAT arrowX, FLOAT arrowY, GlobalValues* g, PaintAccessories* p);
};

#endif // !SHOOTING_TARGET
