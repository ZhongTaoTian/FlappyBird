//
//  PhysicsEdge.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/10.
//
//  topPhysicsEdge
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#ifndef PhysicsEdge_hpp
#define PhysicsEdge_hpp

#include "Const.hpp"

class PhysicsEdge:public Node {
    
public:
    virtual bool init();
    CREATE_FUNC(PhysicsEdge);
};

#endif /* PhysicsEdge_hpp */
