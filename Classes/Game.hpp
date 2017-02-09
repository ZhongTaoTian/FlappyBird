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
#include "Land.hpp"

enum PlayerType {
    OnePlayer = 0,
    TwoPlayer
};

class Game:public Layer {
public:
    static Scene* createScene(PlayerType playerType);
    virtual bool init(PlayerType playerType);
    static Game* createGameLayer(PlayerType playerType);
    
private:
    SpriteBatchNode* _batchNode;
    Land* _land;
    PlayerType _playerType;
    
    void showWaiting();
    void buildBackgroundSprite();
    
    virtual void onEnterTransitionDidFinish();
};


#endif /* Game_hpp */
