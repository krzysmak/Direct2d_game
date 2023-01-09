#ifndef BITMAP_MAKER
#define BITMAP_MAKER

#include <d2d1_3.h>
#include <wincodec.h>
#include "GlobalValues.h"

void loadBitmap(HWND hwnd, const LPCWSTR name, IWICImagingFactory* pWICFactory, GlobalValues* g);

void initializeFactory(IWICImagingFactory* &pWICFactory);

#endif // !BITMAP_MAKER
