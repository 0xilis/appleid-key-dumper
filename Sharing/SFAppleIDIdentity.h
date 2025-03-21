#import <Foundation/Foundation.h>

@interface SFAppleIDIdentity : NSObject <NSSecureCoding>
{
    NSString *_encDSID;
    NSString *_intermediateCertificateSerialNumber;
    BOOL _linkedToCurrentUser;
    NSString *_accountIdentifier;
    NSString *_altDSID;
    NSString *_appleID;
    NSDate *_certificateExpirationDate;
    NSData *_certificatePersistentReference;
    NSDate *_intermediateCertificateExpirationDate;
    NSData *_intermediateCertificatePersistentReference;
    NSDate *_lastValidationAttemptDate;
    NSDate *_lastValidationDate;
    NSDate *_modificationDate;
    NSData *_privateKeyPersistentReference;
    NSString *_serialNumber;
}

+ (BOOL)supportsSecureCoding;
@property(retain, nonatomic) NSString *serialNumber; // @synthesize serialNumber=_serialNumber;
@property(retain, nonatomic) NSData *privateKeyPersistentReference; // @synthesize privateKeyPersistentReference=_privateKeyPersistentReference;
@property(retain, nonatomic) NSDate *modificationDate; // @synthesize modificationDate=_modificationDate;
@property(nonatomic) BOOL linkedToCurrentUser; // @synthesize linkedToCurrentUser=_linkedToCurrentUser;
@property(retain, nonatomic) NSDate *lastValidationDate; // @synthesize lastValidationDate=_lastValidationDate;
@property(retain, nonatomic) NSDate *lastValidationAttemptDate; // @synthesize lastValidationAttemptDate=_lastValidationAttemptDate;
@property(retain, nonatomic) NSData *intermediateCertificatePersistentReference; // @synthesize intermediateCertificatePersistentReference=_intermediateCertificatePersistentReference;
@property(retain, nonatomic) NSDate *intermediateCertificateExpirationDate; // @synthesize intermediateCertificateExpirationDate=_intermediateCertificateExpirationDate;
@property(retain, nonatomic) NSData *certificatePersistentReference; // @synthesize certificatePersistentReference=_certificatePersistentReference;
@property(retain, nonatomic) NSDate *certificateExpirationDate; // @synthesize certificateExpirationDate=_certificateExpirationDate;
@property(readonly, nonatomic) NSString *appleID; // @synthesize appleID=_appleID;
@property(readonly, nonatomic) NSString *altDSID; // @synthesize altDSID=_altDSID;
@property(retain, nonatomic) NSString *accountIdentifier; // @synthesize accountIdentifier=_accountIdentifier;

- (int)verifyKeys;
- (void)removeFromKeychain;
- (struct OpaqueSecIdentityRef *)copyIdentity;
@property(readonly, nonatomic) BOOL needsRenewal;
@property(readonly, nonatomic) BOOL isInvalid;
@property(readonly, nonatomic) BOOL intermediateCertificateExpired;
@property(readonly, nonatomic) NSString *intermediateCertificateSerialNumber;
@property(readonly, nonatomic) BOOL certificateExpired;
- (BOOL)isDateInThePast:(id)arg1;
- (struct OpaqueSecKeyRef *)copyPrivateKey;
- (struct OpaqueSecCertificateRef *)copyIntermediateCertificate;
- (struct OpaqueSecCertificateRef *)copyCertificateWithType:(long long)arg1;
- (struct OpaqueSecCertificateRef *)copyCertificate;
- (id)description;
- (id)initWithDictionary:(id)arg1;
- (id)initWithAppleID:(id)arg1 altDSID:(id)arg2;
- (BOOL)isEqualToIdentity:(id)arg1;
- (BOOL)isEqual:(id)arg1;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;

@end