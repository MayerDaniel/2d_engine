//
//  ECS.cpp
//  2d_engine
//
//  Created by Dan on 5/1/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#include "ECS.hpp"

void Entity::addGroup(Group mGroup)
{
    groupBitset[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}
