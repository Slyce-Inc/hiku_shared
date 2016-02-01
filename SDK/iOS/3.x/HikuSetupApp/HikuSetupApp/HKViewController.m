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

#define EMAIL_PLACEHOLDER @"Enter email"
#define PASSWORD_PLACEHOLDER @"Enter password"
#define FIELD_WIDTH 260

@interface HKViewController () <HKSetupDelegate, UITextFieldDelegate>
@property (strong, nonatomic) HKSetupSDK* sdk;
@property (nonatomic) BOOL shouldHideStatusBar;
@property (strong, nonatomic) UIButton* buttonToggleStatusBar;
@property (strong, nonatomic) UIButton* createOrLogin;
@property (strong, nonatomic) UIButton* buttonStartWithLogo;
@property (strong, nonatomic) UIButton* buttonStartNoLogo;
@property (strong, nonatomic) UIButton* buttonLogout;
@property (strong, nonatomic) UIButton* buttonTips;
@property (strong, nonatomic) UITextField* emailField;
@property (strong, nonatomic) UITextField* passwordField;
@property (strong, nonatomic) UISwitch *emailOffersSwitch;
@property (strong, nonatomic) UISwitch *callbackSwitch;
@property (strong, nonatomic) UISwitch *modalSwitch;
@property (strong, nonatomic) UISwitch *pushSwitch;
@end

@implementation HKViewController

