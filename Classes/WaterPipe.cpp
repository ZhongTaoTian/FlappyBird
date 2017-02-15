//
//  WaterPipe.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/13.
//
//

#include "WaterPipe.hpp"

#define kIntervalDistance (kWinSizeHeight * 0.23)
#define kPipeLimitHeight  (kWinSizeHeight * 0.135)

// pipe_0.png
bool WaterPipe::init(WaterPipeColorType color, float height)
{
    Layer::init();
    
    sprintf(fileName, "pipe_%d.png", color);
    
    // random Type
    auto typeId = arc4random_uniform(85);
    if (typeId <= 85) {
        type = Normal;
    } else if (typeId > 85 && typeId <= 90) {
        type = Move;
    } else if (typeId > 90 && typeId <= 95) {
        type = Plant;
    } else {
        type = Sloping;
    }
   
    float wpHeightSum = height - kIntervalDistance;
    auto topWpAppearHeigh = arc4random_uniform(wpHeightSum - kPipeLimitHeight) + kPipeLimitHeight;
    auto bottomWpAppearHeigh = wpHeightSum - topWpAppearHeigh;
    
    while (bottomWpAppearHeigh < kPipeLimitHeight) {
        topWpAppearHeigh = arc4random_uniform(wpHeightSum - kPipeLimitHeight) + kPipeLimitHeight;
        bottomWpAppearHeigh = wpHeightSum - topWpAppearHeigh;
    }
    
    _topPipe = Sprite::createWithSpriteFrameName(fileName);
    _topPipe->setAnchorPoint(Vec2(0, 0));
    _topPipe->setPosition(0, kWinSizeHeight - topWpAppearHeigh);
    _topPipe->addComponent(PhysicsBody::createEdgeBox(_topPipe->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, -3));
    _topPipe->getPhysicsBody()->setContactTestBitmask(1);
    this->addChild(_topPipe);
    
    _bottomPipe = Sprite::createWithSpriteFrameName(fileName);
    _bottomPipe->setFlippedY(true);
    _bottomPipe->setAnchorPoint(Vec2(0, 1));
    _bottomPipe->setPosition(Vec2(0, bottomWpAppearHeigh + kWinSizeHeight - height));
    _bottomPipe->addComponent(PhysicsBody::createEdgeBox(_bottomPipe->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, -3));
    this->addChild(_bottomPipe);
    _bottomPipe->getPhysicsBody()->setContactTestBitmask(1);
    auto aa = Rect();

    _coin = Sprite::createWithSpriteFrameName("coin.png");
    _coin->setPosition(Vec2(_topPipe->getContentSize().width * 0.5, _bottomPipe->getBoundingBox().getMaxY() + kPipeLimitHeight * 0.5 + _coin->getContentSize().height * 0.5));
    addChild(_coin);

    this->setContentSize(Size(_topPipe->getContentSize().width, height));
    this->setAnchorPoint(Vec2(1, 0));
    
    return true;
}

WaterPipe* WaterPipe::createWaterPipe(WaterPipeColorType color, float height)
{
    auto wp = new WaterPipe();
    if (wp && wp->init(color, height)) {
        wp->autorelease();
    } else {
        delete wp;
        wp = nullptr;
    }
    
    return wp;
}
