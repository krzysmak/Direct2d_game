#include "GlobalValues.h"
#include <windows.h>
#include <d2d1_3.h>

using D2D1::RenderTargetProperties;
using D2D1::HwndRenderTargetProperties;
using D2D1::SizeU;

GlobalValues::GlobalValues() {
	d2d_factory = nullptr;
	d2d_render_target = nullptr;
    mouse_x = -1;
    mouse_y = -1;
}

HRESULT GlobalValues::initValues(const HWND &hwnd) {
    HRESULT hr = S_OK;

    GetClientRect(hwnd, &rc);

    this->width = rc.right - rc.left;
    this->height = rc.bottom - rc.top;
    this->first_width = this->width;
    this->first_height = this->height;
    this->archer_center_x = this->width / 2;
    this->archer_center_y = this->height / 2;
    this->arrow_distance_from_archer_center = 20;
    this->arrow_length = 30;

    if (!d2d_factory) {
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory);
        if (!SUCCEEDED(hr)) {
            return hr;
        }
    }

    if (!d2d_render_target) {
        hr = d2d_factory->CreateHwndRenderTarget(
            RenderTargetProperties(),
            HwndRenderTargetProperties(hwnd,
                SizeU(static_cast<UINT32>(rc.right) -
                    static_cast<UINT32>(rc.left),
                    static_cast<UINT32>(rc.bottom) -
                    static_cast<UINT32>(rc.top))),
            &d2d_render_target);
        if (!SUCCEEDED(hr)) {
            return hr; // TODO delete check.
        }
    }

    return hr;
}

void GlobalValues::updateRC(const HWND& hwnd) {
    GetClientRect(hwnd, &rc);

    this->width = rc.right - rc.left;
    this->height = rc.bottom - rc.top;
    this->archer_center_x = this->width / 2;
    this->archer_center_y = this->height / 2;
    this->arrow_distance_from_archer_center = 20;
    this->arrow_length = 30;
}

void GlobalValues::destroyValues() {
    if (d2d_render_target) d2d_render_target->Release();
    if (d2d_factory) d2d_factory->Release();
}