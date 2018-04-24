//
//  GameObject.hpp
//  2d_engine
//
//  Created by Dan on 4/24/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp
#include "TextureManager.hpp"
#include "Game.hpp"

class GameObject {
    
public:
    GameObject(const char *textureSheet, SDL_Renderer *ren);
    ~GameObject();
    
    void Update();
    void Render();
    
private:
    
    int xpos;
    int ypos;
    
    SDL_Texture *objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer *renderer;
    
};


#endif /* GameObject_hpp */
