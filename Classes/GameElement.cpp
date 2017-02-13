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
    
    playType = type;
    
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
    
    _tipsTap2 = Sprite::createWithSpriteFrameName("tutorial2p.png");
    _tipsTap2->setPosition(kWinSizeWidth * 0.5, kWinSizeHeight * 0.28);
    _tipsTap2->setVisible(false);
    addChild(_tipsTap2);

    // add goldCoin
    _goldCoin = Sprite::createWithSpriteFrameName("coin.png");
    _goldCoin->setAnchorPoint(Vec2(1, 0.5));
    _goldCoin->setPosition(kWinSizeWidth * 0.7, kWinSizeHeight * 0.97 - _goldCoin->getContentSize().height * 0.5);
    _batchNode->addChild(_goldCoin);
    
    auto numTexture = TextureCache().addImage("small_number_iphone.png");
    _goldCoinCount = LabelAtlas::create("0", "small_number_iphone.png", numTexture->getContentSize().width / 10, numTexture->getContentSize().height, '0');
    _goldCoinCount->setAnchorPoint(Vec2(0, 0.5));
    _goldCoinCount->setPosition(_goldCoin->getPosition().x + 20, _goldCoin->getPosition().y);
    addChild(_goldCoinCount);
    
    // add passNum
    auto passTexture = TextureCache().addImage("large_number_iphone.png");
    _passNum = LabelAtlas::create("0", "large_number_iphone.png", passTexture->getContentSize().width / 10, passTexture->getContentSize().height, '0');
    _passNum->setAnchorPoint(Vec2(0.5, 0.5));
    _passNum->setPosition(kWinSizeWidth * 0.5, kWinSizeHeight * 0.76);
    addChild(_passNum);
    
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

void GameElement::startGame()
{
    if (isPlayingGame) return;
    
    // hide tipsPic
    _tipsTap->setVisible(false);
    _title->setVisible(false);
    
    isPlayingGame = true;
    
    // show Two Player tips
    if (playType == OnePlayer) return;
    
    _tipsTap2->setVisible(true);
}
