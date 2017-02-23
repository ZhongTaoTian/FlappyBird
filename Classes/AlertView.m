//
//  AlertView.m
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/21.
//
//  iOS的提示窗,解决C++无法与代理通信问题

#import "AlertView.h"

@interface AlertView () <UIAlertViewDelegate>

@property (nonatomic, copy) ButtonClick okButtonClick;
@property (nonatomic, copy) ButtonClick cancelButtonClick;

@end

@implementation AlertView

- (instancetype)initWithTitle:(NSString *)title message:(NSString *)message cancelButtonTitle:(NSString *)cancelButtonTitle okButtonTitle:(NSString *)okButtonTitle oklClick:(ButtonClick)okClick cancelClick:(ButtonClick)cancelClick
{
    if (self = [super initWithTitle:title message:message delegate:self cancelButtonTitle:okButtonTitle otherButtonTitles:cancelButtonTitle, nil]) {
        self.okButtonClick = okClick;
        self.cancelButtonClick = cancelClick;
    }
    
    return self;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        if (self.okButtonClick) {
            self.okButtonClick();
        }
    } else if (buttonIndex == 1) {
        if (self.cancelButtonClick) {
            self.cancelButtonClick();
        }
    }
}


@end
