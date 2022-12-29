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

	GlobalValues();
	HRESULT initValues(const HWND& hwnd);
	void destroyValues();
};

#endif // GLOBAL_VALUES