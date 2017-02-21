//
//  BUSDKFeatures.h
//  BlinkUp
//
//  Created by Brett Park on 2015-10-27.
//  Copyright © 2015 Electric Imp, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  Enable extra features
 *
 *  This class is used to enable client specific features. Enabling them here makes
 *  them accessible SDK wide.
 */
@interface BUSDKFeatures : NSObject

/*!
 *  @brief Enabled extra feature SDK wide
 *
 *  If you require extra features when using the SDK, you can enable them here
 *  with the feature codes provided by Electric Imp. The feature codes are
 *  specific to your ApiKey. During initial configuration, it is good practice
 *  to examine the return list to ensure all the features you will change are
 *  enabled. If this method is called multiple times, each successive call will
 *  overwrite any previously enabled features.
 *
 *  To clear all features, pass in an empty featureCodes array.
 *
 *  @param apiKey       The APIKey assigned to you from Electric Imp
 *  @param featureCodes All of the features codes that should be enabled
 *
 *  @return The list of feature names that were enabled
 */
+ (NSArray <NSString *> *_Nonnull)enableFeaturesWithApiKey:(NSString *_Nonnull)apiKey featureCodes:(NSArray  <NSString *> *_Nonnull)featureCodes;

/*!
 *  @brief Check if a feature has been enabled
 *
 *  @param featureName Name of the feature to check
 *
 *  @return True if the feature is enabled
 */
+ (BOOL)isFeatureEnabled:(NSString *_Nonnull)featureName;

#pragma mark - Private Cloud Feature

/*!
 *  @brief  The hostname of the private cloud
 *
 *  This value is used as the hostname when retrieving plans, tokens, and
 *  BlinkUp results. Nil is returned by default, which indicates that
 *  the API should use the default Electric Imp URL. To enable this option,
 *  you must provide your feature access key.
 *
 *  Note: This feature must be enabled with a FeatureCode
 *
 *  @return Nil if not set or the override base URL string
 */
+ (NSString *_Nullable)privateCloudHost;

/*!
 *  @brief  The common name of the anchoring certificate for the privateCloudHost
 *
 *  When connecting to the server, the API will validate that the anchoring
 *  certificate (the root) has a common name that matches this string in order
 *  to provide an extra layer of security. If the value is nil, the anchor
 *  certificate will not be checked.
 *
 *  Note: This feature must be enabled with a FeatureCode
 *
 *  @return Nil if any cert is allowed, or the value that must match the cert
 */
+ (NSString *_Nullable)anchorCertCN;

/*!
 *  @brief  Set a custom cloud server and the server's anchor certificate name
 *
 *  If your device is connecting to a private cloud, you can set the host of
 *  your private cloud. Setting the CN of the anchor certificate adds an
 *  additional layer of security to the API calls. If the privateCloudHost is
 *  nil, the default server will be used. If the anchorCertCN is nil, any
 *  certificate trusted by the system will be valid.
 *
 *  Note: This feature must be enabled with a FeatureCode
 *
 *  @param privateCloudHost Server host to connect to
 *  @param anchorCertCN     Common Name of the servers anchor certificate
 */
+ (void)setPrivateCloudHost:(NSString *_Nullable)privateCloudHost anchorCertCN:(NSString *_Nullable)anchorCertCN;

@end
