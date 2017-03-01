//
//  PhysicsEdge.cpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/10.
//
//  topPhysicsEdge
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#include "PhysicsEdge.hpp"

bool PhysicsEdge::init()
{
    Node::init();
    addComponent(PhysicsBody::createEdgeBox(Size(kWinSizeWidth, 20), PHYSICSBODY_MATERIAL_DEFAULT, 30));
    getPhysicsBody()->setDynamic(false);
    setContentSize(Size(kWinSizeWidth, 10));
    setPosition(Vec2(kWinSizeWidth * 0.5, kWinSizeHeight + 35));
    
    return true;
}
