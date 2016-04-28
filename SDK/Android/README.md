![alt text](http://app-staging.hiku.us/static/img/logo.png "hiku")
# hiku SDK for Android

## Background
The hiku Android SDK enables 3rd party applications to incorporate the hiku device setup and onboarding experiences into their own mobile applications. Connection is established via the “BlinkUp” process: a flash emanates from the smartphone screen to communicate with the hiku device and thereby pair it with a local Wi-Fi network. In the past, only hiku’s native iOS and Android applications could setup a hiku device and connect it to a Wi-Fi network.



## Installation

### Prerequisites
Base functionality requires:
Android 4.0, SDK Level 14+

Enhanced Wi-Fi configuration support requires: Android 4.4, SDK Level 19+.

### Gradle via Maven Central
*coming soon*

### Manual

1.&nbsp;Add the hiku repository to your ```build.gradle```

```
buildscript {
    repositories {
        maven { url 'https://s3-us-west-1.amazonaws.com/hiku/'}
    }
}

repositories {
    maven { url 'https://s3-us-west-1.amazonaws.com/hiku/'}
}
```

2.&nbsp; Add the sdk as a dependency.
```
dependencies {
    compile 'us.hiku.sdk:hiku-sdk:3.0.1'
}
```

### Usage and Sample application
#### Usage

The SDK requires 3rd parties to use the application ID and shared secret provided to them by hiku labs, inc. to authenticate and start the setup process.

*Initialization*
```
HikuSetupSDK sdk = HikuSetupSDK.getInstance(this);
sdk.setAppId(APP_ID);
sdk.setAppSecret(APP_SECRET);
```

*Start Configuration*
```
sdk.setEmail(mEmail);
sdk.startSetup(this, authorizationHandler, setupHandler, authenticationHandler, cancelHandler, tutorialCompletedHandler);
```

Callbacks are optional and are called by the SDK at various states in the setup flow.
```
// Sample callbacks
private TutorialCompletedHandler tutorialCompletedHandler = new TutorialCompletedHandler() {
		@Override
		public void onCompletion() {
				String msg = String.format("User completed tutorial!");
				Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
		}
};

private UserCancelledSetupHandler cancelHandler = new UserCancelledSetupHandler() {
		@Override
		public void onCancel() {
				String msg = String.format("User cancelled setup!");
				Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
		}
};

private ApplicationAuthorizationHandler authorizationHandler = new ApplicationAuthorizationHandler() {
		@Override
		public void onAuthorization(boolean authorized) {
				String msg = String.format("Application authorization status: %b",
								authorized);
				Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
		}
};

private UserAuthenticationHandler authenticationHandler = new UserAuthenticationHandler() {
		@Override
		public void onAuthentication(boolean authenticated) {
				String msg = String.format("User authentication status: %b",
								authenticated);
				Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
		}
};

private DeviceSetupHandler setupHandler = new DeviceSetupHandler() {
		@Override
		public void onResult(boolean success) {
				String msg = String.format("Device Setup Status: %b", success);
				Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
		}
};
```

#### Sample app
There is a sample app located in the [sdkapp](https://github.com/hikuinc/hiku_shared/tree/master/SDK/Android/sdkapp) directory. You will need to provide your application id and secret.

# Changelog
For a list of SDK changes, check out the [CHANGELOG](CHANGELOG.md)

# Archive
```
hiku-test-app [archived]:
	a sample application that uses the hiku SDK to manage device setup
repo [archived]:
	contains the SDK aar (v2.1.0.4)
```
