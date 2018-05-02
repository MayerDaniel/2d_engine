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
    std::array<int, 2> wallArray;
    
    TileComponent() = default;
    
    TileComponent(int x, int y, std::array<int, 2> walls)
    {
        tileRect.x = x;
        tileRect.y = y;
        wallArray = walls;
        
        std::string str = "assets/";
        
        switch (wallArray[0]) {
            case 0:
                str += "none";
                break;
             
            case 1:
                str += (char*)"left";
                break;
                
            case 2:
                str += (char*)"right";
                break;
                
            default:
                str += "none";
                break;
        }
        
        str += "_";
        
        switch (wallArray[1]) {
            case 0:
                str += "none";
                break;
                
            case 1:
                str += (char*)"top";
                break;
                
            case 2:
                str += (char*)"bottom";
                break;
                
            default:
                str += "none";
                break;
        }
        
        str += ".png";
        
        path = strdup(str.c_str());        
    }
    
    void init() override
    {
        entity->addComponent<PositionComponent>(tileRect.x, tileRect.y);
        position = &entity->getComponent<PositionComponent>();
        
        entity->addComponent<SpriteComponent>(64, 64, path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
    
    
};

#endif /* TileComponent_hpp */
