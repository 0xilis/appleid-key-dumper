#import <Foundation/Foundation.h>

@class NSArray, NSData, NSDate, NSNumber, NSString;

@interface SFAppleIDValidationRecord : NSObject <NSSecureCoding>
{
    NSString *_altDSID;
    NSData *_data;
    NSString *_identifier;
    NSDate *_nextCheckDate;
    unsigned long long _suggestedValidDuration;
    NSArray *_validatedEmailHashes;
    NSArray *_validatedPhoneHashes;
    NSDate *_validStartDate;
    NSNumber *_version;
}

+ (BOOL)supportsSecureCoding;
@property(retain, nonatomic) NSNumber *version; // @synthesize version=_version;
@property(retain, nonatomic) NSDate *validStartDate; // @synthesize validStartDate=_validStartDate;
@property(retain, nonatomic) NSArray *validatedPhoneHashes; // @synthesize validatedPhoneHashes=_validatedPhoneHashes;
@property(retain, nonatomic) NSArray *validatedEmailHashes; // @synthesize validatedEmailHashes=_validatedEmailHashes;
@property(nonatomic) unsigned long long suggestedValidDuration; // @synthesize suggestedValidDuration=_suggestedValidDuration;
@property(retain, nonatomic) NSDate *nextCheckDate; // @synthesize nextCheckDate=_nextCheckDate;
@property(retain, nonatomic) NSString *identifier; // @synthesize identifier=_identifier;
@property(retain, nonatomic) NSData *data; // @synthesize data=_data;
@property(retain, nonatomic) NSString *altDSID; // @synthesize altDSID=_altDSID;
@property(readonly, nonatomic) BOOL needsUpdate;
@property(readonly, nonatomic) BOOL isInvalid;
- (id)description;
- (id)initWithDictionary:(id)arg1;
- (BOOL)isEqualToValidationRecord:(id)arg1;
- (BOOL)isEqual:(id)arg1;
- (id)expirationDate;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;

@end