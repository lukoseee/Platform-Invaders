#include "CocoaRenderer.hpp"

CocoaRenderer::CocoaRenderer() {
    mRenderedImages = new unordered_map<ImageInfo*, SpriteView*>();

	// Create & initialise the app delegate on renderer construction.
	[NSApplication sharedApplication];
	mAppDelegate = [[AppDelegate alloc] init];
	[NSApp setDelegate:mAppDelegate];
	[NSApp finishLaunching];
}

CocoaRenderer::~CocoaRenderer() {
    closeWindow(); // Close the window on destructor
    delete mRenderedImages;
}

void CocoaRenderer::createWindow(int width, int height, std::string windowName, bool resizeable) {
    BOOL convBool = resizeable ? YES : NO;
    NSString* convString = [NSString stringWithUTF8String:windowName.c_str()];
    [mAppDelegate createWindow:width :height :convString :convBool];
}

void CocoaRenderer::closeWindow() {
       // Remove all SpriteViews
       for (auto& pair : *mRenderedImages) {
           SpriteView* view = pair.second;
           [mAppDelegate removeSpriteView:view];
       }
       mRenderedImages->clear();

       // Close and release the window
       if (mAppDelegate.mWindow) {
           [mAppDelegate.mWindow close];
           mAppDelegate.mWindow = nil;
       }
}

void CocoaRenderer::renderImage(ImageInfo* image, int x, int y) {
    // if the image is already rendered -> do nothing
    if(mRenderedImages->find(image) != mRenderedImages->end())
        return;
    
    // convert filePath to NSString
    string filePath = image->getFilePath();
    NSString* nsPath = [NSString stringWithCString:filePath.c_str() encoding:NSUTF8StringEncoding];
    
    // render it and store the SpriteView
    SpriteView* view = [mAppDelegate createNewSprite:x :y :nsPath];
    [view.mSpriteImage setSize:NSMakeSize(image->getWidth(), image->getHeight())];
    mRenderedImages->insert({image, view});
}

void CocoaRenderer::moveRenderedImage(ImageInfo* image, int x, int y) {
    // if the image is not rendered -> do nothing
    if(mRenderedImages->find(image) == mRenderedImages->end())
        return;
    
    // otherwise change the positin of the assoicated SpriteView
    SpriteView* view = mRenderedImages->at(image);
    [view changeSpritePosition:x :y];
}

void CocoaRenderer::removeImage(ImageInfo* image) {
    // if the image is not rendered -> do nothing
    if(mRenderedImages->find(image) == mRenderedImages->end())
        return;
    
    // otherwise remove the image from the window and remove it from the
    // ImageInfo->SpriteView map
    SpriteView* view = mRenderedImages->at(image);
    mRenderedImages->erase(image);
    [mAppDelegate removeSpriteView:view];
}

// processes any pending events
void CocoaRenderer::updateDisplay() {
    // if the window is no longer open, close the application
    BOOL windowOpen = NO;
    for (NSWindow *window in [NSApp windows]) {
        if ([window isVisible]) {
            windowOpen = YES;
            break;
        }
    }
    
    if (!windowOpen) {
        [NSApp terminate:nil];
        return;
    }
    
    // handle pending events
    @autoreleasepool {
        NSEvent* ev;
        do {
            // get the next event which needs to be proceses
            ev = [NSApp nextEventMatchingMask: NSEventMaskAny
                                    untilDate: nil
                                       inMode: NSDefaultRunLoopMode
                                      dequeue: YES];
            if (ev) {
                // process even via standard Cocoa event delegation process
                [NSApp sendEvent: ev];
            }
            
        // do this while there are still events to handle
        } while (ev);
    }
}
