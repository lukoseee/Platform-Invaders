#import <Cocoa/Cocoa.h>

/*
 Queue is a simple wrapper of a NS-array structure (NSMutableArray), providing
 queue FIFO behaviour.
 
 This is manually provided as there is no such 'NSQueue' object.
 */
@interface Queue : NSObject;

@property (nonatomic, strong) NSMutableArray *mArr;

- (NSString*) pop;
- (void) push:(NSString*)obj;
- (bool) isEmpty;

@end
