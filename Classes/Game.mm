//
//  Game.cpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//  GameCenter

#include "Game.hpp"
#include "PhysicsEdge.hpp"
#include "TipsLayer.hpp"
#include "GameDataManager.hpp"
#include "SelectPlayer.hpp"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <UIKit/UIKit.h>
#endif

#define kPauseImageName "pause_button.png"
#define kPlayImageName "play_button.png"

#define kBird1Tag 40
#define kBird2Tag 50

Scene* Game::createScene(PlayerType playerType)
{
    Scene *scene = Scene::createWithPhysics();
//  scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // set Gravity acceleration
    scene->getPhysicsWorld()->setGravity(Vec2(0, -1400));
    
    auto gameLayer = Game::createGameLayer(playerType);
    if (gameLayer) {
        scene->addChild(gameLayer);
    }
    
    // addPhysicsEdge
    auto edge = PhysicsEdge::create();
    
    scene->addChild(edge);
    
    return scene;
}

bool Game::init(PlayerType playerType)
{
    Layer::init();
    _playerType = playerType;
    buildBackgroundSprite();
    
    // add onTouchLisner
    auto lisner = EventListenerTouchAllAtOnce::create();
    lisner->onTouchesBegan = CC_CALLBACK_2(Game::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(lisner, this);
    
    // add Contact listener
    auto contactLisner = EventListenerPhysicsContact::create();
    contactLisner->onContactBegin = CC_CALLBACK_1(Game::onContactBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactLisner, this);
    
    _pauseBtn = Button::create();
    _pauseBtn->loadTextures(kPauseImageName, kPauseImageName, kPauseImageName, TextureResType::PLIST);
    _pauseBtn->setAnchorPoint(Vec2(0, 1));
    _pauseBtn->setPosition(Vec2(20, kWinSizeHeight - 35));
    _pauseBtn->setVisible(false);
    _pauseBtn->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("swoosh.caf");
        
            _btnSelected = !_btnSelected;
            if (_btnSelected) {
                // pause
                _pauseBtn->loadTextures(kPlayImageName, kPlayImageName, kPlayImageName, TextureResType::PLIST);
                pauseGame();
            } else {
                // play
                _pauseBtn->loadTextures(kPauseImageName, kPauseImageName, kPauseImageName, TextureResType::PLIST);
                resumeGame();
            }
        }
    });
    addChild(_pauseBtn, 1000);
    
    return true;
}

bool Game::onContactBegan(cocos2d::PhysicsContact &cat)
{
    if (_gameOver || _birdUnrivalled) return true;
    
    // 判断是不是鸟
    if (_playerType == OnePlayer) {
        if (!(cat.getShapeA()->getBody()->getNode()->getTag() == kBird1Tag || cat.getShapeB()->getBody()->getNode()->getTag() == kBird1Tag)) {
            return true;
        }
    } else {
        if (!(cat.getShapeA()->getBody()->getNode()->getTag() == kBird1Tag || cat.getShapeB()->getBody()->getNode()->getTag() == kBird1Tag || cat.getShapeB()->getBody()->getNode()->getTag() == kBird2Tag || cat.getShapeB()->getBody()->getNode()->getTag() == kBird2Tag)) {
            return true;
        }
    }
    
    _gameOver = true;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.caf");
    showFlashLightAnimation();
    
    // Contact object stopGame
    if (_playerType == OnePlayer) {
        // stop Fly and rota
        _bird1->stopFlyAndRotatoAnimation();
        // start Fall
        _bird1->startFallAnimation([this](){
            // show revival view
            
            auto tipsLayer = TipsLayer::createTipsLayer(_resCount);
            this->addChild(tipsLayer, 4);
            tipsLayer->showResurrectionTipsView([this](){
                // Resurrection
                _bird1->birdResurrection(Vec2(kWinSizeWidth * 0.25, kWinSizeHeight * 0.5));
                _bird1->click();
                _elementLayer->_goldCoinCount->setString(to_string(GameDataManager::getInstance()->getAllCoinCount()));
                _elementLayer->birdResurrection([this](){
                    _birdUnrivalled = false;
                    _bird1->setOpacity(255);
                });
                _resCount++;
                _gameOver = false;
                _birdUnrivalled = true;
            }, [this](){
                _elementLayer->hiddenAllLabel();
            }, _elementLayer->getPassScore(), [](){
                // player again
                Director::getInstance()->replaceScene(TransitionFade::create(0.25, Game::createScene(OnePlayer), Color3B(255, 255, 255)));
                
            }, [](){
                // share
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"https://github.com/ZhongTaoTian"]];
#endif
            });
        });
    } else {
        bool firstWin = false;
        // 判断是哪一个鸟被撞了
        if (cat.getShapeA()->getBody()->getNode()->getTag() == kBird1Tag || cat.getShapeB()->getBody()->getNode()->getTag() == kBird1Tag) {
            _bird1->stopFlyAndRotatoAnimation();
            _bird2->stopRatatoAnimation();
        } else if (cat.getShapeB()->getBody()->getNode()->getTag() == kBird2Tag || cat.getShapeB()->getBody()->getNode()->getTag() == kBird2Tag) {
            _bird2->stopFlyAndRotatoAnimation();
            _bird1->stopRatatoAnimation();
            firstWin = true;
        }
        
        _bird1->getPhysicsBody()->removeFromWorld();
        _bird2->getPhysicsBody()->removeFromWorld();
        
        auto fallBird = firstWin ? _bird2 : _bird1;
        fallBird->startFallAnimation([this, firstWin](){
            _elementLayer->hiddenAllLabel();
            
            auto tipsLayer = TipsLayer::createTipsLayer(0, false);
            this->addChild(tipsLayer, 4);
            tipsLayer->showVsResultTipsView([](){
                // player again
                Director::getInstance()->replaceScene(TransitionFade::create(0.25, Game::createScene(TwoPlayer), Color3B(255, 255, 255)));
            }, [](){
            
            }, _elementLayer->getPassScore(), firstWin);
        });
    }
    
    _elementLayer->stopGame();
    _bird1->getPhysicsBody()->setEnabled(false);
    
    return true;
}

