//
//  SelectPlayer.hpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/8.
//
//

#ifndef SelectPlayer_hpp
#define SelectPlayer_hpp

#include <stdio.h>
#include "Const.hpp"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class SelectPlayer:public Layer {
    
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(SelectPlayer);
    
private:
    void addButton();
    void addPicture();
    void addButton(const string &pressImageName, int tag, Vec2 postion, const string &title);
    void buttonTouchCallback(Ref *sender, Widget::TouchEventType type);
    
    Sprite* bird;
    Sprite* title;
    Sprite* floor;
    Sprite* floor2;
    
    virtual void onEnterTransitionDidFinish();
};


#endif /* SelectPlayer_hpp */
