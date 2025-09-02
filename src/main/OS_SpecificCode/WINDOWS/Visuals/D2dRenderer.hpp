#pragma once
#pragma comment(lib, "d2d1")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "d2d1.lib")

//Access files provided by programmer-development.
#include "../../../AbstractionLayer/OtherInterfaces/VisualRendererInterface.hpp"
#include "../../../AbstractionLayer/Util/ImageInfo.hpp"

//Access files provided by the C++ standard.
#include <windows.h>
#include <wincodec.h>
#include <d2d1.h>
#include <iostream>
#include <queue>
#include <unordered_map>


/* Releases window pointer. */
template<class Interface>
inline void SafeRelease(
    //Creates pointer.
    Interface** ptrRelease)
{
    //Releases the window pointer if it is pointing.
    if (*ptrRelease != NULL) {
        (*ptrRelease)->Release();
        (*ptrRelease) = NULL;
    }
}

/* Provides instance handling of the current executable. */
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class D2dRenderer : public VisualRendererInterface
{
public:
    //Constructor and destructor for memory management.
    D2dRenderer();
    ~D2dRenderer();

    //Functions from the D2dRenderer.cpp file.
    void createWindow(int, int, std::string, bool) override;
    void closeWindow() override;
    void resizeWindow(int, int);
    void updateDisplay() override;
    void clearQueue();

    virtual void renderImage(ImageInfo*, int, int) override;
    virtual void moveRenderedImage(ImageInfo*, int, int) override;
    virtual void removeImage(ImageInfo*) override;

    //Register the window class and call methods for instantiating drawing resources.
    HRESULT Initialize(int width, int height, std::string, bool);

    //Turns image into bitmap.
    HRESULT LoadBitmapFromFile(
        ID2D1RenderTarget* renderTarget,
        IWICImagingFactory* bitmapFactory,
        PCWSTR uri,
        ID2D1Bitmap** ppBitmap,
        int width,
        int height);

private:
    //Initialise device-independent resources.
    HRESULT CreateDeviceIndependentResources();

    //Initialise device-dependent resources.
    HRESULT CreateDeviceResources();

    //Release device-dependent resource.
    void DiscardDeviceResources();

    HRESULT renderFrame();

    //Functionalities for manipulating each frame on the window.
private:
    HWND mHwnd;
    ID2D1Factory* mFactory;
    ID2D1HwndRenderTarget* mRenderTargetHwnd;
    IWICImagingFactory* mBitmapFactory;

    //position struct to hold x and y coordinates.
    typedef struct {
        int x;
        int y;
    }pos;

    //struct to hold bitmap and its position.
    struct ImageData {
        ID2D1Bitmap* bitmap;
        pos position;
    };

    //hashmap to hold image and bitmap data.
    std::unordered_map<ImageInfo*, ImageData> mImageMap;
    std::vector<ImageInfo*> mRenderOrder; //holds the sequence of images to be rendered 

};
