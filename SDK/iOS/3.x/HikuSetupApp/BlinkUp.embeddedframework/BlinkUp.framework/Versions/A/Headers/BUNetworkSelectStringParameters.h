//
//  BUNetworkSelectStringParameters.h
//  BlinkUp
//
//  Created by Brett Park on 2014-12-12.
//  Copyright (c) 2014 Electric Imp, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
   Runtime string parameters

   Collection of arrays that can be used for parameters based on NSString format
    in the BlinkUpSDK.strings localization file. See the [Text Customization](../docs/text%20customization.html) guide.

    // Example .strings text
    "GlobalFooter" = @"%@ is logged in";

    // Example setting of parameter for the format string
    networkSelectController.stringParams.globalFooter = @[@"Joe User"];
 */
@interface BUNetworkSelectStringParameters : NSObject

///---------------------------------------------------------------------------
/// @name Global parameters
///---------------------------------------------------------------------------

/// Parameters for the title that appears in the user interface
@property (nonatomic, copy) NSArray *globalTitle;

/// Parameters for the footer that appears in the user interface
@property (nonatomic, copy) NSArray *globalFooter;

///---------------------------------------------------------------------------
/// @name Wifi Details Screen parameters
///---------------------------------------------------------------------------

/// Parameters for password hiding label on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailHidePassword;

/// Parameters for instructions text area on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailInstructions;

/// Parameters for network label on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailNetwork;

/// Parameters for network placeholder on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailNetworkPlaceholder;

/// Parameters for password label on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailPassword;

/// Parameters for password placeholder on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailPasswordPlaceholder;

/// Parameters for remember password label on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailRememberPassword;

/// Parameters for send BlinkUp button on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailSendBlinkUp;

/// Parameters for show password label on the Wifi details screen
@property (nonatomic, copy) NSArray *wifiDetailShowPassword;

///---------------------------------------------------------------------------
/// @name Network Settings Screen parameters
///---------------------------------------------------------------------------

/// Parameters for cancel button on the Wifi setting screen
@property (nonatomic, copy) NSArray *wifiSettingsCancel;

/// Parameters for clear wireless button on the Wifi setting screen
@property (nonatomic, copy) NSArray *wifiSettingsClearWirelessConfiguration;

/// Parameters for connect a device label on the Wifi setting screen
@property (nonatomic, copy) NSArray *wifiSettingsConnectADevice;

/// Parameters for connect using wps label on the Wifi setting screen
@property (nonatomic, copy) NSArray *wifiSettingsConnectUsingWPS;

/// Parameters for disconnect a device label on the Wifi setting screen
@property (nonatomic, copy) NSArray *wifiSettingsDisconnectADevice;

/// Parameters for other networks label on the Wifi setting screen
@property (nonatomic, copy) NSArray *wifiSettingsOtherNetwork;

///---------------------------------------------------------------------------
/// @name WPS Details Screen parameters
///---------------------------------------------------------------------------

/// Parameters for detail information text area on the WPS details screen
@property (nonatomic, copy) NSArray *wpsDetailInformation;

/// Parameters for send BlinkUp button on the WPS details screen
@property (nonatomic, copy) NSArray *wpsDetailSendBlinkUp;

/// Parameters for instructions text area on the WPS details screen
@property (nonatomic, copy) NSArray *wpsDetailInstructions;

/// Parameters for pin label on the WPS details screen
@property (nonatomic, copy) NSArray *wpsDetailWPSPIN;

/// Parameters for pin placeholder on the WPS details screen
@property (nonatomic, copy) NSArray *wpsDetailWPSPINPlaceholder;
@end
