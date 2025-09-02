#import <Cocoa/Cocoa.h>
#import "Queue.hpp"

/*
 InputView is an invisible NSView which is added to the window to catch and
 process unser input
*/
@interface InputView : NSView

@property Queue* mQueue;
- (instancetype) initWithFrameAndQueue:(NSRect)frameRect :(Queue*)queue;
- (NSString*) eventToString:(NSEvent*) event;

@end
