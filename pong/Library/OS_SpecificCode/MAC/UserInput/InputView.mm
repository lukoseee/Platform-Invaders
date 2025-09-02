#import "InputView.hpp"

@implementation InputView

- (instancetype)initWithFrameAndQueue:(NSRect)frame :(Queue*)queue{
    self = [super initWithFrame:frame];
    self.mQueue = queue;
    return self;
}

// ensure the InputView can accept user input
- (BOOL)acceptsFirstResponder {
    return YES;
}

// catch any key presses and store in a queue
- (void)keyDown:(NSEvent *)event {
    [self.mQueue push:[NSString stringWithFormat:@"%@_down", [self eventToString:event]]];
}

- (void)keyUp:(NSEvent *)event {
    [self.mQueue push:[NSString stringWithFormat:@"%@_up", [self eventToString:event]]];
}

// convert the key pressed to a NSString
- (NSString*) eventToString:(NSEvent*) event {
    NSString *pressedKey;
    switch([event keyCode]) {
        // cases for non alphanumeric keys
        case 36: pressedKey = @"return"; break;
        case 51: pressedKey = @"delete"; break; 
        case 123: pressedKey = @"left_arrow"; break;
        case 124: pressedKey = @"right_arrow"; break;
        case 125: pressedKey = @"down_arrow"; break;
        case 126: pressedKey = @"up_arrow"; break;
        default: pressedKey = [event charactersIgnoringModifiers];
    }
    return pressedKey;
}

@end
