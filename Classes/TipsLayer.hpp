//
//  TipsLayer.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/14.
//
//  Resurrection,Share,PlayAgain.
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian


#ifndef TipsLayer_hpp
#define TipsLayer_hpp

#include "Const.hpp"
#include "ui/CocosGUI.h"

using namespace ui;

typedef std::function<void ()> Callback;

class TipsLayer:public Layer {
    
public:
    virtual bool init(int resCount, bool isOnePlayer);
    static TipsLayer* createTipsLayer(int resCount, bool isOnePlayer = true);
    
    void showResurrectionTipsView(Callback yesBtnClick, Callback noBtnClick, int score, Callback playAgain, Callback share);
    void showVsResultTipsView(Callback okBtnClick, Callback shareBtnClick, int score, bool isLeftWin);
    
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
    void buildScoreUI(int score, bool isOnePlayer, bool isLeftWin);
    int getResNeedCoinNum(int resCount);
    
    Sprite* addSpriteWithName(const std::string &name, Vec2 position);
    Node* addBtn(int tag, const std::string imageName, Vec2 position, Vec2 anchorPoint);
    
    void showGoidInsufficient();
    Animate* starTwinkleAnimate();
};

#endif /* TipsLayer_hpp */
