#include "WinMain.h"
#include "GlobalValues.h"
#include "PaintAccessories.h"
#include "Arrow.h" 
#include <windows.h>
#include <d2d1_3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <windowsx.h>
#include "ShootingTarget.h"
#include "Minigame.h"

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
PaintAccessories *p;
Arrow* arrow;
ShootingRange* range;
Minigame* minigame;

INT WINAPI wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ PWSTR cmd_line, _In_ INT cmd_show) {

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

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void exampleHandler() {
    exit(0);
}

void arrowAction() {
    if (!arrow) {
        arrow = new Arrow(g);
    }
    if (GetAsyncKeyState(VK_LBUTTON) < 0)
        arrow->onKeyDown(g);
    else
        arrow->onKeyUp();

    arrow->calculatePosition(g->mouse_x, g->mouse_y, g);
    arrow->paint(p, g);
    range->checkHits(arrow->getArrowEndX(), arrow->getArrowEndY(), g, p);
    if (arrow->checkIfLanded(g)) {
        delete arrow;
        arrow = nullptr;
    };
}

void createRange() {
    if (!range) {
        range = new ShootingRange();
    }
    if (range->howManyTargets() == 0) {
        range->addTarget(g->width * 0.9, g->height * 0.8, g);
    }
}

void renderShootingTargets() {
    range->renderTargets(g, p);
    range->renderBaloon(g, p);
}

void renderMinigame() {
    if (!minigame) {
        minigame = new Minigame();
    }
    minigame->setArrowSpeed(arrow->getVelocity());
    minigame->render(g, p);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
        case WM_CREATE:
        {
            if (!g) {
                g = new GlobalValues();
                HRESULT hr = g->initValues(hwnd);
                if (!SUCCEEDED(hr)) {
                    exampleHandler();
                }
            }
            if (!p) {
                p = new PaintAccessories();
                p->initAccessories(g);
            }
            createRange();
            SetTimer(hwnd, 1, 5, NULL);
            return 0;
        }
        case WM_DESTROY:
        {
            KillTimer(hwnd, 1);
            g->destroyValues();
            free(g);
            PostQuitMessage(0);
            return 0;
        }
        case WM_MOUSEMOVE:
        {
            g->mouse_x = LOWORD(lParam);
            g->mouse_y = HIWORD(lParam);
            return 0;
        }
        case WM_PAINT:
        {
            g->updateRC(hwnd);
            g->d2d_render_target->BeginDraw();

            g->d2d_render_target->Clear(p->clear_color);

            Matrix3x2F scale = Matrix3x2F::Scale(g->first_width / g->width, g->first_height / g->height, Point2F(0, 0));
            g->d2d_render_target->SetTransform(scale);
            if (!g->minigame) {
                renderShootingTargets();
                arrowAction();
            }
            else {
                renderMinigame();
            }
            g->d2d_render_target->EndDraw();
            InvalidateRect(hwnd, &g->rc, 0);
           
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
