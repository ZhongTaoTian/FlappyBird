//
//  GameElement.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/9.
//
//

#include "GameElement.hpp"

GameElement* GameElement::createGameElementLayer(PlayerType type)
{
    auto elementLayer = new GameElement();
    if (elementLayer && elementLayer->init(type)) {
        elementLayer->autorelease();
    } else {
        delete elementLayer;
        elementLayer = nullptr;
    }
    
    return elementLayer;
}

bool GameElement::init(PlayerType type)
{
    Layer::init();
    
    // bg
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images_block_copy.plist");
    _batchNode = SpriteBatchNode::create("images_block_copy.pvr.ccz");
    addChild(_batchNode);
    
    auto bgType = arc4random_uniform(2);
    auto bg = Sprite::createWithSpriteFrameName(bgType == 0 ? "bg_0.png" : "bg_1.png");
    bg->setPosition(kWinSize / 2);
    _batchNode->addChild(bg);
    
    // land
    _land = Land::createLand(true);
    addChild(_land);
    
    _title = Sprite::createWithSpriteFrameName("ready.png");
    _title->setPosition(kWinSizeWidth * 0.5, kWinSizeHeight * 0.63);
    _batchNode->addChild(_title);
    
    // tips pictrue
    string name = type == OnePlayer ? "tap.png" : "tutorial.png";
    _tipsTap = Sprite::createWithSpriteFrameName(name);
    _tipsTap->setPosition(Vec2(kWinSizeWidth * 0.5, kWinSizeHeight * 0.45));
    _batchNode->addChild(_tipsTap);
    
    return true;
}

void GameElement::startMoveFloor()
{
    // floor move animtion
    float durtion = 4;
    auto move = MoveTo::create(durtion, Vec2(-kWinSizeWidth, 0));
    auto moveEnd = CallFuncN::create([this](Node *){
        _land->setPosition(Vec2(0, 0));
    });
    _land->runAction(RepeatForever::create(Sequence::create(move, moveEnd, NULL)));
}
