//
//  Bird.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//

#ifndef Bird_hpp
#define Bird_hpp

#include "Const.hpp"
#include "Land.hpp"

typedef std::function<void ()> AnimEnd;

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
    void stopFlyAndRotatoAnimation();
    void stopRatatoAnimation();
    AnimEnd _end;
    
    void startFallAnimation(AnimEnd animEnd);
    void startShakeAnimation(int birdNum);
    void click();
    void birdResurrection(Vec2 position);
    
private:
    void stopShakeAnimation();
    bool isShakeing;
    
};

#endif /* Bird_hpp */
