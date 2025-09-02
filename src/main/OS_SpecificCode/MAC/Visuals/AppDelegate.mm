#import "AppDelegate.hpp"

@implementation AppDelegate

- (void) createWindow:(int)width :(int)height :(NSString*)windowName :(BOOL) resizeable{
    // create a base frame rect of the width and height of the window
    // x, y position is 0,0 as this is the basis for all further graphics
    self.mFrame = NSMakeRect(0, 0, width, height);
    
    // configure window properties based upon if the window should be resizeable or not
    NSWindowStyleMask baseMask = NSWindowStyleMaskTitled |
    NSWindowStyleMaskClosable |
    NSWindowStyleMaskMiniaturizable;
    NSWindowStyleMask mask = resizeable ?
    baseMask | NSWindowStyleMaskResizable : baseMask;
    
    // construct a window using the above frame and window properties
    self.mWindow = [[NSWindow alloc]
                   initWithContentRect:self.mFrame
                   styleMask:mask
                   backing:NSBackingStoreBuffered
                   defer:YES];
    
    // center window on screen
    [self.mWindow center];
    
    // set window name
    [self.mWindow setTitle:windowName];
    
    // Set a default background to add views to
    self.mView = [[BackgroundView alloc] initWithFrame:self.mFrame];
    [self.mWindow setContentView:self.mView];
    [self.mWindow makeFirstResponder:self.mView];
    
    // display window
    [self.mWindow makeKeyAndOrderFront:nil];
    
    // add user input handler if initalised
    [self.mWindow.contentView addSubview:self.mInputView];
    [self.mWindow makeFirstResponder:self.mInputView];
    
}

// construct a new graphic to be added to the window
- (SpriteView*) createNewSprite:(int)x :(int)y :(NSString*)resource {
    SpriteView* spriteView = [[SpriteView alloc] initWithImage:self.mFrame :resource :x :y];
    [self.mWindow.contentView addSubview:spriteView];
    return spriteView;
}

// remove a graphic from the screen
- (void) removeSpriteView:(SpriteView*)view {
    [view removeFromSuperview];
}

@end
