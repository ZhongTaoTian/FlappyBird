//
//  Game.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Const.hpp"
#include "Bird.hpp"
#include "GameElement.hpp"

#include "ui/CocosGUI.h"

using namespace ui;

class Game:public Layer {
public:
    static Scene* createScene(PlayerType playerType);
    virtual bool init(PlayerType playerType);
    static Game* createGameLayer(PlayerType playerType);
    
private:
    PlayerType _playerType;
    Bird* _bird1;
    Bird* _bird2;
    GameElement* _elementLayer;
    bool _gameIsStarting;
    WaterPipeColorType _pipeType;
    bool _gameOver;
    Button* _pauseBtn;
    
    void showWaiting();
    void buildBackgroundSprite();
    // 复活次数
    int _resCount;
    // 无敌状态
    bool _birdUnrivalled;
    bool _btnSelected;
    
    float _pH;
    
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    bool onContactBegan(PhysicsContact& cat);
    
    void update(float dt);
    
    void startGame();
    void pauseGame();
    void resumeGame();
    
    void showFlashLightAnimation();
};


#endif /* Game_hpp */
