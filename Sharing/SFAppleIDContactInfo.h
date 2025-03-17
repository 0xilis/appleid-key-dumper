#import <Foundation/Foundation.h>

@interface SFAppleIDContactInfo : NSObject <NSSecureCoding>
{
    NSString *_firstName;
    NSString *_lastName;
    NSArray *_validatedEmailAddresses;
    NSArray *_validatedPhoneNumbers;
}

+ (BOOL)supportsSecureCoding;
@property(retain, nonatomic) NSArray *validatedPhoneNumbers; // @synthesize validatedPhoneNumbers=_validatedPhoneNumbers;
@property(retain, nonatomic) NSArray *validatedEmailAddresses; // @synthesize validatedEmailAddresses=_validatedEmailAddresses;
@property(retain, nonatomic) NSString *lastName; // @synthesize lastName=_lastName;
@property(retain, nonatomic) NSString *firstName; // @synthesize firstName=_firstName;
- (id)description;
- (id)initWithDictionary:(id)arg1;
- (BOOL)isEqualToContactInfo:(id)arg1;
- (BOOL)isEqual:(id)arg1;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;

@end