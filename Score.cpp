#include "Score.h"
#include <dwrite_3.h>
#include <Windows.h>
#include <d2d1_3.h>
#include "PaintAccessories.h"
#include "GlobalValues.h"

using D2D1::RectF;

void initializeWriteFactory(GlobalValues *g) {
    IDWriteFactory* write_factory = nullptr;
    
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&write_factory)
    );
    write_factory->CreateTextFormat(
        TEXT("Times New Roman"),
        nullptr,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        25.0f,
        TEXT("en-us"),
        &g->text_format
    );
}

void write(WCHAR const NAPIS[], GlobalValues* g, PaintAccessories* p) {
    g->d2d_render_target->DrawText(
        NAPIS,
        wcslen(NAPIS),
        g->text_format,
        RectF(
            10.0f, 10.0f,
            static_cast<FLOAT>(g->rc.right),
            static_cast<FLOAT>(g->rc.bottom)
        ), p->brush);
}