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

    void showResurrectionTipsView(Callback yesBtnClick, Callback noBtnClick, int score, Callback playAgain, Callback share);
   
private:
    Sprite* _resurrection;
    Button* _noBtn;
    Button* _yesBtn;
    int _resCount;
    int _scroe;
    
    Callback _yesBtnClick;
    Callback _noBtnClick;
    Callback _playAgain;
    Callback _share;
    Layer* _scoreLayer;
    ProgressTimer* _progress;
    
    void buttonTouchCallback(Ref *sender, Widget::TouchEventType type);
    void update(float dt);
    void showGameOverTips(int score);
    void continueGame();
    int getResNeedCoinNum(int resCount);
    
    Sprite* addSpriteWithName(const std::string &name, Vec2 position);
    Node* addBtn(int tag, const std::string imageName, Vec2 position, Vec2 anchorPoint);
    
    void showGoidInsufficient();
};

#endif /* TipsLayer_hpp */
