#import <Foundation/Foundation.h>
#import "SFAppleIDAccount.h"

@interface SFAppleIDClient : NSObject<NSSecureCoding>
- (void)myAccountWithCompletion:(void (^)(SFAppleIDAccount *, NSError *))arg1;
@end
