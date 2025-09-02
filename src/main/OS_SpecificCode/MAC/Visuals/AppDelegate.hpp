#pragma once

#import <Cocoa/Cocoa.h>

#import "SpriteView.hpp"
#import "BackgroundView.hpp"
#import "../UserInput/InputView.hpp"

/*
 AppDelegate is a delegate class which manages the app as a whole i.e. the
 running instance of the game. Directly interfaces with Cocoa API to render
 graphics
 
 The CocoaRenderer interacts with this delegate to display graphics to the
 mWindow
 */
@interface AppDelegate : NSObject <NSApplicationDelegate>

// properties

// properties for mWindow creation and graphical rendering
@property (strong, nonatomic) NSWindow* mWindow;
@property (strong, nonatomic) NSView* mView;
@property NSRect mFrame;

// property to catch user input
@property (strong, nonatomic) InputView* mInputView;

// methods

// instantiate a mWindow
- (void) createWindow:(int)width :(int)height :(NSString*)windowName :(BOOL)resizeable;

// render a new graphic to the screen (a sprite)
- (SpriteView*) createNewSprite:(int)x :(int)y :(NSString*)filepath;

// remove a graphic from the screen
- (void) removeSpriteView:(SpriteView*)view;

@end

