//
//  BUHelper.h
//  BlinkUp
//
//  Created by Brett Park on 2016-10-13.
//  Copyright © 2016 Electric Imp, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 Helper methods when performing BlinkUps
 */
@interface BUHelper : NSObject

/**
 During BlinkUp, the rotation of the application and the status bar may become
 out of sync with the device orientation. In order to fix the orientation and status
 bar this method can be called in an attempt to correct both. It works by quickly 
 presenting an empty view controller with a clear background on the view controller
 passed in. It is then immediatly dismissed which causes the presenting view controller
 to be redrawn in the correct orientation. It is important that this may cause the
 presenting view controllers viewDidAppear and other methods to be called. This method
 works best if called after shouldAutorotate has been set to true (if it was altered for
 BlinkUp).

 @param presentingViewController The view that is out of rotation or has the status bar
            in the incorrect orientation
 */
+(void) fixRotationForViewController:(UIViewController *) presentingViewController;



/**
 This method can be used in the view controller, navigation controller, root view controller
 or other container view controllers to retrieve if BlinkUp should allow or prevent autorotation.
 It is recomended to override the shouldAutorotate function of all view controllers that are in
 charge of rotation when a BlinkUp occurs.

 @return True if the interface should rotate, false is a flash is occurring
 */
+(BOOL) shouldAutorotate;
@end