Game* Game::createGameLayer(PlayerType playerType)
{
    auto gameLayer = new Game();
    if (gameLayer && gameLayer->init(playerType)) {
        gameLayer->autorelease();
        
        return gameLayer;
    } else {
        delete gameLayer;
        gameLayer = nullptr;
        return nullptr;
    }
}

void Game::buildBackgroundSprite()
{
    // add elementLayer
    _elementLayer = GameElement::createGameElementLayer(_playerType);
    addChild(_elementLayer, 2);
    
    // add bird
    _bird1 = Bird::createBird();
    _bird1->setPosition(Vec2(kWinSizeWidth * 0.3, kWinSizeHeight * 0.5));
    _bird1->setTag(kBird1Tag);
    this->addChild(_bird1, 3);
    
    if (_playerType == TwoPlayer) {
        // vs model
        _bird2 = Bird::createBird(_bird1->color);
        _bird2->setPosition(Vec2(kWinSizeWidth * 0.3, kWinSizeHeight * 0.5));
        _bird2->setTag(kBird2Tag);
        _bird1->setPosition(Vec2(kWinSizeWidth * 0.15, _bird1->getPosition().y));
        this->addChild(_bird2, 3);
        _elementLayer->_birdX = _bird2->getPosition().x;
    } else {
        _elementLayer->_birdX = _bird1->getPosition().x;
    }
    
    _pH = kWinSizeHeight;

}

void Game::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    
    // floor Move
    _elementLayer->startMoveFloor();
    
    // bird Fly
    _bird1->startFlyAnimation();
    _bird1->startShakeAnimation(1);
    
    if (_playerType == TwoPlayer) {
        _bird2->startFlyAnimation();
        _bird2->startShakeAnimation(2);
    }
}

#pragma mark - Touch Action
void Game::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    if (_gameOver) return;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("flap.caf");
    
    if (!_gameIsStarting) {
        _gameIsStarting = true;
        startGame();
        
        if (_playerType == PlayerType::TwoPlayer) {
            _bird1->click();
            _bird2->click();
            return;
        }
    }
    
    if (_playerType == PlayerType::OnePlayer) {
        _bird1->click();
    } else {
        // 对战模式 判断点击的点在屏幕哪边
        for (int i = 0; i < touches.size(); i++) {
            auto touch = touches[i];
            if (touch->getLocation().x <= kWinSizeWidth * 0.5) {
                _bird1->click();
            } else {
                _bird2->click();
            }
        }
    }
}

void Game::onExit()
{
    Layer::onExit();
    
    GameDataManager::getInstance()->saveUserData();
}

