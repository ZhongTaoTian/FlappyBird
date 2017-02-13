//
//  Game.hpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/9.
//
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Const.hpp"
#include "Bird.hpp"
#include "GameElement.hpp"


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
    
    void showWaiting();
    void buildBackgroundSprite();
    
    virtual void onEnterTransitionDidFinish();
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void startGame();
};


#endif /* Game_hpp */
