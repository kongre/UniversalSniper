//
//  UniversalSniperAppController.h
//  UniversalSniper
//
//  Created by 排骨 on 14-12-16.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

