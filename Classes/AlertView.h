//
//  AlertView.h
//  FlappyBird
//
//  Created by sfbest on 2017/2/21.
//
//

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
