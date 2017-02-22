//
//  PhysicsEdge.cpp
//  FlappyBird
//
//  Created by sfbest on 2017/2/10.
//
//  topPhysicsEdge

#include "PhysicsEdge.hpp"

bool PhysicsEdge::init()
{
    Node::init();
    addComponent(PhysicsBody::createEdgeBox(Size(kWinSizeWidth, 20), PHYSICSBODY_MATERIAL_DEFAULT, 30));
    getPhysicsBody()->setDynamic(false);
    setContentSize(Size(kWinSizeWidth, 10));
    setPosition(Vec2(kWinSizeWidth * 0.5, kWinSizeHeight + 35));
    
    return true;
}
