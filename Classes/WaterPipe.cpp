//
//  WaterPipe.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/13.
//
//

#include "WaterPipe.hpp"

#define kIntervalDistance (kWinSizeHeight * 0.2)
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
    auto topWpAppearHeigh = arc4random_uniform(wpHeightSum - 100) + 100;
    auto bottomWpAppearHeigh = wpHeightSum - topWpAppearHeigh;
    
    _topPipe = Sprite::createWithSpriteFrameName(fileName);
    _topPipe->setAnchorPoint(Vec2(0, 0));
    _topPipe->setPosition(0, kWinSizeHeight - topWpAppearHeigh);
    this->addChild(_topPipe);
    
    _bottomPipe = Sprite::createWithSpriteFrameName(fileName);
    _bottomPipe->setFlippedY(true);
    _bottomPipe->setAnchorPoint(Vec2(0, 1));
    _bottomPipe->setPosition(Vec2(0, bottomWpAppearHeigh - height + kWinSizeHeight));
    this->addChild(_bottomPipe);

    this->setContentSize(Size(_topPipe->getContentSize().width, height));
    this->setAnchorPoint(Vec2(0, 0));
    
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
