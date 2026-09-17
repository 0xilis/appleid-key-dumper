#import <Foundation/Foundation.h>
#import <Security/Security.h>
#import "Sharing/SFAppleIDAccount.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
    NSData *plist = (__bridge NSData *) CFPreferencesCopyValue((CFStringRef)@"AppleIDAccount",
        (CFStringRef)@"com.apple.sharingd",
        (CFStringRef)kCFPreferencesCurrentUser,
        (CFStringRef)kCFPreferencesCurrentHost);
    
    SFAppleIDAccount *account = [NSKeyedUnarchiver unarchivedObjectOfClass:SFAppleIDAccount.class fromData:plist error:NULL];
    
    /* Get the SFAppleIDIdentity from it */
    SFAppleIDIdentity *identity = [account identity];
    
    /* Get the certificates from that identity */
    SecCertificateRef cert = (SecCertificateRef)[[account identity] copyCertificate];
    SecCertificateRef intercert = (SecCertificateRef)[[account identity] copyIntermediateCertificate];
    
    /* Get private key from Apple ID. This will be used to sign a public key that we will randomly generate. */
    SecKeyRef privateKey = (SecKeyRef)[identity copyPrivateKey];
    
    /* Generate an ECDSA-P256 key */
    NSMutableDictionary *mutableDict = [NSMutableDictionary dictionary];
    mutableDict[(__bridge id)kSecAttrKeyType] = (__bridge id)kSecAttrKeyTypeECSECPrimeRandom;
    mutableDict[(__bridge id)kSecAttrKeySizeInBits] = @256;
    mutableDict[(__bridge id)kSecAttrIsPermanent] = @NO;
    
    SecKeyRef key = SecKeyCreateRandomKey((__bridge CFDictionaryRef)mutableDict, 0);
    
    /* Get public key */
    SecKeyRef pubKey = SecKeyCopyPublicKey(key);
    NSData *signingPublicKey = (__bridge NSData *)SecKeyCopyExternalRepresentation(pubKey, 0);
    
    /* Sign it with the Apple ID private key */
    CFErrorRef error = NULL;
    CFDataRef data = SecKeyCopyExternalRepresentation(pubKey, &error);
    NSData *signature = (__bridge NSData *)SecKeyCreateSignature(privateKey, kSecKeyAlgorithmRSASignatureMessagePSSSHA256, data, &error);
    
    /* The auth-data field is a plain plist containing the raw CMS record,
     * not an archive of the SFAppleIDValidationRecord Objective-C object. */
    NSData *validationRecordData = account.validationRecord.data;
    if (validationRecordData.length == 0) {
        fprintf(stderr, "appleid-key-dumper: missing Apple ID validation record data\n");
        return EXIT_FAILURE;
    }

    NSDictionary *dict = @{
        @"AppleIDCertificateChain" : @[
            (__bridge NSData *)SecCertificateCopyData(cert),
            (__bridge NSData *)SecCertificateCopyData(intercert),
        ],
        @"SigningPublicKey" : signingPublicKey,
        @"SigningPublicKeySignature" : signature,
        @"AppleIDValidationRecord" : validationRecordData,
    };

    NSError *serializationError = nil;
    NSData *authData = [NSPropertyListSerialization dataWithPropertyList:dict
                                                               format:NSPropertyListBinaryFormat_v1_0
                                                              options:0
                                                                error:&serializationError];
    if (!authData) {
        const char *message = serializationError.localizedDescription.UTF8String;
        fprintf(stderr, "appleid-key-dumper: failed to serialize auth data: %s\n",
                message ? message : "unknown error");
        return EXIT_FAILURE;
    }
    
    printf("writing to file...\n");

    mkdir("/var/mobile/Documents/appleid-key-dumper", 0755);
    [authData writeToFile:@"/var/mobile/Documents/appleid-key-dumper/authData.plist" atomically:FALSE];

    CFErrorRef errorer = NULL; /* its called errorer because its more error */
    CFDataRef keyData = SecKeyCopyExternalRepresentation(key, &errorer);
    if (errorer) {
        fprintf(stderr,"appleid-key-dumper: failed to copy key representation\n");
        return -1;
    }
    NSData *data2 = (__bridge NSData *)keyData;
    [data2 writeToFile:@"/var/mobile/Documents/appleid-key-dumper/privateKey.bin" atomically:FALSE];

    printf("wrote private key and auth data to file\n");
    
    return 0;
}