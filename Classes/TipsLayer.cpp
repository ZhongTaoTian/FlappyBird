//
//  TipsLayer.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/14.
//
//

#include "TipsLayer.hpp"

#define kNoBtnTag 100
#define kYesBtnTag 101
#define kOkBtnTag 102
#define kShareBtnTag 103

bool TipsLayer::init(int resCount)
{
    Layer::init();
    
    _resCount = resCount;
    
    _resurrection = Sprite::createWithSpriteFrameName("resurrect.png");
    _resurrection->setPosition(kWinSizeWidth * 0.5, kWinSizeHeight * 0.6);
    _resurrection->setAnchorPoint(Vec2(0.5, 0));
    _resurrection->setVisible(false);
    addChild(_resurrection);
    
    _noBtn = Button::create();
    _noBtn->setAnchorPoint(Vec2(0.5, 1));
    _noBtn->setVisible(false);
    _noBtn->loadTextures("no_button.png", "no_button.png", "", TextureResType::PLIST);
    _noBtn->setPosition(Vec2(kWinSizeWidth * 0.5, _resurrection->getBoundingBox().getMinY() - 50));
    _noBtn->addTouchEventListener(CC_CALLBACK_2(TipsLayer::buttonTouchCallback, this));
    _noBtn->setTag(kNoBtnTag);
    addChild(_noBtn);
    
    _yesBtn = Button::create();
    _yesBtn->setAnchorPoint(Vec2(0.5, 1));
    _yesBtn->loadTextures("yes_5.png", "yes_5.png", "", TextureResType::PLIST);
    _yesBtn->setVisible(false);
    _yesBtn->setTag(kYesBtnTag);
    _yesBtn->setPosition(Vec2(kWinSizeWidth * 0.5, _noBtn->getBoundingBox().getMinY() - 50));
    _yesBtn->addTouchEventListener(CC_CALLBACK_2(TipsLayer::buttonTouchCallback, this));
    addChild(_yesBtn);
    
    auto pic = Sprite::createWithSpriteFrameName("progress_bg.png");
    _progress = ProgressTimer::create(pic);
    _progress->setType(kCCProgressTimerTypeBar);
    _progress->setBarChangeRate(Vec2(1, 0));
    _progress->setMidpoint(Vec2(0, 1));
    _progress->setPercentage(100);
    _progress->setPosition(Vec2((_yesBtn->getContentSize().width - pic->getContentSize().width) * 0.5 + pic->getContentSize().width * 0.5, _yesBtn->getContentSize().height * 0.25));
    _yesBtn->addChild(_progress);
    return true;
}

TipsLayer *TipsLayer::createTipsLayer(int resCount)
{
    auto tips = new TipsLayer();
    if (tips && tips->init(resCount)) {
        tips->autorelease();
    } else {
        delete tips;
        tips = nullptr;
    }
    
    return tips;
}

void TipsLayer::showResurrectionTipsView(Callback yesBtnClick, Callback noBtnClick, int score)
{
    _yesBtnClick = yesBtnClick;
    _noBtnClick = noBtnClick;
    _scroe = score;
    _resurrection->setVisible(true);
    _noBtn->setVisible(true);
    _yesBtn->setVisible(true);
    
    schedule(schedule_selector(TipsLayer::update), 1 / 60.0f);
}

void TipsLayer::update(float dt)
{
    auto pro = _progress->getPercentage() - 0.5;
    if (pro <= 0) {
        unschedule(schedule_selector(TipsLayer::update));
    }
    _progress->setPercentage(pro--);
}

void TipsLayer::buttonTouchCallback(cocos2d::Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        auto btn = (Button *)sender;
        
        switch (btn->getTag()) {
            case kNoBtnTag:
                unschedule(schedule_selector(TipsLayer::update));
                _noBtnClick();
                showGameOverTips(_scroe);
                break;
            case kYesBtnTag:
                unschedule(schedule_selector(TipsLayer::update));
                _yesBtnClick();
                break;
            
            default:
                break;
        }
    }
}

void TipsLayer::showGameOverTips(int score)
{
    _resurrection->setVisible(false);
    _noBtn->setVisible(false);
    _yesBtn->setVisible(false);
    
    _scoreLayer = Layer::create();
    this->addChild(_scoreLayer);
    
    // Layout score
    auto gameOver = addSpriteWithName("gameover.png", Vec2(kWinSizeWidth * 0.5, kWinSizeHeight * 0.8));
    auto board = addSpriteWithName("score_board.png", Vec2(kWinSizeWidth * 0.5, 0));
    board->setPosition(Vec2(kWinSizeWidth * 0.5, gameOver->getBoundingBox().getMidY() - gameOver->getContentSize().height * 0.5 - board->getContentSize().height * 0.5 - 30));
    
    
}

Sprite* TipsLayer::addSpriteWithName(const std::string &name, Vec2 position)
{
    auto sp = Sprite::createWithSpriteFrameName(name);
    sp->setPosition(position);
    _scoreLayer->addChild(sp);
    return sp;
}











