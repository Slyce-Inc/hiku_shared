//
//  BlinkUpErrors.h
//  BlinkUp
//
//  Created by BrettPark on 2014-08-12.
//  Copyright (c) 2014 Electric Imp, Inc. All rights reserved.
//

#pragma once

extern NSString *const BlinkUpErrorDomain;

// Please use the enumerations for error matching.
// The comment string listed after each error is the .string key for the
//  NSLocalizedDescription of the error if you would like to override the message
// Conversion from older error codes is provided in the Migration.markdown
//  documentation that can be found with the SDK
typedef NS_ENUM (NSInteger, BlinkUpError) {
  //Common errors for users
  BlinkUpErrorNetworkError = 10,        // NetworkErrorDuringImpPol
  BlinkUpErrorStatusUpdateTimedOut = 11,  // StatusUpdateTimedOut

  //Less common errors
  BlinkUpErrorFlashPacketInvalid = 20,     // BadFlashPacket
  BlinkUpErrorPasswordAlreadySaved = 51, //SaveWifiConfigPasswordError
  BlinkUpErrorPlanIDInvalid = 30,           // BadPlanId
  BlinkUpErrorPlanIDRetrievalFailed = 31,  // FailedGettingPlanIdFromServer
  BlinkUpErrorSetupTokenInvalid = 41,    // BadSetupToken
  BlinkUpErrorSetupTokenRetrievalFailed = 42, // SetupTokenFailure
  BlinkUpErrorSSIDNotSet = 60,              // EmptySsid

  //Even less common errors
  BlinkUpErrorAPIKeyIsInvalid = 70,      // BadApiKey
  BlinkUpErrorMIMETypeInvalid = 80,     // BadMimeType
  BlinkUpErrorPasswordSaveFailed = 52,

  //SDK Configuration error
  BlinkUpErrorBundleNotCopied = 110,
  BlinkUpErrorObjCFlagNotSet = 111,
};
