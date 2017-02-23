//
//  GameElement.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//  game场景内其他元素

#ifndef GameElement_hpp
#define GameElement_hpp

#include "Const.hpp"
#include "Land.hpp"
#include "WaterPipe.hpp"

enum PlayerType {
    OnePlayer = 0,
    TwoPlayer
};

class GameElement:public Layer {
    
public:
    virtual bool init(PlayerType type);
    static GameElement* createGameElementLayer(PlayerType type);
    void startMoveFloor();
    float _birdX;
   
    void startGame();
    void stopGame();
    void birdResurrection(function<void ()> timeEnd);
    void addWaterPipe(WaterPipeColorType color);
    void hiddenAllLabel();
    LabelAtlas* _goldCoinCount;
    int getPassScore();
    
    void pauseGame();
    void resumeGame();
    
private:
    SpriteBatchNode* _batchNode;
    Land* _land;
    Sprite* _title;
    Sprite* _tipsTap;
    Sprite* _tipsTap2;
    bool isPlayingGame;
    PlayerType playType;
    Sprite* _goldCoin;
    float _wpHeight;
    int _index = 80;
    WaterPipeColorType _wpColor;
    function<void ()> _unTimeEnd;
    bool _birdUnrivalled;
    int _unrivalledIndex;
    
    Vector<WaterPipe *>_waterPipes;
    
    
    LabelAtlas* _passNum;
    int _passIndex;
    
    virtual void update(float dt);
};

#endif /* GameElement_hpp */
