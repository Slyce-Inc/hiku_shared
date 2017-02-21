//
//  BUNetworkProxy.h
//  BlinkUp
//
//  Created by Brett Park on 2016-05-24.
//  Copyright © 2016 Electric Imp, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  Manually set proxy information for the imp to use
 *
 *  The initializer is failable and may return nil if the server is nil or empty
 */
@interface BUNetworkProxy : NSObject

/*!
 *  @brief Create proxy information for an imp
 *
 *  @param server   Valid IP or Hostname of the proxy server
 *  @param port     Port of the proxy server
 *
 *  @return nil if any parameters are invalid, a BUNetworkProxy if creation was successful
 */
- (_Nullable instancetype)initWithServer:(nonnull NSString *)server port:(uint16_t)port;

/*!
 *  @brief Create proxy information for an imp
 *
 *  If the username or password is nil, neither will be used
 *
 *  @param server   Valid IP or Hostname of the proxy server
 *  @param port     Port of the proxy server
 *  @param username Username used for authentication (optional)
 *  @param password Password used for authentication (optional)
 *
 *  @return nil if any parameters are invalid, a BUNetworkProxy if creation was successful
 */
- (_Nullable instancetype)initWithServer:(nonnull NSString *)server port:(uint16_t)port username:(nullable NSString *)username password:(nullable NSString *)password;

/*!
 *  @brief IP or Hostname of the proxy server
 */
@property (strong, nonatomic, nonnull, readonly) NSString *server;

/*!
 *  @brief Port of the proxy server
 */
@property (assign, nonatomic, readonly) uint16_t port;

/*!
 *  @brief Username used for authentication (optional)
 */
@property (strong, nonatomic, nullable, readonly) NSString *username;

/*!
 *  @brief Password used for authentication (optional)
 */
@property (strong, nonatomic, nullable, readonly) NSString *password;
@end
