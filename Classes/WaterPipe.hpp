//
//  WaterPipe.hpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/13.
//
//

#ifndef WaterPipe_hpp
#define WaterPipe_hpp

#include "Const.hpp"

enum WaterPipeType {
    Normal = 0, // 正常样式 %85
    Move,       // 上下移动 % 5
    Plant,      // 有植物的水管 %5
    Sloping     // 倾斜的水管 %5
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
    
private:
    Sprite *_topPipe;
    Sprite *_bottomPipe;
    Sprite *_plant;
    Vector<Node *> _phyBodys;
    
    char fileName[30];
    WaterPipeType type;
    
};

#endif /* WaterPipe_hpp */
