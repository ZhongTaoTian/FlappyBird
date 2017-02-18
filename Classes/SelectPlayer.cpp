//
//  SelectPlayer.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/8.
//
//  SelectModelScene

#include "SelectPlayer.hpp"
#include "Game.hpp"

Scene* SelectPlayer::createScene()
{
    auto s = Scene::create();
    auto l = SelectPlayer::create();
    s->addChild(l);
    
    return s;
}

bool SelectPlayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    addPicture();
    addButton();
    
    return true;
}

void SelectPlayer::addButton()
{
    // add player1
    float btnY = land->getContentSize().height + kWinSizeHeight * 0.03;
    addButton("start_button.png", 10, Vec2(0, btnY), "单人游戏");
    
    // add player2
    addButton("two_play.png", 11, Vec2(0, btnY), "双人对战");
}

void SelectPlayer::addButton(const string &pressImageName, int tag, cocos2d::Vec2 postion, const string &title)
{
    auto btn = Button::create();
    btn->loadTextures(pressImageName, "", "", TextureResType::PLIST);
    auto btnW = btn->getContentSize().width;
    auto margin = kWinSizeWidth * 0.02;
    btn->setAnchorPoint(Vec2(0, 0));
    btn->setTag(tag);
    btn->cocos2d::Node::setPosition(tag == 10 ? kWinSizeWidth * 0.5 - btnW -margin : kWinSizeWidth * 0.5 + margin, postion.y);
    btn->addTouchEventListener(CC_CALLBACK_2(SelectPlayer::buttonTouchCallback, this));
    addChild(btn);
    
    Label *textLabel = Label::create(title, "Marker Felt", 40);
    textLabel->setTextColor(Color4B::BLACK);
    textLabel->setPosition(Vec2(btn->getPosition().x + btnW * 0.5, btn->getPosition().y + btn->getContentSize().height + kWinSizeHeight * 0.03));
    addChild(textLabel);
}

void SelectPlayer::buttonTouchCallback(Ref *sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        auto btn = static_cast<Button *>(sender);
        
        auto type = OnePlayer;
        if (btn->getTag() == 10) {
            type = OnePlayer;
        } else if (btn->getTag() == 11) {
            type = TwoPlayer;
        }
        
        // cut to GameScene
        Director::getInstance()->replaceScene(TransitionFade::create(0.25, Game::createScene(type), Color3B(255, 255, 255)));
    }
}

void SelectPlayer::addPicture()
{
    // add background
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images_block_copy.plist");
    auto batchNode = SpriteBatchNode::create("images_block_copy.pvr.ccz");
    addChild(batchNode);
    
    auto bg = Sprite::createWithSpriteFrameName("bg_0.png");
    bg->setPosition(kWinSize * 0.5);
    batchNode->addChild(bg);
    
    // add floor
    land = Land::createLand(false);
    addChild(land);
    
    // add title
    title = Sprite::createWithSpriteFrameName("title.png");
    title->setPosition(kWinSizeWidth * 0.5 - kWinSizeWidth * 0.05, kWinSizeHeight * 0.8);
    batchNode->addChild(title);
    
    // add bird
    bird = Sprite::createWithSpriteFrameName("fly_0_0.png");
    bird->setPosition(title->getPosition().x + title->getContentSize().width * 0.5 + kWinSizeWidth * 0.07, title->getPosition().y);
    batchNode->addChild(bird);
}

void SelectPlayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    
    // floor move animation
    float durtion = 4;
    auto move = MoveTo::create(durtion, Vec2(-kWinSizeWidth, 0));
    auto moveEnd = CallFuncN::create([this](Node *){
        land->setPosition(Vec2(0, 0));
    });
    land->runAction(RepeatForever::create(Sequence::create(move, moveEnd, NULL)));
    
    // bird fly anim
    float durtion1 = 1.5;
    auto moveUp = MoveTo::create(durtion1, Vec2(title->getPosition().x, title->getPosition().y + 15));
    auto moveDown = MoveTo::create(durtion1, Vec2(title->getPosition().x, title->getPosition().y - 15));
    title->runAction(RepeatForever::create(Sequence::create(moveUp, moveDown, NULL)));
    
    auto birdMoveUp = MoveTo::create(durtion1, Vec2(bird->getPosition().x, bird->getPosition().y + 15));
    auto bireMoveDown = MoveTo::create(durtion1, Vec2(bird->getPosition().x, bird->getPosition().y - 15));
    auto birdMove = Sequence::create(birdMoveUp, bireMoveDown, NULL);
    
    cocos2d::Vector<SpriteFrame *>frams;
    for (int i = 0; i < 3; i++) {
        char name[30];
        sprintf(name, "fly_0_%d.png", i);
        auto sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        frams.pushBack(sf);
    }
    Animation *birdA = Animation::createWithSpriteFrames(frams);
    birdA->setDelayPerUnit(0.1);
    birdA->setRestoreOriginalFrame(true);
    Animate *anma = Animate::create(birdA);

    bird->runAction(RepeatForever::create(anma));
    bird->runAction(RepeatForever::create(birdMove));
}