- (void)hideKeyboard:(id)sender
{
    [self.view endEditing:YES];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [self hideKeyboard:nil];
    return YES;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    UIScrollView* scrollView = [[UIScrollView alloc] initWithFrame:self.view.frame];
    scrollView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleTopMargin;

    UITapGestureRecognizer* gestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(hideKeyboard:)];
    [scrollView addGestureRecognizer:gestureRecognizer];

    self.view.backgroundColor = [UIColor whiteColor];
    self.edgesForExtendedLayout = UIRectEdgeNone;

    float y = (self.pickedPresentationStyle == SDKHKPRESENTATION_MODAL ? 80 : 16);

    float width = self.view.frame.size.width;

    float x = (width - FIELD_WIDTH) /2;
    width = FIELD_WIDTH;

    float height = 25;

    UILabel *callbackLabel = [[UILabel alloc] initWithFrame:CGRectMake(x, y, 175, height)];
    callbackLabel.text = @"Show received callbacks";
    callbackLabel.textColor = [UIColor colorWithRed:(0/255.0) green:(110/255.0) blue:(1/255.0) alpha:(255/255.0)];
    callbackLabel.font = [UIFont systemFontOfSize:14];

    [scrollView addSubview:callbackLabel];

    self.callbackSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(callbackLabel.frame.origin.x + callbackLabel.frame.size.width + 35, y - 3, 0, 0)];
    self.callbackSwitch.onTintColor = [UIColor colorWithRed:(0/255.0) green:(110/255.0) blue:(1/255.0) alpha:(255/255.0)];
    self.callbackSwitch.on = YES;

    [scrollView addSubview:self.callbackSwitch];

    y += height + 10;

    UILabel *modalLabel = [[UILabel alloc] initWithFrame:CGRectMake(x, y, 175, height)];
    modalLabel.text = @"Modally present screens";
    modalLabel.textColor = [UIColor colorWithRed:(0/255.0) green:(110/255.0) blue:(1/255.0) alpha:(255/255.0)];
    modalLabel.font = [UIFont systemFontOfSize:14];

    [scrollView addSubview:modalLabel];

    self.modalSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(modalLabel.frame.origin.x + modalLabel.frame.size.width + 35, y - 3, 0, 0)];
    [self.modalSwitch addTarget:self action:@selector(togglePresentationStyle:) forControlEvents:UIControlEventValueChanged];
    self.modalSwitch.onTintColor = [UIColor colorWithRed:(0/255.0) green:(110/255.0) blue:(1/255.0) alpha:(255/255.0)];
    self.modalSwitch.on = (self.pickedPresentationStyle == SDKHKPRESENTATION_MODAL);

    [scrollView addSubview:self.modalSwitch];

    y += height + 10;

    UILabel *pushLabel = [[UILabel alloc] initWithFrame:CGRectMake(x, y, 175, height)];
    pushLabel.text = @"Push screens";
    pushLabel.textColor = [UIColor colorWithRed:(0/255.0) green:(110/255.0) blue:(1/255.0) alpha:(255/255.0)];
    pushLabel.font = [UIFont systemFontOfSize:14];

    [scrollView addSubview:pushLabel];

    self.pushSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(modalLabel.frame.origin.x + modalLabel.frame.size.width + 35, y - 3, 0, 0)];
    [self.pushSwitch addTarget:self action:@selector(togglePresentationStyle:) forControlEvents:UIControlEventValueChanged];
    self.pushSwitch.onTintColor = [UIColor colorWithRed:(0/255.0) green:(110/255.0) blue:(1/255.0) alpha:(255/255.0)];
    self.pushSwitch.on = (self.pickedPresentationStyle == SDKHKPRESENTATION_PUSH);

    [scrollView addSubview:self.pushSwitch];

    y += height + 10;

    self.shouldHideStatusBar = [UIApplication sharedApplication].statusBarHidden;
    self.buttonToggleStatusBar = [self createButton:@"Toggle status bar" selector:@selector(buttonHandler:)];
    self.buttonToggleStatusBar.frame = CGRectMake(x, y, width, height);
    self.buttonToggleStatusBar.backgroundColor = [UIColor colorWithRed:(0/255.0) green:(110/255.0) blue:(1/255.0) alpha:(255/255.0)];

    [scrollView addSubview:self.buttonToggleStatusBar];

    y += height + 30;

    self.emailField = [[UITextField alloc] initWithFrame:CGRectMake(x, y, width, height)];
    self.emailField.delegate = self;
    self.emailField.layer.cornerRadius = 5;
    self.emailField.layer.borderWidth = 1.0;
    self.emailField.layer.borderColor = [UIColor colorWithRed:(58/255.0) green:(144/255.0) blue:(222/255.0) alpha:0.5].CGColor;
    self.emailField.placeholder = EMAIL_PLACEHOLDER;
    self.emailField.textAlignment = NSTextAlignmentCenter;
    self.emailField.autocapitalizationType = UITextAutocapitalizationTypeNone;
    self.emailField.autocorrectionType = UITextAutocorrectionTypeNo;

    [scrollView addSubview:self.emailField];

    y += height + 10;

    self.passwordField = [[UITextField alloc] initWithFrame:CGRectMake(x, y, width, height)];
    self.passwordField.delegate = self;
    self.passwordField.layer.cornerRadius = 5;
    self.passwordField.layer.borderWidth = 1.0;
    self.passwordField.layer.borderColor = [UIColor colorWithRed:(58/255.0) green:(144/255.0) blue:(222/255.0) alpha:0.5].CGColor;
    self.passwordField.placeholder = PASSWORD_PLACEHOLDER;
    self.passwordField.textAlignment = NSTextAlignmentCenter;
    self.passwordField.secureTextEntry = YES;

    [scrollView addSubview:self.passwordField];

    y += height + 10;

    UILabel *emailOffersLabel = [[UILabel alloc] initWithFrame:CGRectMake(x, y, 175, height)];
    emailOffersLabel.text = @"Show email offers popup";
    emailOffersLabel.textColor = [UIColor colorWithRed:(58/255.0) green:(144/255.0) blue:(222/255.0) alpha:(255/255.0)];
    emailOffersLabel.font = [UIFont systemFontOfSize:14];

    [scrollView addSubview:emailOffersLabel];

    self.emailOffersSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(emailOffersLabel.frame.origin.x + emailOffersLabel.frame.size.width + 35, y - 3, 0, 0)];
    [self.emailOffersSwitch addTarget:self action:@selector(toggleEmailOffers:) forControlEvents:UIControlEventValueChanged];
    self.emailOffersSwitch.onTintColor = [UIColor colorWithRed:(58/255.0) green:(144/255.0) blue:(222/255.0) alpha:(255/255.0)];
    self.emailOffersSwitch.on = YES;

    [scrollView addSubview:self.emailOffersSwitch];

    y += height + 10;

    self.createOrLogin = [self createButton:@"Create or login to an account\n(bypasses setup)" selector:@selector(buttonHandler:)];
    self.createOrLogin.frame = CGRectMake(x, y, width, height * 2);
    self.createOrLogin.backgroundColor = [UIColor colorWithRed:(58/255.0) green:(144/255.0) blue:(222/255.0) alpha:(255/255.0)];

    [scrollView addSubview:self.createOrLogin];

    y += (height * 2) + 10;

    self.buttonStartNoLogo = [self createButton:@"Start Setup" selector:@selector(buttonHandler:)];
    self.buttonStartNoLogo.frame = CGRectMake(x, y, width, height);
    self.buttonStartNoLogo.backgroundColor = [UIColor colorWithRed:(58/255.0) green:(144/255.0) blue:(222/255.0) alpha:(255/255.0)];

    [scrollView addSubview:self.buttonStartNoLogo];

    /*
    y += height + 10;

    self.buttonStartWithLogo = [self createButton:@"Start Setup (w/ Partner Logo)" selector:@selector(buttonHandler:)];
    self.buttonStartWithLogo.frame = CGRectMake(x, y, width, height);
    self.buttonStartWithLogo.backgroundColor = [UIColor colorWithRed:(58/255.0) green:(144/255.0) blue:(222/255.0) alpha:(255/255.0)];

    [scrollView addSubview:self.buttonStartWithLogo];
     */

    y += height + 30;

    self.buttonLogout = [self createButton:@"Logout" selector:@selector(buttonHandler:)];
    self.buttonLogout.frame = CGRectMake(x, y, width, height);
    self.buttonLogout.backgroundColor = [UIColor colorWithRed:(128/255.0) green:(0/255.0) blue:(0/255.0) alpha:(255/255.0)];

    [scrollView addSubview:self.buttonLogout];

    y += height + 10;

    self.buttonTips = [self createButton:@"Tips" selector:@selector(buttonHandler:)];
    self.buttonTips.frame = CGRectMake(x, y, width, height);
    self.buttonTips.backgroundColor = [UIColor colorWithRed:(84/255.0) green:(35/255.0) blue:(126/255.0) alpha:(255/255.0)];

    [scrollView addSubview:self.buttonTips];

    y += height + 60;

	// Do any additional setup after loading the view, typically from a nib.

    scrollView.contentSize = CGSizeMake(scrollView.contentSize.width, y);
    [self.view addSubview:scrollView];
}

