//
//  WaterPipe.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/13.
//
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#ifndef WaterPipe_hpp
#define WaterPipe_hpp

#include "Const.hpp"

enum WaterPipeType {
    Normal = 0, // 正常样式 %80
    Move,       // 上下移动 % 10
    Plant,      // 有植物的水管 %10
};

enum WaterPipeColorType {
    GreenColor = 0,
    RedColor,
    BlueColor
};


class WaterPipe:public Layer {
    
public:
    virtual bool init(WaterPipeColorType color, float height, bool showCoin);
    static WaterPipe* createWaterPipe(WaterPipeColorType color, float height, bool showCoin);
    Sprite *_coin;
    void setChildPhysicsBodyEnabled(bool enabled);
    
    void pause();
    void resume();
    void stopGame();
    WaterPipeType type;
private:
    Sprite *_topPipe;
    Sprite *_bottomPipe;
    Sprite *_plant;
    Vector<Node *> _phyBodys;
    
    char fileName[30];
    
    bool _showCoin;
    float _topMoveDis;
    float _bottomMoveDis;
    
    bool _topHasPlant;
    
    virtual void onEnterTransitionDidFinish();
    
};

#endif /* WaterPipe_hpp */
