//
//  PositionComponent.h
//  2d_engine
//
//  Created by Dan on 4/26/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#ifndef PositionComponent_h
#define PositionComponent_h

#include "../TextureManager.hpp"
#include "Components.hpp"


class PositionComponent : public Component
{
private:
    int xpos, ypos;
    int displayX, displayY;
    
public:
    PositionComponent();
    PositionComponent(int x, int y);
        
    void update() override;
    void draw() override;
    
    int x();
    void x(int x);
    
    int y();
    void y(int y);
    
    void update(int x, int y);
    
};

#endif /* PositionComponent_h */
