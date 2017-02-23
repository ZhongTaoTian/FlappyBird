//
//  GameElement.cpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//

#include "GameElement.hpp"
#include "GameDataManager.hpp"

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
    addChild(_land, 2);
    _wpHeight = kWinSizeHeight - _land->getContentSize().height;
    
    _title = Sprite::createWithSpriteFrameName("ready.png");
    _title->setPosition(kWinSizeWidth * 0.5, kWinSizeHeight * 0.63);
    _batchNode->addChild(_title, 4);
    
    // tips pictrue
    string name = type == OnePlayer ? "tap.png" : "tutorial.png";
    _tipsTap = Sprite::createWithSpriteFrameName(name);
    _tipsTap->setPosition(Vec2(kWinSizeWidth * 0.5, kWinSizeHeight * 0.45));
    _batchNode->addChild(_tipsTap);
    
    _tipsTap2 = Sprite::createWithSpriteFrameName("tutorial2p.png");
    _tipsTap2->setPosition(kWinSizeWidth * 0.5, kWinSizeHeight * 0.28);
    _tipsTap2->setVisible(false);
    addChild(_tipsTap2, 5);
    
    // add goldCoin
    if (type == OnePlayer) {
        _goldCoin = Sprite::createWithSpriteFrameName("coin.png");
        _goldCoin->setAnchorPoint(Vec2(1, 0.5));
        _goldCoin->setPosition(kWinSizeWidth * 0.8, kWinSizeHeight * 0.97 - _goldCoin->getContentSize().height * 0.5);
        this->addChild(_goldCoin, 4);
        
        auto numTexture = TextureCache().addImage("small_number_iphone.png");
        auto picH = numTexture->getContentSize().height;
        auto picW = numTexture->getContentSize().width;
        int coinCount = GameDataManager::getInstance()->getAllCoinCount();
        
        _goldCoinCount = LabelAtlas::create(to_string(coinCount), "small_number_iphone.png", picW * 0.1, picH, '0');
        _goldCoinCount->setAnchorPoint(Vec2(0, 0.5));
        _goldCoinCount->setPosition(_goldCoin->getPosition().x + 10, _goldCoin->getPosition().y);
        addChild(_goldCoinCount, 4);
    }
    
    // add passNum
    auto passTexture = TextureCache().addImage("large_number_iphone.png");
    _passNum = LabelAtlas::create("0", "large_number_iphone.png", passTexture->getContentSize().width / 10, passTexture->getContentSize().height, '0');
    _passNum->setAnchorPoint(Vec2(0.5, 0.5));
    _passNum->setPosition(kWinSizeWidth * 0.5, kWinSizeHeight * 0.8);
    addChild(_passNum, 4);
    
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

void GameElement::stopGame()
{
    _land->pause();
    unschedule(schedule_selector(GameElement::update));
}

// 获取
int GameElement::getPassScore()
{
    return _passIndex;
}

void GameElement::birdResurrection(function<void ()> timeEnd)
{
    _unTimeEnd = timeEnd;
    _unrivalledIndex = 200;
    _birdUnrivalled = true;
    _land->resume();
    schedule(schedule_selector(GameElement::update), 1 / 60.0f);
}

void GameElement::addWaterPipe(WaterPipeColorType color)
{
    _wpColor = color;
    schedule(schedule_selector(GameElement::update), 1 / 60.0f);
}

void GameElement::update(float dt)
{
    if (_birdUnrivalled) {
        _unrivalledIndex--;
        if (_unrivalledIndex <= 0) {
            _birdUnrivalled = false;
            _unTimeEnd();
        }
    }
    
    _index++;
    
    if (_index == 135) {
        // add water pipe
        _index = 0;
        auto wp = WaterPipe::createWaterPipe(_wpColor, _wpHeight, playType == OnePlayer);
        wp->setPosition(kWinSizeWidth, 0);
        addChild(wp);
        _waterPipes.pushBack(wp);
    }
    
    for (auto it = _waterPipes.begin(); it != _waterPipes.end(); it ++) {
        WaterPipe *wp = *it;
        
        if (_birdUnrivalled) {
            wp->setChildPhysicsBodyEnabled(false);
        } else {
            wp->setChildPhysicsBodyEnabled(true);
        }
        
        // move wp
        wp->setPosition(Vec2(wp->getPosition().x - 3, wp->getPosition().y));
        
        if (wp->_coin->isVisible()) {
            // remove coin
            if (wp->getPosition().x < _birdX) {
                wp->_coin->setVisible(false);
                
#pragma mark - todo
                // play sound effect
                if (playType == OnePlayer) {                    
                    GameDataManager::getInstance()->addCoin();
                    _goldCoinCount->setString(to_string(GameDataManager::getInstance()->getAllCoinCount()));
                }
                _passNum->setString(to_string(++_passIndex));
            }
        }
        
        if (wp->getPosition().x < 0 - wp->getContentSize().width) {
            // remove wp
            _waterPipes.eraseObject(wp);
            wp->removeFromParent();
        }
    }
}

void GameElement::hiddenAllLabel()
{
    _passNum->setVisible(false);
}

void GameElement::pauseGame()
{
    pause();
    _land->pause();
}

void GameElement::resumeGame()
{
    resume();
    _land->resume();
}

