//
//  GameElement.hpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/9.
//
//  game场景内其他元素

#ifndef GameElement_hpp
#define GameElement_hpp

#include "Const.hpp"
#include "Land.hpp"

enum PlayerType {
    OnePlayer = 0,
    TwoPlayer
};

class GameElement:public Layer {
    
public:
    virtual bool init(PlayerType type);
    static GameElement* createGameElementLayer(PlayerType type);
    void startMoveFloor();
    
    void startGame();
private:
    SpriteBatchNode* _batchNode;
    Land* _land;
    Sprite* _title;
    Sprite* _tipsTap;
    Sprite* _tipsTap2;
    bool isPlayingGame;
    PlayerType playType;
    Sprite* _goldCoin;
    
    LabelAtlas* _goldCoinCount;
    LabelAtlas* _passNum;
};

#endif /* GameElement_hpp */
