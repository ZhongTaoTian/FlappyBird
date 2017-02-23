//
//  WaterPipe.cpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/13.
//
//

#include "WaterPipe.hpp"

#define kIntervalDistance (kWinSizeHeight * 0.24)
#define kPipeLimitHeight  (kWinSizeHeight * 0.15)

// pipe_0.png
bool WaterPipe::init(WaterPipeColorType color, float height, bool showCoin)
{
    Layer::init();
    _showCoin = showCoin;
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
   
    type = Move;
    
    _coin = Sprite::createWithSpriteFrameName("coin.png");
    if (!showCoin) {
        _coin->setOpacity(0);
    }
    addChild(_coin);
    
    if (type == Normal || type == Move) {
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
        _phyBodys.pushBack(_topPipe);
        
        _bottomPipe = Sprite::createWithSpriteFrameName(fileName);
        _bottomPipe->setFlippedY(true);
        _bottomPipe->setAnchorPoint(Vec2(0, 1));
        _bottomPipe->setPosition(Vec2(0, bottomWpAppearHeigh + kWinSizeHeight - height));
        _bottomPipe->addComponent(PhysicsBody::createEdgeBox(_bottomPipe->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, -3));
        this->addChild(_bottomPipe);
        _phyBodys.pushBack(_bottomPipe);
        _bottomPipe->getPhysicsBody()->setContactTestBitmask(1);
        
        _coin->setPosition(Vec2(_topPipe->getContentSize().width * 0.5, _bottomPipe->getBoundingBox().getMaxY() + kPipeLimitHeight * 0.5 + _coin->getContentSize().height * 0.5));
        
        if (type == Move) {
            _coin->setOpacity(0);
            _topMoveDis = _topPipe->getContentSize().height - topWpAppearHeigh;
            _bottomMoveDis = _topPipe->getContentSize().height - bottomWpAppearHeigh;
        }
    }
    
    this->setContentSize(Size(_topPipe->getContentSize().width, height));
    this->setAnchorPoint(Vec2(1, 0));
    
    return true;
}

WaterPipe* WaterPipe::createWaterPipe(WaterPipeColorType color, float height, bool showCoin)
{
    auto wp = new WaterPipe();
    if (wp && wp->init(color, height, showCoin)) {
        wp->autorelease();
    } else {
        delete wp;
        wp = nullptr;
    }
    
    return wp;
}

void WaterPipe::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    
    if (type == Move) {
        
        bool toUp = false;
        float moveDis = 0;
        // start Move
        if (_topMoveDis > _bottomMoveDis) {
            toUp = false;
            moveDis = _topMoveDis * 0.5;
        } else {
            toUp = true;
            moveDis = _bottomMoveDis * 0.5;
        }
        
        float topY = _topPipe->getPosition().y;
        float bomY = _bottomPipe->getPosition().y;
        
        float duration = moveDis / 80;
        
        auto move1 = MoveTo::create(duration, Vec2(_topPipe->getPosition().x, toUp ? (topY + moveDis) : (topY - moveDis)));
        auto move2 =  MoveTo::create(duration, Vec2(_topPipe->getPosition().x, topY));
        _topPipe->runAction(RepeatForever::create(Sequence::create(move1, move2, NULL)));
        
        auto move3 = MoveTo::create(duration, Vec2(_bottomPipe->getPosition().x, toUp ? bomY + moveDis : bomY - moveDis));
        auto move4 = MoveTo::create(duration, Vec2(_bottomPipe->getPosition().x, bomY));
        _bottomPipe->runAction(RepeatForever::create(Sequence::create(move3, move4, NULL)));
    }
}

void WaterPipe::setChildPhysicsBodyEnabled(bool enabled)
{
    for (auto it = _phyBodys.begin(); it != _phyBodys.end(); it++) {
        Node *node = *it;
        node->getPhysicsBody()->setEnabled(enabled);
    }
}

void WaterPipe::pause()
{
    Layer::pause();
}

void WaterPipe::resume()
{
    Layer::resume();
}



