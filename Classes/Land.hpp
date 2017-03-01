//
//  Land.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#ifndef Land_hpp
#define Land_hpp

#include <stdio.h>
#include "Const.hpp"

class Land:public Layer {
public:
    virtual bool init(bool needPhysics);
    static Land* createLand(bool needPhysics);

private:
    void addFloor(Vec2 position, int zOrder);
};

#endif /* Land_hpp */