- (void)toggleEmailOffers:(id)sender
{
    [_sdk setValue:[NSNumber numberWithBool:[sender isOn]] forKey:@"show_email_offers_dialog"];
}

- (void)pushMode
{
    HKViewController *viewController = [[HKViewController alloc] init];
    viewController.pickedPresentationStyle = SDKHKPRESENTATION_PUSH;
    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:viewController];
    [UIApplication sharedApplication].delegate.window.rootViewController = nil;
    [UIApplication sharedApplication].delegate.window.rootViewController = navigationController;
}

- (void)modalMode
{
    HKViewController *viewController = [[HKViewController alloc] init];
    viewController.pickedPresentationStyle = SDKHKPRESENTATION_MODAL;
    [UIApplication sharedApplication].delegate.window.rootViewController = nil;
    [UIApplication sharedApplication].delegate.window.rootViewController = viewController;
}

- (void)togglePresentationStyle:(id)sender
{
    if (self.modalSwitch == sender) {
        [self.pushSwitch setOn:![sender isOn] animated:YES];

        if ([sender isOn])
            [self modalMode];
        else
            [self pushMode];
    }
    else {
        [self.modalSwitch setOn:![sender isOn] animated:YES];

        if ([sender isOn])
            [self pushMode];
        else
            [self modalMode];
    }

}

- (UIButton *) createButton:(NSString *)title selector:(SEL)selector
{
    UIButton* button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.layer.cornerRadius = 5;
    button.titleLabel.font = [UIFont systemFontOfSize:14];
    button.titleLabel.textColor = [UIColor whiteColor];
    button.titleLabel.numberOfLines = 0;
    button.titleLabel.textAlignment = NSTextAlignmentCenter;
    [button setTitle:title forState:UIControlStateNormal];
    [button addTarget:self action:selector forControlEvents:UIControlEventTouchUpInside];
    return button;
}

- (IBAction) buttonHandler:(id)sender
{
    if (sender == self.buttonLogout)
    {
        [_sdk logoutUser];
    }
    else if (sender == self.createOrLogin)
    {
        [_sdk loginUserWithEmail:self.emailField.text password:self.passwordField.text];
    }
    else if (sender == self.buttonStartNoLogo)
    {
        if (![self.emailField.text isEqualToString:@""] && ![self.emailField.text isEqualToString:EMAIL_PLACEHOLDER])
            _sdk.email = self.emailField.text;

        [_sdk startSetup:[UIApplication sharedApplication].delegate.window.rootViewController withPresentationStyle:_pickedPresentationStyle]; // call this to start the process
    }
    else if (sender == self.buttonStartWithLogo)
    {
        if (![self.emailField.text isEqualToString:@""] && ![self.emailField.text isEqualToString:EMAIL_PLACEHOLDER])
            _sdk.email = self.emailField.text;

        _sdk.partner_logo = [UIImage imageNamed:@"genericlogo"];
        [_sdk setValue:[UIColor redColor] forKey:@"navigation_bar_color"];
        [_sdk startSetup:[UIApplication sharedApplication].delegate.window.rootViewController withPresentationStyle:_pickedPresentationStyle]; // call this to start the process
    }
    else if (sender == self.buttonTips)
    {
        [_sdk launchTipsFlow:[UIApplication sharedApplication].delegate.window.rootViewController withPresentationStyle:_pickedPresentationStyle];
    }
    else if (sender == self.buttonToggleStatusBar) {
        self.shouldHideStatusBar = !self.shouldHideStatusBar;
        _sdk.show_status_bar = !self.shouldHideStatusBar;
        [self setNeedsStatusBarAppearanceUpdate];
    }
}

