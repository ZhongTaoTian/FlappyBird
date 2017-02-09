//
//  Game.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/9.
//
//

#include "Game.hpp"

Scene* Game::createScene(PlayerType playerType)
{
    Scene *scene = Scene::create();
    
    auto gameLayer = Game::createGameLayer(playerType);
    if (gameLayer) {
        scene->addChild(gameLayer);
    }
    
    return scene;
}

bool Game::init(PlayerType playerType)
{
    Layer::init();
    _playerType = playerType;
    buildBackgroundSprite();
    
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
}

void Game::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    
    // floor move animtion
    float durtion = 8;
    auto move = MoveTo::create(durtion, Vec2(-kWinSizeWidth, 0));
    auto moveEnd = CallFuncN::create([this](Node *){
        _land->setPosition(Vec2(0, 0));
    });
    _land->runAction(RepeatForever::create(Sequence::create(move, moveEnd, NULL)));
}
