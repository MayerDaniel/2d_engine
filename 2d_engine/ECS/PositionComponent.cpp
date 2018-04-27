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
    moveableTiles = 3;
}

PositionComponent::PositionComponent(int x, int y, int tiles)
{
    xpos = x;
    ypos = y;
    moveableTiles = tiles;
}

void PositionComponent::update(){}

int PositionComponent::x() { return xpos; }
void PositionComponent::x(int x) { xpos = x; }

int PositionComponent::y() { return ypos; }
void PositionComponent::y(int y) { ypos = y; }

void PositionComponent::update(int x, int y)
{
    if (abs(x - xpos) > moveableTiles*32 || (abs(x - xpos) > moveableTiles*32)){
        std::cout << "Too far away!" << std::endl;
    } else {
        xpos = x;
        ypos = y;
    }
}

void PositionComponent::showValidMoves(){
    
    src.x = src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;
    
    SDL_Texture *tile = TextureManager::LoadTexture("assets/valid_move.png");
    
    int endX = xpos + ((moveableTiles + 1) * 32); //the +1 compensate for the fact that sprite's locations are their top left corner
    int endY = ypos + ((moveableTiles + 1) * 32);
    
    for (int x = xpos - (moveableTiles * 32); x < endX; x = x + 32){
        
        for(int y = ypos - (moveableTiles * 32); y < endY; y = y + 32){
            
            if(!(x == xpos && y == ypos)){
                dest.x = x;
                dest.y = y;
                TextureManager::Draw(tile, src, dest);
            }
            
            
        }
        
    }
}
    
void PositionComponent::draw(){
    
    if (this->entity->isClicked()){
        this->showValidMoves();
    }
    
}

