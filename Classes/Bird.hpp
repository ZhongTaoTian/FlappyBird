//
//  Bird.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

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
