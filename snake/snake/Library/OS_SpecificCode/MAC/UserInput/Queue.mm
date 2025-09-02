#import "Queue.hpp"

@implementation Queue

// basic instance constructor
- (instancetype)init {
    self = [super init];
    if (self) {
        self.mArr = [NSMutableArray array];
    }
    return self;
}

// pop data from the head of the queue, return it
- (NSString*) pop {
    // sanity check for if the queue is empty
    if ([self isEmpty]) {
        return nil;
    }
    
    // else: pop head, return string
    NSString* str = [self.mArr objectAtIndex:0];
    [self.mArr removeObjectAtIndex:0];
    return str;
}

// add string to back of queue
- (void) push:(NSString*)str {
    [self.mArr addObject:str];
}

- (bool) isEmpty {
    return [self.mArr count] == 0;
}
@end
