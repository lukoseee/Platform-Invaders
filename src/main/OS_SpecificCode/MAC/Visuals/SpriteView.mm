#import "SpriteView.hpp"

@implementation SpriteView

// basic constructor to initalise property values of sprite
- (instancetype)initWithImage:(NSRect)frame :(NSString*)resource :(int)x :(int)y{
    self = [super initWithFrame:frame];
    if(self){
        self.mSpriteImage = [[NSImage alloc] initWithContentsOfFile:resource];
        self.mSpritePosition = NSMakePoint(x, y);
    }
    return self;
}

// override the default drawing to draw the spriteImage
- (void)drawRect:(NSRect)dirtyRect {
    // call of super.drawRect
    [super drawRect:dirtyRect];
    
    // draw the spriteImage
    [self.mSpriteImage drawAtPoint:self.mSpritePosition fromRect:NSZeroRect operation:NSCompositingOperationSourceOver fraction:1.0];
}

- (void)changeSpritePosition:(int)x :(int)y {
    // change the sprite position property
    self.mSpritePosition = NSMakePoint(x, y);
    
    // tell the system the sprite needs to be drawn again. See drawRect.
    [self setNeedsDisplay:YES];
}

@end
