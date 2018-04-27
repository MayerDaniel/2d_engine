//
//  SpriteComponent.cpp
//  2d_engine
//
//  Created by Dan on 4/26/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(const char* path)
{
    SpriteComponent::setTex(path);
    counter = 0;
}

void SpriteComponent::setTex(const char *path){
    
    texture = TextureManager::LoadTexture(path);

}

void SpriteComponent::init()
{
    position = &entity->getComponent<PositionComponent>();
    
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 16;
    destRect.w = destRect.h = 32;
}

void SpriteComponent::update()
{
    counter++;
    srcRect.x = ((counter/30) % 4) * 16;
    destRect.x = position->x();
    destRect.y = position->y();
    
}

void SpriteComponent::draw() 
{
    TextureManager::Draw(texture, srcRect, destRect);
}
