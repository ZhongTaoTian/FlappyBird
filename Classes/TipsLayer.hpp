//
//  TipsLayer.hpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/14.
//
//  Resurrection,Share,PlayAgain.

#ifndef TipsLayer_hpp
#define TipsLayer_hpp

#include "Const.hpp"
#include "ui/CocosGUI.h"

using namespace ui;

class TipsLayer:public Layer {
    
public:
    virtual bool init();
    CREATE_FUNC(TipsLayer);

private:
    Sprite* _resurrection;
    Button* _noBtn;
    Button* _yesBtn;
};

#endif /* TipsLayer_hpp */
