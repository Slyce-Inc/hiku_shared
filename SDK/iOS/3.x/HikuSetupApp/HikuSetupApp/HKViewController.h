//
//  HKViewController.h
//  HikuSetupTestApp
//
//  Created by Rajan Bala on 10/11/14.
//  Copyright (c) 2014 hiku labs, inc. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <HKSetupSDKFramework/include/HKSetupSDK/HKSetupSDK.h>


@interface HKViewController : UIViewController <UIPickerViewDataSource, UIPickerViewDelegate>

@property (nonatomic) NSInteger selectedPickerRow;
@property (strong, nonatomic) UIPickerView *presentationStylePicker;
@property (nonatomic) SDKHKPresentationStyle pickedPresentationStyle;

@end
