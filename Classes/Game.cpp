//
//  Game.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/9.
//
//  GameCenter

#include "Game.hpp"
#include "PhysicsEdge.hpp"
#include "TipsLayer.hpp"

Scene* Game::createScene(PlayerType playerType)
{
    Scene *scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // set Gravity acceleration
    scene->getPhysicsWorld()->setGravity(Vec2(0, -1200));
    
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
    
    // add tips
//    _tipsLayer = TipsLayer::create();
//    addChild(_tipsLayer, 4);
    
    return true;
}

bool Game::onContactBegan(cocos2d::PhysicsContact &cat)
{
    if (_gameOver) return false;
    
    _gameOver = true;
    
#warning play sound effect
    
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
                CCLOG("Yes");
            }, [this](){
                CCLOG("NO");
                _elementLayer->hiddenAllLabel();
            }, 100);
            
        });
    } else {
        
    }
    
    _elementLayer->stopGame();
    _bird1->getPhysicsBody()->removeFromWorld();
    
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
    _bird1->setPosition(Vec2(kWinSizeWidth * 0.25, kWinSizeHeight * 0.5));
    this->addChild(_bird1, 3);
    
    _elementLayer->_birdX = _bird1->getPosition().x;
}

void Game::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    
    // floor Move
    _elementLayer->startMoveFloor();
    
    // bird Fly
    _bird1->startFlyAnimation();
    _bird1->startShakeAnimation();
}

#pragma mark - Touch Action
void Game::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    if (_gameOver) return;
    
    if (!_gameIsStarting) {
        _gameIsStarting = true;
        startGame();
    }
    
    _bird1->click();
}

void Game::startGame()
{
     // start Refresh Time
    _elementLayer->startGame();
    
    // setPipeColor
    _pipeType = WaterPipeColorType(arc4random_uniform(3));
    _elementLayer->addWaterPipe(_pipeType);
}
