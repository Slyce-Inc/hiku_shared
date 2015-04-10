//
//  BUDeviceInfo.h
//  BlinkUp
//
//  Created by Brett Park on 2014-12-10.
//  Copyright (c) 2014 Electric Imp, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 *  Information about the device
 */
@interface BUDeviceInfo : NSObject
/*!
 *  @brief  The URL of the agent for the device that connected
 */
@property (strong, nonatomic) NSURL *agentURL;
/*!
 *  @brief  The deviceId of the device that connected
 */
@property (strong, nonatomic) NSString *deviceId;
/*!
 *  @brief  The planId of the device that connected
 */
@property (strong, nonatomic) NSString *planId;
/*!
 *  @brief  The date when the device connected to the server
 */
@property (strong, nonatomic) NSDate *verificationDate;
@end
