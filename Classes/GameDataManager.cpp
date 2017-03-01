//
//  GameDataManager.cpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 17/2/18.
//
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#include "GameDataManager.hpp"

#define kUserBestCountKey "kUserBestCountKey"
#define kUserAllCoinCount "kUserAllCoinCount"

static GameDataManager* s_SharedUserDataManager = nullptr;

GameDataManager* GameDataManager::getInstance()
{
    if (s_SharedUserDataManager == nullptr) {
        s_SharedUserDataManager = new GameDataManager();
        
        auto userDefault = cocos2d::UserDefault::getInstance();
        s_SharedUserDataManager->setBestScore(userDefault->getIntegerForKey(kUserBestCountKey, 0));
        s_SharedUserDataManager->setAllCoinCount(userDefault->getIntegerForKey(kUserAllCoinCount, 0));
    }
    
    return s_SharedUserDataManager;
}

void GameDataManager::spendCoinToResurrection(int coinCount)
{
    _allCoinCount -= coinCount;
}

void GameDataManager::addCoin()
{
    _allCoinCount++;
}

void GameDataManager::saveUserBestScore(int score)
{
    if (score < getBestScore()) return;
    
    setBestScore(score);
}

void GameDataManager::saveUserData()
{
    auto useDe = cocos2d::UserDefault::getInstance();
    useDe->setIntegerForKey(kUserAllCoinCount, getAllCoinCount());
    useDe->setIntegerForKey(kUserBestCountKey, getBestScore());
}
