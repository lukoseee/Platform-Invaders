#include "D2dRenderer.hpp"
#include "../UserInput/WindowsUserInputManager.hpp"
#include <chrono>
#include <cmath>
/* Constructor. */
D2dRenderer::D2dRenderer()
{
    mHwnd = NULL;
    mFactory = NULL; //render taget mFactory
    mRenderTargetHwnd = NULL; //render target
    mBitmapFactory = NULL; //bitmap mFactory
}

/* Destructor. */
D2dRenderer::~D2dRenderer()
{
    clearQueue();
    SafeRelease(&mFactory);
    SafeRelease(&mRenderTargetHwnd);
    SafeRelease(&mBitmapFactory);

}

/* Bitmap constructor. */
HRESULT D2dRenderer::LoadBitmapFromFile(
    ID2D1RenderTarget* renderTarget,
    IWICImagingFactory* bitmapFactory,
    PCWSTR uri,
    ID2D1Bitmap** ppBitmap,
    int width,
    int height)
{
    HRESULT hhResult = S_OK;

    //Creates a WIC decoder.
    IWICBitmapDecoder* pDecoder = NULL;
    if (!bitmapFactory) return E_FAIL;
    hhResult = bitmapFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder);

    if (FAILED(hhResult)) {
        wchar_t msg[256];
        swprintf(msg, 256, L"CreateDecoderFromFilename failed: 0x%08X\n", hhResult);
        OutputDebugString(msg); //debug message in event of invalid file path
    }


    if (SUCCEEDED(hhResult)) {
        //retrieves the first frame of the image.
        IWICBitmapFrameDecode* pFrame = NULL;
        hhResult = pDecoder->GetFrame(0, &pFrame);

        if (SUCCEEDED(hhResult)) {
            //converts the frame to a format compatible with Direct2D.
            IWICBitmapScaler* pScaler = nullptr;
            hhResult = bitmapFactory->CreateBitmapScaler(&pScaler);

            if (SUCCEEDED(hhResult)) {
                //scales the image to the desired size.
                hhResult = pScaler->Initialize(pFrame, width, height, WICBitmapInterpolationModeFant);

                if (SUCCEEDED(hhResult)) {
                    //convert the image to a format compatible with Direct2D.
                    IWICFormatConverter* pConverter = NULL;
                    hhResult = bitmapFactory->CreateFormatConverter(&pConverter);

                    //converts the frame to a format compatible with Direct2D.
                    if (SUCCEEDED(hhResult)) {
                        hhResult = pConverter->Initialize(
                            pScaler,
                            GUID_WICPixelFormat32bppPBGRA,
                            WICBitmapDitherTypeNone,
                            NULL,
                            0.f,
                            WICBitmapPaletteTypeCustom);

                        if (SUCCEEDED(hhResult)) {
                            //creates a Direct2D bitmap from the WIC bitmap.
                            hhResult = renderTarget->CreateBitmapFromWicBitmap(
                                pConverter,
                                NULL,
                                ppBitmap);
                        }
                        pConverter->Release();
                    }
                    pScaler->Release();
                }
                pFrame->Release();
            }
            pDecoder->Release();
        }
    }

    return hhResult;

}

/* Frame rendering constructor. */
void D2dRenderer::renderImage(ImageInfo* image, int x, int y)
{
    HRESULT hhResult = S_OK;

    //only call CreateDeviceResources() if the render target does not exist
    if (!mRenderTargetHwnd) {
        hhResult = CreateDeviceResources();
        if (FAILED(hhResult)) {

            return; // don't proceed if device resources couldn't be created
        }
    }

    //image is not yet loaded into hashmap
    if (mImageMap.find(image) == mImageMap.end()) {

        std::string filePath = image->getFilePath();

        // convert file path from std::string to PCWSTR
        std::wstring widePath(filePath.begin(), filePath.end());

        // create a struct to store the bitmap and its position
        ImageData bitmapData;

        //null instance of bitmap to be loaded
        ID2D1Bitmap* bitmap = nullptr;

        //load as bitmap
        hhResult = LoadBitmapFromFile(mRenderTargetHwnd,
            mBitmapFactory,
            widePath.c_str(),
            &bitmap,
            image->getWidth(),
            image->getHeight());

        if (SUCCEEDED(hhResult)) {
            //store bitmap in struct
            bitmapData.bitmap = bitmap;

            //store position in struct
            bitmapData.position = { x , y };

            //store struct in hashmap
            mImageMap[image] = bitmapData;

            // add to the render order to preserve sequence
            mRenderOrder.push_back(image);
        }

    }

}


