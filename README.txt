								The HikuSetupApp
								============


The HikuSetupApp is an application that demonstrates how to use the Hiku SDK. It contains code that shows you how to login a user and to register a Hiku device.

Building HikuSetupApp
------------------
1. Make sure that CocoaPods (https://cocoapods.org/) is installed on your machine and that you understand how to use pods.
2. Make a git clone from https://github.com/hikuinc/hiku_shared
3. cd hiku_shared/SDK/iOS/3.x/HikuSetupApp
4. edit HikuSetupApp/HKViewController.m and modify the #defines for APPID and SHARED. These will contain strings provided to you by Hiku which will enable your app to communicate with the Hiku servers.
6. pod install
    * This command will retrieve some libraries. You will see output something like this:
            * Analyzing dependencies
            * Pre-downloading: `AFNetworkActivityLogger` from `https://github.com/AFNetworking/AFNetworkActivityLogger.git`, branch `3_0_0`
            * Downloading dependencies
            * Installing AFNetworkActivityLogger (3.0.0)
            * Installing AFNetworking (3.1.0)
            * Installing Bolts (1.8.4)
            * Installing FBSDKCoreKit (4.18.0)
            * Installing FBSDKShareKit (4.18.0)
            * Generating Pods project
            * Integrating client project
            * [!] Please close any current Xcode sessions and use `HikuSetupApp.xcworkspace` for this project from now on.
            * Sending stats
            * Pod installation complete! There are 3 dependencies from the Podfile and 5 total pods installed.
	    
    * You might see an error in the pod install output that says something about target settings being overridden and advising you to add a new line that includes the string "$(inherited). If you see this, then, go to the HKSetupApp project "Build Settings" page and search for "OTHER_LDFLAGS". Using the editor, add a new line for this setting with the string "$(inherited)"

7. The pod install command creates a new project workspace file "HikuSetupApp.xcworkspace". You will use this file instead of the HikuSetupApp.xcodeproj file because it includes additional library dependency information provide by pods.
8. Open HikuSetupApp.xcworkspace in Xcode
    * select “HikuSetupApp” target in “HikuSetupApp” project
    * select type of device to build for (e.g., simulator or connected iPhone)
    * build [there will be some Xcode warnings, which you may ignore]
    * run
