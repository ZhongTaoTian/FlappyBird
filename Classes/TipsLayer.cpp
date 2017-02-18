//
//  TipsLayer.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/14.
//

#include "TipsLayer.hpp"
#include "GameDataManager.hpp"

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
    char name[30];
    sprintf(name, "yes_%d.png", getResNeedCoinNum(resCount));
    _yesBtn->loadTextures(name, name, "", TextureResType::PLIST);
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

int TipsLayer::getResNeedCoinNum(int resCount)
{
    int res = 5;
    switch (resCount) {
        case 0:
            res = 5;
            break;
        case 1:
            res = 10;
            break;
        case 2:
            res = 20;
            break;
        case 3:
            res = 50;
            break;
        case 4:
            res = 100;
            break;
        case 5:
            res = 200;
            break;
        case 6:
            res = 300;
            break;
        case 7:
            res = 500;
            break;
        default:
            res = 1000;
            break;
    }
    
    return res;
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

void TipsLayer::showResurrectionTipsView(Callback yesBtnClick, Callback noBtnClick, int score, Callback playAgain, Callback share)
{
    _yesBtnClick = yesBtnClick;
    _noBtnClick = noBtnClick;
    _playAgain = playAgain;
    _share = share;
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
        buttonTouchCallback(_noBtn, Widget::TouchEventType::ENDED);
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
                GameDataManager::getInstance()->saveUserBestScore(_scroe);
                showGameOverTips(_scroe);
                GameDataManager::getInstance()->saveUserData();
                
                break;
            case kYesBtnTag:
                
                // 计算需要扣除的金币数量
                unschedule(schedule_selector(TipsLayer::update));
                
                if (GameDataManager::getInstance()->getAllCoinCount() - getResNeedCoinNum(_resCount) >= 0) {
                    this->removeFromParent();
                    GameDataManager::getInstance()->spendCoinToResurrection(getResNeedCoinNum(_resCount));
                    _yesBtnClick();
                } else {
                    // 提示金币不足
                    this->showGoidInsufficient();
                }

                break;
            case kOkBtnTag:
                if (_playAgain) {
                    _playAgain();
                }
                break;
            case kShareBtnTag:
                if (_share) {
                    _share();
                }
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
    _scoreLayer->setPosition(Vec2(0, -kWinSizeHeight));
    
    // Layout score
    auto gameOver = addSpriteWithName("gameover.png", Vec2(kWinSizeWidth * 0.5, kWinSizeHeight * 0.8));
    auto board = addSpriteWithName("score_board.png", Vec2(kWinSizeWidth * 0.5, 0));
    board->setPosition(Vec2(kWinSizeWidth * 0.5, gameOver->getBoundingBox().getMidY() - gameOver->getContentSize().height * 0.5 - board->getContentSize().height * 0.5 - 30));
    
    addBtn(kOkBtnTag, "ok_button.png", Vec2(board->getBoundingBox().getMinX() + 30, board->getBoundingBox().getMinY() - 20), Vec2(0, 1));
    addBtn(kShareBtnTag, "share_button.png", Vec2(board->getBoundingBox().getMaxX() - 40, board->getBoundingBox().getMinY() - 20), Vec2(1, 1));
    
    auto boardH = board->getContentSize().height;
    auto boardW = board->getContentSize().width;
    // add score label
    auto numTexture = TextureCache().addImage("small_number_iphone.png");
    auto picW = numTexture->getContentSize().width;
    auto picH = numTexture->getContentSize().height;
    auto scoreLb = LabelAtlas::create(to_string(score), "small_number_iphone.png", picW * 0.1, picH, '0');
    scoreLb->setAnchorPoint(Vec2(1, 0.5));
    scoreLb->setPosition(Vec2(boardW * 0.86, boardH * 0.635));
    board->addChild(scoreLb);
    
    auto bestLb = LabelAtlas::create(to_string(GameDataManager::getInstance()->getBestScore()), "small_number_iphone.png", picW * 0.1, picH, '0');
    bestLb->setAnchorPoint(Vec2(1, 0.5));
    bestLb->setPosition(Vec2(boardW * 0.86,boardH * 0.3));
    board->addChild(bestLb);
    
    string name;
    if (score >= 0 && score < 100) {
        name = "bronze_medal.png";
    } else if (score >= 100 && score < 200) {
        name = "platinum_medal.png";
    } else if (score >= 200) {
        name = "gold_medal.png";
    }
    
    if (name.length() > 0) {
        auto madel = Sprite::createWithSpriteFrameName(name);
        madel->setPosition(boardW * 0.22, boardH * 0.47);
        board->addChild(madel);
    }
    
    // start animation
    auto move = MoveTo::create(0.5, Vec2(0, 0));

    auto anim = Sequence::create(move, DelayTime::create(0.2), CallFunc::create([this](){
        auto btn1 = _scoreLayer->getChildByTag(kOkBtnTag);
        auto btn2 = _scoreLayer->getChildByTag(kShareBtnTag);
        btn1->runAction(FadeIn::create(0.3));
        btn2->runAction(FadeIn::create(0.3));
    }), NULL);
    
    _scoreLayer->runAction(anim);
}

Sprite* TipsLayer::addSpriteWithName(const std::string &name, Vec2 position)
{
    auto sp = Sprite::createWithSpriteFrameName(name);
    sp->setPosition(position);
    _scoreLayer->addChild(sp);
    return sp;
}

Node* TipsLayer::addBtn(int tag, const std::string imageName, cocos2d::Vec2 position, Vec2 anchorPoint)
{
    auto btn = Button::create();
    btn->setAnchorPoint(anchorPoint);
    btn->loadTextures(imageName, imageName, "", TextureResType::PLIST);
    btn->setPosition(position);
    btn->addTouchEventListener(CC_CALLBACK_2(TipsLayer::buttonTouchCallback, this));
    btn->setTag(tag);
    btn->setOpacity(0);
    _scoreLayer->addChild(btn);
    
    return btn;
}

#pragma mark - todo 购买金币
void TipsLayer::showGoidInsufficient()
{
    
}









