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

typedef std::function<void ()> Callback;

class TipsLayer:public Layer {
    
public:
    virtual bool init(int resCount);
    static TipsLayer* createTipsLayer(int resCount);

    void showResurrectionTipsView(Callback yesBtnClick, Callback noBtnClick, int score);
   
private:
    Sprite* _resurrection;
    Button* _noBtn;
    Button* _yesBtn;
    int _resCount;
    int _scroe;
    
    Callback _yesBtnClick;
    Callback _noBtnClick;
    Layer* _scoreLayer;
    ProgressTimer* _progress;
    
    void buttonTouchCallback(Ref *sender, Widget::TouchEventType type);
    void update(float dt);
    void showGameOverTips(int score);
    void continueGame();
    
    Sprite* addSpriteWithName(const std::string &name, Vec2 position);
};

#endif /* TipsLayer_hpp */
