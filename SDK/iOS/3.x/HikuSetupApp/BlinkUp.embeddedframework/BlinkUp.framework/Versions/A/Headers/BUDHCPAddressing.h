//
//  BUDHCPAddressing.h
//  BlinkUp
//
//  Created by Brett Park on 2016-05-24.
//  Copyright © 2016 Electric Imp, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BlinkUp/BlinkUp.h>

/*!
 *  Informs the imp to use DHCP addresses
 *
 *  There are currently no properties to set for this class
 */
@interface BUDHCPAddressing : BUNetworkAddressing
- (instancetype)init;
@end


