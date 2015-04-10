/******************************************************************************
 * - Copyright Electric Imp, Inc. 2013. All rights reserved.
 * - License: <#LICENSE#>
 *
 * <#SUMMARY INFORMATION#>
 */

#import <Foundation/Foundation.h>


@interface BlinkUpNetworkManager : NSObject

//Returns an array of BlinkUpWPSConfig objects
// The first object will be for the currentWifi if one exists
// Any additional wifi configurations will be from previously saved configurations
+ (NSArray *)allWifiConfigs;

// Wifi SSID
// this class method returns the current SSID (name) of the wifi network that the iOS device
// is connected to. It may change if the user changes their network settings. The method may
// also be nil if the user is not connected to any wifi network.
// * It is recommended to use the allWifiConfigs array rather than the individual ssid's
+ (NSString *)currentWifiSSID;


//Return an array of strings containing a list of the SSIDs that have been saved by the user
// This list may contain the currentWifiSSID value.
//  * It is recommended to use the allWifiConfigs array rather than the list of ssid strings
+ (NSArray *)savedWifiSSIDs;

@end



@interface BlinkUpWPSConfig : NSObject
//The pin is the WPS pin for authentication
// pin can be left empty @"" if wps push button configuration is used
@property (nonatomic, copy) NSString *pin;

//Creates the object and sets the WPS pin with the value given
- (id)initWithWPSPin:(NSString *)pin;
@end



@interface BlinkUpWifiConfig : NSObject

//The ssid of the network to connect to
@property (nonatomic, copy) NSString *ssid;

//The password of the network.
// Be sure to check the useSavedPassword property before choosing
// this property or the savedPassword.
// If this property is set, useSavedPassword will be changed to NO
@property (nonatomic, copy) NSString *password;

//If this option is true, a previously stored password will be used
//If this option is false, the password property will be used
// Note: setting the password will automatically change this property to NO
// Note: calling removeConfig with automatically change this property to NO
@property (nonatomic, assign) BOOL useSavedPassword;

//Return the previously saved password (if one exists).
@property (nonatomic, readonly) NSString *savedPassword;

//Initializes the object with the ssid given. Sets the useSavedPassword property to true by default
- (id)initWithExistingSSID:(NSString *)ssid;

//Initializes the object with an ssid and password. By default useSavedPassword is false
- (id)initWithSSID:(NSString *)ssid password:(NSString *)password;

//Standard init does not preset properties
- (id)init;

//Saves the ssid (using the current password property) to storage
// This should not be called on configurations where useSavedPassword is true as it already saved
- (void)saveConfig;

//Remove the ssid (and any saved passwords for that ssid) from storage
// Also sets useSavedPassword to NO
- (void)removeConfig;
@end
