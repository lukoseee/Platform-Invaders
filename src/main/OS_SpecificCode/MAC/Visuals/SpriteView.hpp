#pragma once
#import <Cocoa/Cocoa.h>

/*
 SpriteView represents graphics rendered to the window. Stores all necessary
 data to render the graphic to the screen.
 
 Abstraction layer Images are mapped to SpriteViews
 */
@interface SpriteView : NSView

// The image for the sprite
@property (nonatomic) NSImage *mSpriteImage;

// The position of the sprite
@property (nonatomic) NSPoint mSpritePosition;

// constructor with the image path and location
- (instancetype)initWithImage:(NSRect)frame :(NSString*)resource :(int)x : (int)y;

// alter the position of the sprite if already rendered
- (void)changeSpritePosition:(int)x :(int)y;

@end
