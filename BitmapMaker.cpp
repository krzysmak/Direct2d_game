#include "BitmapMaker.h"

void loadBitmap(HWND hwnd, const LPCWSTR name, IWICImagingFactory* pWICFactory, GlobalValues *g) {
    HRESULT hr;
    IWICBitmapDecoder* pDecoder = NULL;
    hr = pWICFactory->CreateDecoderFromFilename(name, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
    if (FAILED(hr))
        exit(0);
    IWICBitmapFrameDecode* pFrame = NULL;
    hr = pDecoder->GetFrame(0, &pFrame);
    if (FAILED(hr))
        exit(0);
    IWICFormatConverter* pConverter = NULL;
    hr = pWICFactory->CreateFormatConverter(&pConverter);
    if (FAILED(hr))
        exit(0);
    hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);
    if (FAILED(hr))
        exit(0);
    hr = g->d2d_render_target->CreateBitmapFromWicBitmap(pConverter, NULL, &g->landscape);
    if (FAILED(hr))
        exit(0);
}

void initializeFactory(IWICImagingFactory* &pWICFactory) {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
        exit(0);
    hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
    if (FAILED(hr))
        exit(0);
}