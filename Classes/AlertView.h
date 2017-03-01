//
//  AlertView.h
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/21.
//
//  iOS的提示窗,解决C++无法与代理通信问题
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#import <Foundation/Foundation.h>

@interface AlertView : UIAlertView

typedef void (^ButtonClick)();

- (instancetype)initWithTitle:(NSString *)title
                      message:(NSString *)message
            cancelButtonTitle:(NSString *)cancelButtonTitle
                okButtonTitle:(NSString *)okButtonTitle
                     oklClick:(ButtonClick)okClick
                  cancelClick:(ButtonClick)cancelClick;

@end
