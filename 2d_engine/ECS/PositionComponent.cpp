//
//  PositionComponent.cpp
//  2d_engine
//
//  Created by Dan on 4/26/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#include "PositionComponent.hpp"

PositionComponent::PositionComponent(){
    xpos = 0;
    ypos = 0;
}

PositionComponent::PositionComponent(int x, int y)
{
    xpos = x;
    ypos = y;
}

void PositionComponent::update(){
   
}

int PositionComponent::x() { return xpos; }
void PositionComponent::x(int x) { xpos = x; }

int PositionComponent::y() { return ypos; }
void PositionComponent::y(int y) { ypos = y; }

void PositionComponent::update(int x, int y) { xpos = x; ypos = y;}
