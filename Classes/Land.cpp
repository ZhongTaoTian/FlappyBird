//
//  Land.cpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#include "Land.hpp"

bool Land::init(bool needPhysics)
{
    if (!Layer::init()) {
        return false;
    }
    this->setAnchorPoint(Vec2(0, 0));
    
    // floor
    addFloor(Vec2(0, 0), 3);
    addFloor(Vec2(kWinSizeWidth - 100, 0), 2);
    addFloor(Vec2(kWinSizeWidth * 2 - 320, 0), 1);
    
    if (needPhysics) {
        // add bottom edge
        auto land = Layer::create();
        land->setContentSize(Size(kWinSizeWidth * 2, 10));
        land->addComponent(PhysicsBody::createEdgeBox(land->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 5));
        land->setAnchorPoint(Vec2(0, 1));
        land->setPosition(Vec2(0, getContentSize().height - 20));
        land->getPhysicsBody()->setContactTestBitmask(1);
        this->addChild(land);
    }
    
    return true;
}

void Land::addFloor(cocos2d::Vec2 position, int zOrder)
{
    auto floor = Sprite::createWithSpriteFrameName("land.png");
    floor->setAnchorPoint(Vec2(0, 0));
    floor->setPosition(position);
    addChild(floor, zOrder);
    setContentSize(Size(kWinSizeWidth * 2, floor->getContentSize().height));
}

Land* Land::createLand(bool needPhysics)
{
    auto land = new Land();
    if (land && land->init(needPhysics)) {
        land->autorelease();
    } else {
        delete land;
        land = nullptr;
    }
    
    return land;
}