void Game::startGame()
{
    // showpauseBtn
    _pauseBtn->setVisible(true);
    
    // start Refresh Time
    _elementLayer->startGame();
    
    // setPipeColor
    _pipeType = WaterPipeColorType(arc4random_uniform(3));
    _elementLayer->addWaterPipe(_pipeType);
    
    schedule(schedule_selector(Game::update), 1 / 60.0f);
}

void Game::pauseGame()
{
    Director::getInstance()->pause();
    if (_bird1->getPhysicsBody()->isEnabled()) {
        _bird1->getPhysicsBody()->setEnabled(false);
    }
    
    if (_playerType == TwoPlayer) {
        _bird2->getPhysicsBody()->setEnabled(false);
    }
    
    // show coverLayer
    auto cover = LayerColor::create(Color4B::BLACK);
    cover->setOpacity(120);
    cover->setTag(10086);
    addChild(cover, _pauseBtn->getLocalZOrder() - 1);
    
    auto homeBtn = Button::create();
    homeBtn->loadTextures("home_button.png", "home_button.png", "home_button.png", TextureResType::PLIST);
    homeBtn->setPosition(kWinSize * 0.5);
    cover->addChild(homeBtn);
    homeBtn->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("swoosh.caf");
            Director::getInstance()->resume();
            Director::getInstance()->replaceScene(TransitionFade::create(0.25, SelectPlayer::createScene(), Color3B(255, 255, 255)));
        }
    });
}

void Game::resumeGame()
{
    removeChildByTag(10086);
    
    if (_gameOver) {
        Director::getInstance()->resume();
        return;
    }
    Director::getInstance()->resume();
    
    _bird1->pause();
    if (_playerType == TwoPlayer) {
        _bird2->pause();
    }
    _elementLayer->pauseGame();
    
    // show resume count down
    auto picTexture = TextureCache().addImage("large_number_iphone.png");
    auto countDown = LabelAtlas::create("3", "large_number_iphone.png", picTexture->getContentSize().width / 10, picTexture->getContentSize().height, '0');
    countDown->setAnchorPoint(Vec2(0.5, 0.5));
    countDown->setTag(1232);
    countDown->setPosition(kWinSizeWidth * 0.5, kWinSizeHeight * 0.5);
    addChild(countDown, 10000);
    auto call2 = CallFunc::create([this](){
        auto c = getChildByTag<LabelAtlas *>(1232);
        c->setString("2");
    });
    
    auto call1 = CallFunc::create([this](){
        auto c = getChildByTag<LabelAtlas *>(1232);
        c->setString("1");
    });
    
    auto call = CallFunc::create([this](){
        auto c = getChildByTag<LabelAtlas *>(1232);
        c->removeFromParent();
        
        _bird1->resume();
        if (_playerType == TwoPlayer) {
            _bird2->resume();
        }
        
        _elementLayer->resumeGame();
        
        _bird1->getPhysicsBody()->setEnabled(true);
        if (_playerType == TwoPlayer) {
            _bird2->getPhysicsBody()->setEnabled(true);
        }
    });
    
    countDown->runAction(Sequence::create(DelayTime::create(1), call2, DelayTime::create(1), call1, DelayTime::create(1), call, NULL));
}

void Game::update(float dt)
{
    // 这里稍微解决physicsworld刚体被穿透加的判断,physicsworld内有点问题,速度很快的物体有时候会穿透刚体或者卡住刚体的内部
    // 感觉没有Box2d好用一些,box2d可以设置刚体bullet属性,以便更加精确的计算碰撞
    // 实际项开发中,碰撞的检查需要加入更加精确的判断以及动画 已达到所需求的完美样子
    if (_bird1->getPosition().y > _pH) {
        _bird1->setPosition(Vec2(_bird1->getPosition().x, kWinSizeHeight - _bird1->getContentSize().height));
    }
    
    if (_playerType == TwoPlayer) {
        if (_bird2->getPosition().y > _pH) {
            _bird2->setPosition(Vec2(_bird2->getPosition().x, kWinSizeHeight - _bird2->getContentSize().height));
        }
    }
}

void Game::showFlashLightAnimation()
{
    auto whiteL = LayerColor::create(Color4B::WHITE);
    addChild(whiteL, 100000);
    
    whiteL->runAction(Sequence::create(FadeTo::create(0.25, 0), CallFuncN::create([](Node *no){
        no->removeFromParent();
    }), NULL));
}
