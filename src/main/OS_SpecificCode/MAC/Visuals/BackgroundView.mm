#include "BackgroundView.hpp"

@implementation BackgroundView

- (void)drawRect:(NSRect)dirtyRect {
    [[NSColor blackColor] setFill];
    NSRectFill(dirtyRect);
}

@end