- (BOOL)prefersStatusBarHidden {
    return self.shouldHideStatusBar;
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
    _sdk.show_status_bar = !self.shouldHideStatusBar;
    _sdk.delegate = self;
}

- (void)logAndShowAlert:(NSString *)message
{
    NSLog(@"%@", message);

    if (self.callbackSwitch.on) {
        UIButton *callbackMessage = [[UIButton alloc] initWithFrame:CGRectMake(5, 50, [UIApplication sharedApplication].keyWindow.frame.size.width - 10, 175.0)];
        callbackMessage.clipsToBounds = YES;
        callbackMessage.layer.cornerRadius = 3;
        callbackMessage.backgroundColor = [UIColor colorWithWhite:0 alpha:0.75];
        callbackMessage.contentMode = UIViewContentModeCenter;
        callbackMessage.titleLabel.textAlignment = NSTextAlignmentCenter;
        callbackMessage.titleLabel.textColor = [UIColor whiteColor];
        callbackMessage.titleLabel.numberOfLines = 0;
        callbackMessage.titleLabel.font = [UIFont systemFontOfSize:14];
        [callbackMessage addTarget:self action:@selector(fadeOut:) forControlEvents:UIControlEventTouchUpInside];

        [[UIApplication sharedApplication].keyWindow addSubview:callbackMessage];

        [callbackMessage setTitle:[message stringByAppendingString:@"\n\n(Tap to dismiss)"] forState:UIControlStateNormal];

        [self fadeIn:callbackMessage];
    }
}

- (void)userCompletedTutorial:(HKSetupSDK *)sdk
{
    [self logAndShowAlert:@"User completed the tutorial"];
}

- (void)userCancelledSetup:(HKSetupSDK *)sdk
{
    [self logAndShowAlert:@"User cancelled setup"];
}

- (void)applicationAuthorizationStatus:(BOOL)success sdk:(HKSetupSDK *)sdk
{
    [self logAndShowAlert:[NSString stringWithFormat:@"Application authorization status: %@", success ? [NSString stringWithFormat:@"Success\n\nApp token is: %@", [sdk getApplicationTokenForUser]] : @"Failed"]];
}

- (void)userAuthenticationStatus:(BOOL)success sdk:(HKSetupSDK *)sdk
{
    [self logAndShowAlert:[NSString stringWithFormat:@"User authentication status: %@", success ? @"Success" : @"Failed"]];
}

- (void)deviceSetupStatus:(BOOL)success sdk:(HKSetupSDK *)sdk
{
    [self logAndShowAlert:[NSString stringWithFormat:@"Device setup status: %@",success ? @"Success" : @"Failed"]];
}

// Call the following function to explicitly logout a user

- (void)logoutUser
{
    [_sdk logoutUser];
}

- (void)userLoggedOut:(HKSetupSDK *)sdk
{
    [self logAndShowAlert:[NSString stringWithFormat:@"User logged out"]];
}

// Call the following function to explicitly initiate the tips flow for a user

- (void)launchTipsFlow
{
    [_sdk launchTipsFlow:self];
}

- (void)fadeIn:(UIView *)view
{
    view.alpha = 0;

    [UIView animateWithDuration:0.5 delay:0.0 options:UIViewAnimationCurveEaseIn | UIViewAnimationOptionAllowUserInteraction animations:^{
        view.alpha = 1;
    } completion:nil];
}

- (void)fadeOut:(id)sender
{
    __block UIView *view = (UIView *)sender;
    [UIView animateWithDuration:0.5 animations:^{
        view.alpha = 0;
    } completion: ^(BOOL finished) {
        if (finished)
            [view removeFromSuperview];
    }];
}

@end
