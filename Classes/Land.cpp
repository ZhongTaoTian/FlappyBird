//
//  Land.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/9.
//
//

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
