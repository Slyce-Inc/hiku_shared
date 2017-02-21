//
//  BUStaticNetwork.h
//  BlinkUp
//
//  Created by Brett Park on 2016-05-24.
//  Copyright © 2016 Electric Imp, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BlinkUp/BlinkUp.h>

/*!
 *  Static addressing information for an imp
 *
 *  The initializer is failable and may return nil if the strings are not valid IP addresses
 *  Strings can be validated using [BUNetworkManager isValidIpAddress:@"String"]
 *
 */
@interface BUStaticAddressing : BUNetworkAddressing

/*!
 *  @brief Provide static addressing information with a single DNS server
 *
 *  All strings must be valid IPv4 addresses of form xxx.xxx.xxx.xxx
 *
 *  @param ip      IP address desired for the imp
 *  @param netmask Netmask desired for the imp
 *  @param gateway Gateway desired for the imp
 *  @param dns1    DNS address desired for the imp
 *
 *  @return nil if any strings are not valid IPs, a BUStaticAddressing object if data is valid
 */
- (_Nullable instancetype)initWithIp:(nonnull NSString *)ip netmask:(nonnull NSString *)netmask gateway:(nonnull NSString *)gateway dns1:(nonnull NSString *)dns1;

/*!
 *  @brief Provide static addressing information with two DNS servers
 *
 *  All strings must be valid IPv4 addresses of form xxx.xxx.xxx.xxx
 *
 *  @param ip      IP address desired for the imp
 *  @param netmask Netmask desired for the imp
 *  @param gateway Gateway desired for the imp
 *  @param dns1    DNS address desired for the imp
 *  @param dns2    Second DNS address desired for the imp
 *
 *  @return nil if any strings are not valid IPs. A BUStaticAddressing object if data is valid.
 */
- (_Nullable instancetype)initWithIp:(nonnull NSString *)ip netmask:(nonnull NSString *)netmask gateway:(nonnull NSString *)gateway dns1:(nonnull NSString *)dns1 dns2:(nullable NSString *)dns2 NS_DESIGNATED_INITIALIZER;

/*!
 *  @brief IP address desired for the imp
 */
@property (strong, nonatomic, nonnull, readonly) NSString *ip;

/*!
 *  @brief Netmask desired for the imp
 */
@property (strong, nonatomic, nonnull, readonly) NSString *netmask;

/*!
 *  @brief Gateway desired for the imp
 */
@property (strong, nonatomic, nonnull, readonly) NSString *gateway;

/*!
 *  @brief DNS address desired for the imp
 */
@property (strong, nonatomic, nonnull, readonly) NSString *dns1;

/*!
 *  @brief Second DNS address desired for the imp, or nil if not set
 */
@property (strong, nonatomic, nullable, readonly) NSString *dns2;
@end
