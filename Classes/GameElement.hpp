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
#include "Game.hpp"

class GameElement:public Layer {
    
public:
    virtual bool init(PlayerType type);
    static GameElement* createGameElementLayer(PlayerType type);
};

#endif /* GameElement_hpp */
