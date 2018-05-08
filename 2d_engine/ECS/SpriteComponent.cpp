//
//  SpriteComponent.cpp
//  2d_engine
//
//  Created by Dan on 4/26/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(int h, int w, const char* path)
{
    SpriteComponent::setTex(path);
    counter = 0;
    srcH = h;
    srcW = w;
}

SpriteComponent::SpriteComponent(const char* path)
{
    SpriteComponent::setTex(path);
    counter = 0;
    srcH = 32;
    srcW = 32;
}

void SpriteComponent::setTex(const char *path){
    
    texture = TextureManager::LoadTexture(path);

}

void SpriteComponent::init()
{
    position = &entity->getComponent<PositionComponent>();
    
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcH;
    srcRect.h = srcW;
    destRect.w = destRect.h = 32;
}

void SpriteComponent::update()
{
    destRect.x = position->x() - Game::camera.x;
    destRect.y = position->y() - Game::camera.y;
    
}

void SpriteComponent::draw() 
{
    TextureManager::Draw(texture, srcRect, destRect);
}