void D2dRenderer::closeWindow()
{
    if (mHwnd) {
        DestroyWindow(mHwnd);
        mHwnd = NULL;
    }
    DiscardDeviceResources();
}

/* Window creation constructor. */
void D2dRenderer::createWindow(int width, int height, std::string name, bool resizeable)
{
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL))) {

        HRESULT hr = this->Initialize(width, height, name, resizeable); //initialise Direct2d window

        if (SUCCEEDED(hr)) {
            //not calling message loop here, as it will be called in the main game loop
        }
        CoUninitialize();
    }
}

/* Window resizing constructor. */
void D2dRenderer::resizeWindow(int newWidth, int newHeight)
{
    //Note: This method can fail, but it's okay to ignore the error here, because the error will be returned again the next time EndDraw is called.
    if (mRenderTargetHwnd) {
        mRenderTargetHwnd->Resize(D2D1::SizeU(newWidth, newHeight));
    }
}

/* Windows message looping constructor. */
void D2dRenderer::updateDisplay()
{
    MSG msg = { 0 };

    //non-blocking message loop
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return;

        //translate input into messages and dispatches to wndProc
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //render all entites in hashmap to screen
    this->renderFrame();
}

/* Initialising Direct2d functionalities through a constructor. */
HRESULT D2dRenderer::Initialize(int width, int height, std::string name, bool resizeable)
{
    HRESULT hhResult;

    //Initialises device-independent resources, such as the Direct2D mFactory.
    hhResult = CreateDeviceIndependentResources();

    //convert string to wchar_t
    std::wstring widestr = std::wstring(name.begin(), name.end());
    const wchar_t* newName = widestr.c_str();

    //check if resizable window is requested
    DWORD style = WS_OVERLAPPEDWINDOW;

    if (!resizeable) {
        style &= ~WS_THICKFRAME;
        style &= ~WS_MAXIMIZEBOX;
    }
    WindowsUserInputManager* userInputManager = WindowsUserInputManager::getInstance();

    if (SUCCEEDED(hhResult)) {

        //Registers the window class.
        WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = userInputManager->WndProc; //set window procedure to the static WndProc method in WindowsUserInputManager
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = sizeof(LONG_PTR);
        wcex.hInstance = HINST_THISCOMPONENT;
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName = NULL;
        wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
        wcex.lpszClassName = newName;

        RegisterClassEx(&wcex);

        //Create the window hidden, get the DPI, use SetWindowPos to resize, ShowWindow to show changes.
        mHwnd = CreateWindow(
            newName,
            newName,
            style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this);

        if (mHwnd) {
            //Obtains this window's DPI to be used to scale the window size for SetWindowPos.
            float dpi = GetDpiForWindow(mHwnd);

            //calculate new width and height based on DPI
            int newWidth = static_cast<int>(ceil(width * dpi / USER_DEFAULT_SCREEN_DPI)); //96.f is the default DPI Windows OS
            int newHeight = static_cast<int>(ceil(height * dpi / USER_DEFAULT_SCREEN_DPI));

            //create rect to use for AdjustWindowRect
            RECT adjustedRect = { 0, 0, newWidth, newHeight };

            //adjust window size to account for window borders and title bar
            AdjustWindowRect(&adjustedRect, WS_OVERLAPPEDWINDOW, FALSE);

            SetWindowPos(
                mHwnd,
                NULL,
                0,
                0,
                adjustedRect.right - adjustedRect.left, //use adjusted rect to set window size
                adjustedRect.bottom - adjustedRect.top,
                SWP_NOMOVE);
            ShowWindow(mHwnd, SW_SHOWNORMAL);
            UpdateWindow(mHwnd);
        }
    }

    return hhResult;
}

/* Creating Direct2d independent resources through a constructor. */
HRESULT D2dRenderer::CreateDeviceIndependentResources()
{
    HRESULT hhResult = S_OK;

    //Create a Direct2D mFactory.
    hhResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactory);
    return hhResult;
}

