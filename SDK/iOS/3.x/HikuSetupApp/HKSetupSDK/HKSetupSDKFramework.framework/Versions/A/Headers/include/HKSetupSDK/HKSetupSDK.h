//
//  HKSetupSDK.h
//  HKSetupSDK
//
//  Created by Rajan Bala on 10/10/14.
//  Copyright (c) 2014 hiku labs, inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Foundation/Foundation.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <AVFoundation/AVFoundation.h>
#import <MessageUI/MessageUI.h>
#import <MessageUI/MFMailComposeViewController.h>


typedef enum : NSUInteger {
    SDKHKPRESENTATION_MODAL,
    SDKHKPRESENTATION_PUSH
} SDKHKPresentationStyle;

@protocol HKSetupDelegate;

@interface HKSetupSDK : NSObject

@property (strong, nonatomic) NSString* app_id;
@property (strong, nonatomic) NSString* shared;
@property (strong, nonatomic) NSString* email;
@property (strong, nonatomic) UIImage* partner_logo;
@property (strong, nonatomic) id<HKSetupDelegate> delegate;

+ (HKSetupSDK *)instance;
// sdkParameters dictionary should have the following format:
//     @{
//         @"app_id" : <NSString>, // mandatory
//         @"shared_secret" : <NSString>, // mandatory
//         @"email" : <NSString>, // optional
//         @"partner_logo" : <UIImage> // optional
//      }
- (id)initWithParameters:(NSDictionary *)sdkParameters;
- (id)initWithAppId:(NSString *)app_id shared:(NSString *)shared email:(NSString* )email;
- (void)startSetup:(UIViewController *)withViewController;
- (void)startSetup:(UIViewController *)withViewController withPresentationStyle:(SDKHKPresentationStyle)presentationStyle;
- (void)logoutUser;
- (NSString *)getApplicationTokenForUser;
- (void)launchTipsFlow:(UIViewController *)withViewController;
- (void)launchTipsFlow:(UIViewController *)withViewController withPresentationStyle:(SDKHKPresentationStyle)presentationStyle;

@end


@protocol HKSetupDelegate <NSObject>
- (void) applicationAuthorizationStatus:(BOOL)success sdk:(HKSetupSDK *)sdk;
- (void) userAuthenticationStatus:(BOOL)success sdk:(HKSetupSDK *)sdk;
- (void) deviceSetupStatus:(BOOL)success sdk:(HKSetupSDK *)sdk;
- (void) userCancelledSetup:(HKSetupSDK *)sdk;
@end
