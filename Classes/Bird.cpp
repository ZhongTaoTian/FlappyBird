//
//  Bird.cpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//  Bird
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#include "Bird.hpp"
#include "SimpleAudioEngine.h"

#define kBirdFlyTag 10
#define kBirdShakeTag 11
#define kBirdRotatoTag 12

Bird* Bird::createBird(BirdColor ExcludeColor)
{
    auto bird = new Bird();

    auto randColor = BirdColor(BirdColor(arc4random_uniform(3)));
    
    while (randColor == ExcludeColor) {
        randColor = BirdColor(BirdColor(arc4random_uniform(3)));
    }
    
    char name[30];
    sprintf(name, "fly_%d_0.png", randColor);
    
    if (bird && bird->initWithSpriteFrameName(name)) {
        bird->color = randColor;
        bird->addComponent(PhysicsBody::createBox(bird->getContentSize()));
        bird->getPhysicsBody()->setDynamic(true);
        bird->getPhysicsBody()->setEnabled(false);
        bird->getPhysicsBody()->setRotationEnable(false);
        bird->getPhysicsBody()->setVelocityLimit(500);
        bird->getPhysicsBody()->addMoment(-1);
        bird->getPhysicsBody()->setContactTestBitmask(1);
        bird->autorelease();
    } else {
        delete bird;
        bird = nullptr;
    }
    
    return bird;
}

void Bird::startFlyAnimation()
{
    Vector<SpriteFrame *>frames;
    for (int i = 0; i < 3; i++) {
        char name[30];
        sprintf(name, "fly_%d_%d.png", color, i);
        auto sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        frames.pushBack(sf);
    }
    auto animation = Animation::createWithSpriteFrames(frames);
    animation->setDelayPerUnit(0.1);
    animation->setRestoreOriginalFrame(true);
    auto anim = Animate::create(animation);

    auto fly = RepeatForever::create(anim);
    fly->setTag(kBirdFlyTag);
    
    runAction(fly);
}

void Bird::stopFlyAndRotatoAnimation()
{
    stopFlyAnimation();
    stopActionByTag(kBirdRotatoTag);
}

void Bird::stopRatatoAnimation()
{
    stopActionByTag(kBirdRotatoTag);
}

void Bird::stopFlyAnimation()
{
    stopActionByTag(kBirdFlyTag);
}

void Bird::startFallAnimation(AnimEnd animEnd)
{
    _end = animEnd;
    float currentY = this->getPosition().y;
    auto *land = Sprite::createWithSpriteFrameName("land.png");
    float disH = currentY - land->getContentSize().height;
    float duration = disH / 800;
    
    auto move = MoveTo::create(duration, Vec2(getPosition().x, land->getContentSize().height));
    auto rota = RotateTo::create(duration, 80);
    
//    CallFunc
    auto callback = CallFunc::create([this](){
        if (_end) {
            _end();
        }
    });
    this->runAction(Sequence::create(Spawn::create(move, rota, NULL), callback, NULL));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("drop.caf");
}

void Bird::startShakeAnimation(int birdNum)
{
    if (isShakeing) return;

    float moveDis = 20;
    if (birdNum == 2) {
        moveDis = -20;
    }
    
    auto durtion = 0.7;
    auto moveUp = MoveTo::create(durtion, Vec2(getPosition().x, getPosition().y + moveDis));
    auto moveDown = MoveTo::create(durtion, Vec2(getPosition().x, getPosition().y - moveDis));
    RepeatForever *anim = RepeatForever::create(Sequence::create(moveUp, moveDown, NULL));
    anim->setTag(kBirdShakeTag);
    runAction(anim);
    
    isShakeing = true;
}

void Bird::stopShakeAnimation()
{
    if (!isShakeing) return;
        
    stopActionByTag(kBirdShakeTag);
    
    isShakeing = false;
    
    getPhysicsBody()->setEnabled(true);
}

void Bird::click()
{
    stopShakeAnimation();

    getPhysicsBody()->setVelocity(Vec2(0, 600));
    
    // click bird rotate action
    stopActionByTag(kBirdRotatoTag);
    auto rotaUp = RotateTo::create(0.1, -40);
    auto rotaDown = RotateTo::create(2.5, 80);
    auto seqe = Sequence::create(rotaUp, rotaDown, NULL);
    seqe->setTag(kBirdRotatoTag);
    this->runAction(seqe);
}

void Bird::birdResurrection(cocos2d::Vec2 position)
{
    this->getPhysicsBody()->setEnabled(true);
    this->startFlyAnimation();
    this->setPosition(position);
    this->setOpacity(150);
    this->setRotation(0);
}

