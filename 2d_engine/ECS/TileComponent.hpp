//
//  TileComponent.hpp
//  2d_engine
//
//  Created by Dan on 5/2/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#ifndef TileComponent_hpp
#define TileComponent_hpp

#include "ECS.hpp"
#include "SpriteComponent.hpp"
#include <string.h>
#include "PositionComponent.hpp"
#include "SDL2/SDL.h"

class SpriteComponent;

class TileComponent : public Component
{
public:
    PositionComponent *position;
    SpriteComponent *sprite;
    char *path;
    
    SDL_Rect tileRect;
    int type;
        
    TileComponent() = default;
    
    TileComponent(int x, int y, int t)
    {
        tileRect.x = x;
        tileRect.y = y;
        type = t;
        
        std::string str = "assets/";
        
        switch (type) {
            case 0:
                str += "none_none";
                break;
             
            case 1:
                str += "crate";
                break;
                
            default:
                str += "none_none";
                break;
        }
        
        str += ".png";
        
        path = strdup(str.c_str());        
    }
    
    void init() override
    {
        entity->addComponent<PositionComponent>(tileRect.x, tileRect.y);
        position = &entity->getComponent<PositionComponent>();
        
        entity->addComponent<SpriteComponent>(48, 48, path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
    
    int getType()
    {
        return type;
    }
    
};

#endif /* TileComponent_hpp */
