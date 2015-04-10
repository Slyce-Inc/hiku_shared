//
//  BlinkUpStringFormatParameters.h
//  BlinkUp
//
//  Created by Brett Park on 12/8/2013.
//  Copyright (c) 2013 Electric Imp, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Collection of arrays that can be used for parameters based on NSString format
 *   in the .strings localization files
 *

   @code
   //Example .strings text
   "GlobalFooter" = @"%@ is logged in";

   //Example setting of parameter for the format string
   blinkUpController.strings.globalFooter = @[@"Joe User"];
   @endcode
 */
@interface BlinkUpStringFormatParameters : NSObject

//BlinkUpSDK.strings
@property (nonatomic, copy) NSArray *globalTitle;
@property (nonatomic, copy) NSArray *globalFooter;
@property (nonatomic, copy) NSArray *interstitialContinue;
@property (nonatomic, copy) NSArray *preflashText;
@property (nonatomic, copy) NSArray *wifiDetailHidePassword;
@property (nonatomic, copy) NSArray *wifiDetailInstructions;
@property (nonatomic, copy) NSArray *wifiDetailNetwork;
@property (nonatomic, copy) NSArray *wifiDetailNetworkPlaceholder;
@property (nonatomic, copy) NSArray *wifiDetailPassword;
@property (nonatomic, copy) NSArray *wifiDetailPasswordPlaceholder;
@property (nonatomic, copy) NSArray *wifiDetailRememberPassword;
@property (nonatomic, copy) NSArray *wifiDetailSendBlinkUp;
@property (nonatomic, copy) NSArray *wifiDetailShowPassword;
@property (nonatomic, copy) NSArray *wifiSettingsCancel;
@property (nonatomic, copy) NSArray *wifiSettingsClearWirelessConfiguration;
@property (nonatomic, copy) NSArray *wifiSettingsConnectAnImp;
@property (nonatomic, copy) NSArray *wifiSettingsConnectUsingWPS;
@property (nonatomic, copy) NSArray *wifiSettingsDisconnectAnImp;
@property (nonatomic, copy) NSArray *wifiSettingsOtherNetwork;
@property (nonatomic, copy) NSArray *wpsDetailInformation;
@property (nonatomic, copy) NSArray *wpsDetailSendBlinkUp;
@property (nonatomic, copy) NSArray *wpsDetailInstructions;
@property (nonatomic, copy) NSArray *wpsDetailWPSPIN;
@property (nonatomic, copy) NSArray *wpsDetailWPSPINPlaceholder;


//BlinkUpError.strings
@property (nonatomic, copy) NSArray *badApiKey;
@property (nonatomic, copy) NSArray *badFlashPacket;
@property (nonatomic, copy) NSArray *badPlanId;
@property (nonatomic, copy) NSArray *badSetupToken;
@property (nonatomic, copy) NSArray *emptySsid;
@property (nonatomic, copy) NSArray *errorAlertButton;
@property (nonatomic, copy) NSArray *errorAlertMessage;
@property (nonatomic, copy) NSArray *errorAlertTitle;
@property (nonatomic, copy) NSArray *failedGettingPlanIdFromServer;
@property (nonatomic, copy) NSArray *networkErrorDuringImpPoll;
@property (nonatomic, copy) NSArray *setupTokenFailure;
@property (nonatomic, copy) NSArray *statusUpdateTimedOut;

@end