/* Creating Direct2d device resources through a constructor. */
HRESULT D2dRenderer::CreateDeviceResources()
{
    HRESULT hhResult = S_OK;

    // Prevent multiple initializations
    if (mRenderTargetHwnd != nullptr) {
        return S_OK; // Already initialized, no need to create again
    }

    if (mHwnd == NULL) {
        printf("Error: Window handle(mHwnd) is NULL in CreateDeviceResources()!\n");
        //return E_FAIL; // Prevents using a null window handle
    }

    if (mFactory == NULL) {
        std::cerr << "Error: Direct2D mFactory is NULL in CreateDeviceResources()!" << std::endl;
        //return E_FAIL; // Prevents using a null mFactory
    }

    // Create render target
    RECT rc;
    GetClientRect(mHwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
    hhResult = mFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(mHwnd, size),
        &mRenderTargetHwnd
    );

    if (SUCCEEDED(hhResult) && mBitmapFactory == NULL) {
        // Create WIC Imaging Factory once and store it globally
        hhResult = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&mBitmapFactory)
        );

        if (FAILED(hhResult)) {
            OutputDebugString(L"Failed to create WIC Imaging Factory\n");
            return hhResult;
        }
    }

    return hhResult;
}

/* Discards Direct2d resources through a constructor. */
void D2dRenderer::DiscardDeviceResources()
{
    SafeRelease(&mRenderTargetHwnd);
}

/* Updates images' positions in hashmaps */
void D2dRenderer::moveRenderedImage(ImageInfo* image, int x, int y) {
    if (!image) {
        printf("Error: moveRenderedImage received a null image!\n");
        std::cerr << "Error: moveRenderedImage received a null image!" << std::endl;
        return;  // Prevent crash
    }
    if (mImageMap.find(image) == mImageMap.end()) {
        printf("Error: No bitmap found for given image in moveRenderedImage!\n");
        std::cerr << "Error: No bitmap found for given image in moveRenderedImage!" << std::endl;
        std::cerr << "Debug: ImageInfo pointer address = " << image << std::endl;
        return;
    }

    mImageMap[image].position = { x, y };
}

/* Removes images from hashmaps */
void D2dRenderer::removeImage(ImageInfo* image) {

    if (mImageMap.find(image) == mImageMap.end()) {
        return; // ImageInfo not found in hashmap
    }

    auto entry = mImageMap.find(image); // Retrieve the ImageData struct mapped to the given ImageInfo


    if (entry->second.bitmap) {
        entry->second.bitmap->Release();  // Direct release
        entry->second.bitmap = nullptr;   // Clear the pointer
    }

    mImageMap.erase(image); //remove entry in hashmap

    mRenderOrder.erase(
        std::remove(mRenderOrder.begin(), mRenderOrder.end(), image),
        mRenderOrder.end()
    );
}

void D2dRenderer::clearQueue() {
    for (auto& pair : mImageMap) {
        if (pair.second.bitmap) {
            pair.second.bitmap->Release(); // Release D2D1 resources
            pair.second.bitmap = nullptr;
        }
    }
    mImageMap.clear();
    mRenderOrder.clear();
}

/* Renders the frame to the window */
HRESULT D2dRenderer::renderFrame()
{
    HRESULT hhResult = S_OK;

    //get rendertarget size
    D2D1_SIZE_F rtSize = mRenderTargetHwnd->GetSize();

    //begin drawing frame
    mRenderTargetHwnd->BeginDraw();

    mRenderTargetHwnd->Clear(D2D1::ColorF(0, 0, 0, 0)); //clear to black

    int i = 0;
    //draw each bitmap in updated positions
    for (ImageInfo* image : mRenderOrder) {

        //std::cout << "Render order[" << i++ << "]: " << image << std::endl;
        auto entry = mImageMap.find(image);

        if (entry == mImageMap.end())
        {
            continue;
            std::cerr << "Null bitmap! Skipping render of image." << std::endl;
        }

        const ImageData& bitmapData = entry->second;
        pos pos = bitmapData.position;

        ID2D1Bitmap* bitmap = bitmapData.bitmap;

        if (!bitmap) {
            std::cerr << "Null bitmap! Skipping render of image." << std::endl;
            continue;
        }

        D2D1_SIZE_F size = bitmap->GetSize();

        //draw bitmap at desired position using the dimensions of the bitmap
        mRenderTargetHwnd->DrawBitmap(bitmap, D2D1::RectF(pos.x,
            rtSize.height - (pos.y + size.height), //flip the y axis to mimic cocao's coordinate system
            pos.x + size.width,
            rtSize.height - pos.y));
    }

    //end drawing frame
    hhResult = mRenderTargetHwnd->EndDraw();

    if (hhResult == D2DERR_RECREATE_TARGET) { //if the render target is lost (window resised,etc), discard resources and recreate
        DiscardDeviceResources();
    }
    return hhResult;
}


