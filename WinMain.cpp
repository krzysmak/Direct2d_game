#include "WinMain.h"
#include "GlobalValues.h"
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

GlobalValues *g;

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
        g = new GlobalValues();
        g->initValues(hwnd);
        return 0;
    case WM_DESTROY:
        g->destroyValues();
        free(g);
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        g->d2d_render_target->BeginDraw();

        g->d2d_render_target->EndDraw();
        InvalidateRect(hwnd, &rc, 0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
