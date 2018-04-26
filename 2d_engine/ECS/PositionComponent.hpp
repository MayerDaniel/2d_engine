//
//  PositionComponent.h
//  2d_engine
//
//  Created by Dan on 4/26/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#ifndef PositionComponent_h
#define PositionComponent_h

#include "Components.hpp"

class PositionComponent : public Component
{
private:
    int xpos;
    int ypos;
    
public:
    
    PositionComponent();
    
    PositionComponent(int x, int y);
    
    void update() override;
    
    int x();
    void x(int x);
    
    int y();
    void y(int y);
    
    void update(int x, int y);
    
};


#endif /* PositionComponent_h */
