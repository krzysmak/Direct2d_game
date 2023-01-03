#ifndef GLOBAL_VALUES
#define GLOBAL_VALUES

#include <windows.h>
#include <d2d1_3.h>

class GlobalValues {
public:
	ID2D1Factory7* d2d_factory;
	ID2D1HwndRenderTarget* d2d_render_target;
	RECT rc;
	FLOAT width;
	FLOAT height;
	FLOAT mouse_x;
	FLOAT mouse_y;
	FLOAT archer_center_x;
	FLOAT archer_center_y;
	FLOAT arrow_distance_from_archer_center;
	FLOAT arrow_length;
	FLOAT first_width; 
	FLOAT first_height;
	const size_t number_of_targets = 3;
	const size_t baloon_pop_animation_length = 60;
	FLOAT ground_level;
	bool minigame = false;
	FLOAT arrowHitYPercent;
	GlobalValues();
	HRESULT initValues(const HWND& hwnd);
	void updateRC(const HWND& hwnd);
	void destroyValues();
};

#endif // GLOBAL_VALUES