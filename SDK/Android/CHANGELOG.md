# Change Log
---
## 3.0.1
- Updated sdk sample app

## 3.0.0
- Updated Blinkup videos and flows.
- Updated Mixpanel events.
- Added Crashlytics

#### [2.1.0.4]
2015-Jul-09
- fixes layout for the password request link in the login screen
- turns off auto-brightness and increases brightness for Blinkup
- 404 fix (on the Blinkup server side)

Note: *2.1.0.4 was the last version built under Eclipse*

#### 2.1.0.1
- Button style change for Lollipop devices
- Help link for Apple Airport
- Added Mixpanel AppRelease property
- Minor padding changes in UI elements for some screens where there is a lot of text

#### 2.1.0
- Added a check for Internet connectivity
- Integrated Mixpanel analytics
- Revised hiku setup screens
- Updated blinkup library
- Added countdown timer
- Removed filtering of 5 GHz networks.

#### 2.0.27
- Fixed padding on the existing email account and password screen so that long text doesn’t overlap with UI buttons.
- Fixed padding on the wifi SSID and password screen.
- Increased the Blinkup timeout from 30 to 40 seconds to match what is used for iOS.
- Added ‘(Android)’ to the email subjects to help track the devices creating support tickets.
- Added a server error msg to the Flurry event log when logging certain server errors.
- Increased the Flurry session time from 10 to 60 seconds so that Blinkup activity is kept with the rest of the session activity.
- Fixed a bug in the timer checking for a progressing countdown if the user hits back.

[2.1.0.4]: https://github.com/hikuinc/hiku_shared/tree/master/SDK/Android/repo/us/hiku/sdk/hiku-sdk
