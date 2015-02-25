//
//  HKViewController.m
//  HikuSetupTestApp
//
//  Created by Rajan Bala on 10/11/14.
//  Copyright (c) 2014 hiku labs, inc. All rights reserved.
//
#import "HKViewController.h"


#define EMAIL @"<email_address_here>"
#define APPID @"<app_id_here>"
#define SHARED @"<shared_secret_here>"

#define FIELD_WIDTH 260

@interface HKViewController () <HKSetupDelegate>
@property (strong, nonatomic) HKSetupSDK* sdk;
@property (strong, nonatomic) UIButton* buttonStart;
@property (strong, nonatomic) UIButton* buttonLogout;
@property (strong, nonatomic) UIButton* buttonTips;
@property (strong, nonatomic) NSArray *viewControllerTypes;
@end

@implementation HKViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.view.backgroundColor = [UIColor whiteColor];

    _viewControllerTypes = @[@"Modal", @"Push"];

    float y = 60;

    float width = self.view.frame.size.width;

    float x = (width - FIELD_WIDTH) /2;
    width = FIELD_WIDTH;

    float height = 25;

    UIPickerView *presentationStylePicker = [[UIPickerView alloc] initWithFrame:CGRectMake(10, y, [UIScreen mainScreen].bounds.size.width - 20, height)];
    presentationStylePicker.dataSource = self;
    presentationStylePicker.delegate = self;
    presentationStylePicker.showsSelectionIndicator = YES;
    [presentationStylePicker selectRow:self.selectedPickerRow inComponent:0 animated:YES];
    self.presentationStylePicker = presentationStylePicker;

    [self.view addSubview:presentationStylePicker];

    y += presentationStylePicker.frame.size.height + 10;

    self.buttonStart = [self createButton:@"Start Setup" selector:@selector(buttonHandler:)];
    self.buttonStart.frame = CGRectMake(x, y, width, height);

    [self.view addSubview:self.buttonStart];

    y += height + 10;

    self.buttonLogout = [self createButton:@"Logout" selector:@selector(buttonHandler:)];
    self.buttonLogout.frame = CGRectMake(x, y, width, height);

    [self.view addSubview:self.buttonLogout];

    y += height + 10;

    self.buttonTips = [self createButton:@"Tips" selector:@selector(buttonHandler:)];
    self.buttonTips.frame = CGRectMake(x, y, width, height);

    [self.view addSubview:self.buttonTips];

	// Do any additional setup after loading the view, typically from a nib.
}

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
    return _viewControllerTypes.count;
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    return _viewControllerTypes[row];
}

-(void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
    if ([_viewControllerTypes[row] isEqualToString:@"Modal"]) {
        HKViewController *viewController = [[HKViewController alloc] init];
        [viewController.presentationStylePicker selectRow:0 inComponent:0 animated:YES];
        viewController.pickedPresentationStyle = SDKHKPRESENTATION_MODAL;
        [UIApplication sharedApplication].delegate.window.rootViewController = nil;
        [UIApplication sharedApplication].delegate.window.rootViewController = viewController;
    }
    else if ([_viewControllerTypes[row] isEqualToString:@"Push"]) {
        HKViewController *viewController = [[HKViewController alloc] init];
        viewController.selectedPickerRow = 1;
        viewController.pickedPresentationStyle = SDKHKPRESENTATION_PUSH;
        UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:viewController];
        [UIApplication sharedApplication].delegate.window.rootViewController = navigationController;
    }
}

- (UIButton *) createButton:(NSString *)title selector:(SEL)selector
{
    UIButton* button = [UIButton buttonWithType:UIButtonTypeSystem];

    [button setTitle:title forState:UIControlStateNormal];
    [button addTarget:self action:selector forControlEvents:UIControlEventTouchUpInside];
    return button;
}

- (IBAction) buttonHandler:(id)sender
{
    if( sender == self.buttonLogout )
    {
        [_sdk logoutUser];
    }
    else if( sender == self.buttonStart )
    {
        [_sdk startSetup:[UIApplication sharedApplication].delegate.window.rootViewController withPresentationStyle:_pickedPresentationStyle]; // call this to start the process
    }
    else if (sender == self.buttonTips)
    {
        [_sdk launchTipsFlow:[UIApplication sharedApplication].delegate.window.rootViewController withPresentationStyle:_pickedPresentationStyle];
    }
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];

    _sdk = [[HKSetupSDK alloc] initWithAppId:APPID shared:SHARED email:EMAIL];
    _sdk.delegate = self;
}

- (void) userCancelledSetup:(HKSetupSDK *)sdk
{
    NSLog(@"User Cancelled Setup!");
}

- (void) applicationAuthorizationStatus:(BOOL)success sdk:(HKSetupSDK *)sdk
{
    NSLog(@"Application authorization status: %@", success ? [NSString stringWithFormat:@"Success! App token is: %@", [sdk getApplicationTokenForUser]] : @"Failed");
}

- (void) userAuthenticationStatus:(BOOL)success sdk:(HKSetupSDK *)sdk
{
    NSLog(@"User authentication status: %@", success?@"Success" : @"Failed");
}

- (void) deviceSetupStatus:(BOOL)success sdk:(HKSetupSDK *)sdk
{
    NSLog(@"Device Setup Status: %@",success?@"Success":@"Failed");
}

// Call the following function to explicitly logout a user

- (void)logoutUser
{
    [_sdk logoutUser];
}

// Call the following function to explicitly initiate the tips flow for a user

- (void)launchTipsFlow
{
    [_sdk launchTipsFlow:self];
}

@end
