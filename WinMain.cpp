#include <windows.h>
#include <d2d1_3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

using D2D1::RenderTargetProperties;
using D2D1::HwndRenderTargetProperties;
using D2D1::SizeU;

using D2D1::ColorF;
using D2D1::LinearGradientBrushProperties;
using D2D1::Point2F;
using D2D1::RadialGradientBrushProperties;
using D2D1::BezierSegment;
using D2D1::QuadraticBezierSegment;
using D2D1::Matrix3x2F;
using D2D1::Ellipse;
using std::sin;

ID2D1Factory7* d2d_factory = nullptr;
ID2D1HwndRenderTarget* d2d_render_target = nullptr;

INT WINAPI wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ PWSTR cmd_line, _In_ INT cmd_show) {


    // Register the window class.
    const wchar_t CLASS_NAME[] = TEXT("Sample Window Class");

    WNDCLASSEX wc = { };

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_GLOBALCLASS;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = CLASS_NAME;
    wc.hIconSm = nullptr;


    RegisterClassEx(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        TEXT("Learn to Program Windows"),    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        instance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, cmd_show);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

RECT rc;

void exampleHandler() {
    exit(0);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
    case WM_CREATE:
        if (!d2d_factory) {
            HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory);
            if (!SUCCEEDED(hr)) {
                exampleHandler();
            }
        }

        if (!d2d_render_target) {
            HRESULT hr = d2d_factory->CreateHwndRenderTarget(
                RenderTargetProperties(),
                HwndRenderTargetProperties(hwnd,
                    SizeU(static_cast<UINT32>(rc.right) -
                        static_cast<UINT32>(rc.left),
                        static_cast<UINT32>(rc.bottom) -
                        static_cast<UINT32>(rc.top))),
                &d2d_render_target);
            if (!SUCCEEDED(hr)) {
                exampleHandler();
            }
        }
        return 0;
    case WM_DESTROY:
        if (d2d_render_target) d2d_render_target->Release();
        if (d2d_factory) d2d_factory->Release();
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        d2d_render_target->BeginDraw();

        d2d_render_target->EndDraw();
        InvalidateRect(hwnd, &rc, 0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
