//
//  GameDataManager.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 17/2/18.
//
//  博客: http://www.jianshu.com/u/5fe7513c7a57
//  微博: http://weibo.com/5622363113/profile?topnav=1&wvr=6
//  GitHub: https://github.com/ZhongTaoTian

#ifndef GameDataManager_hpp
#define GameDataManager_hpp

#include <stdio.h>

class GameDataManager {
    
public:
    static GameDataManager* getInstance();
    void spendCoinToResurrection(int coinCount);
    void addCoin();
    // 保存用户金币总数以及最佳成绩
    void saveUserData();
    void saveUserBestScore(int score);
    
private:
    CC_SYNTHESIZE(int, _bestScore, BestScore);
    CC_SYNTHESIZE(int, _allCoinCount, AllCoinCount);
};

#endif /* GameDataManager_hpp */
