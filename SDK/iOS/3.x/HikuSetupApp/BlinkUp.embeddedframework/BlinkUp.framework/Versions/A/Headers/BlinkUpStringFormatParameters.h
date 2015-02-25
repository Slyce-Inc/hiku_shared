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
@interface BlinkUpStringFormatParameters: NSObject

//BlinkUpSDK.strings
@property (nonatomic, strong) NSArray * globalTitle;
@property (nonatomic, strong) NSArray * globalFooter;
@property (nonatomic, strong) NSArray * interstitialContinue;
@property (nonatomic, strong) NSArray * preflashText;
@property (nonatomic, strong) NSArray * wifiDetailInstructions;
@property (nonatomic, strong) NSArray * wifiDetailNetwork;
@property (nonatomic, strong) NSArray * wifiDetailNetworkPlaceholder;
@property (nonatomic, strong) NSArray * wifiDetailPassword;
@property (nonatomic, strong) NSArray * wifiDetailPasswordPlaceholder;
@property (nonatomic, strong) NSArray * wifiDetailRememberPassword;
@property (nonatomic, strong) NSArray * wifiDetailSendBlinkUp;
@property (nonatomic, strong) NSArray * wifiSettingsCancel;
@property (nonatomic, strong) NSArray * wifiSettingsClearWirelessConfiguration;
@property (nonatomic, strong) NSArray * wifiSettingsConnectAnImp;
@property (nonatomic, strong) NSArray * wifiSettingsConnectUsingWPS;
@property (nonatomic, strong) NSArray * wifiSettingsDisconnectAnImp;
@property (nonatomic, strong) NSArray * wifiSettingsOtherNetwork;
@property (nonatomic, strong) NSArray * wpsDetailInformation;
@property (nonatomic, strong) NSArray * wpsDetailSendBlinkUp;
@property (nonatomic, strong) NSArray * wpsDetailInstructions;
@property (nonatomic, strong) NSArray * wpsDetailWPSPIN;
@property (nonatomic, strong) NSArray * wpsDetailWPSPINPlaceholder;


//BlinkUpError.strings
@property (nonatomic, strong) NSArray * badApiKey;
@property (nonatomic, strong) NSArray * badFlashPacket;
@property (nonatomic, strong) NSArray * badPlanId;
@property (nonatomic, strong) NSArray * badSetupToken;
@property (nonatomic, strong) NSArray * emptySsid;
@property (nonatomic, strong) NSArray * errorAlertButton;
@property (nonatomic, strong) NSArray * errorAlertMessage;
@property (nonatomic, strong) NSArray * errorAlertTitle;
@property (nonatomic, strong) NSArray * failedGettingPlanIdFromServer;
@property (nonatomic, strong) NSArray * networkErrorDuringImpPoll;
@property (nonatomic, strong) NSArray * setupTokenFailure;
@property (nonatomic, strong) NSArray * statusUpdateTimedOut;

@end