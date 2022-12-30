#ifndef SHOOTING_TARGET
#define SHOOTING_TARGET

#include <Windows.h>
#include <d2d1_3.h>
#include "GlobalValues.h"
#include <vector>
#include "PaintAccessories.h"

class ShootingTarget {
	D2D1_POINT_2F center;
	bool goingUp;
	FLOAT limitY;
	FLOAT radiusX;
	FLOAT radiusY;

public:
	ShootingTarget(FLOAT x, FLOAT y, GlobalValues* g, bool going_up = false);
	void render(GlobalValues* g, PaintAccessories* p);
};


class ShootingRange {
	std::vector<ShootingTarget> targets;
	size_t targets_count;

public:
	void renderTargets(GlobalValues* g, PaintAccessories* p);
	void addTarget(FLOAT x, FLOAT y, GlobalValues* g, bool going_up = false);
	size_t howManyTargets() { return targets_count; }
};

#endif // !SHOOTING_TARGET
