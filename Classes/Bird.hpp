//
//  Bird.hpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/9.
//
//

#ifndef Bird_hpp
#define Bird_hpp

#include "Const.hpp"

enum BirdColor{
    Red = 0,
    Blue,
    Yellow,
    Random
};

class Bird:public Sprite {

public:
    BirdColor color;
    
    static Bird* createBird(BirdColor ExcludeColor = Random);
    void startFlyAnimation();
    void stopFlyAnimation();
    
    void startShakeAnimation();
    void stopShakeAnimation();
};

#endif /* Bird_hpp */
