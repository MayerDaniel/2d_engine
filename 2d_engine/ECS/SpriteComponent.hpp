//
//  Sprite.h
//  2d_engine
//
//  Created by Dan on 4/26/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h

#include "../TextureManager.hpp"
#include "Components.hpp"
#include "SDL2/SDL.h"

class PositionComponent;

class SpriteComponent : public Component
{
private:
    PositionComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    int srcH;
    int srcW;
    int counter;
    
public:
    SpriteComponent() = default;
    SpriteComponent(const char* path);
    SpriteComponent(int h, int w, const char* path);
    
    void setTex(const char* path);
    
    void init() override;
    
    void update() override;
    
    void draw() override;
};

#endif /* Sprite_h */
