//
//  Land.hpp
//  FlappyBird
//
//  Created by 维尼的小熊 on 2017/2/9.
//
//

#ifndef Land_hpp
#define Land_hpp

#include <stdio.h>
#include "Const.hpp"

class Land:public Layer {
public:
    virtual bool init(bool needPhysics);
    static Land* createLand(bool needPhysics);

private:
    void addFloor(Vec2 position, int zOrder);
};

#endif /* Land_hpp */
