//
//  MovementComponent.cpp
//  2d_engine
//
//  Created by Dan on 4/30/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#include "MovementComponent.hpp"


MoveMarker::MoveMarker(int x, int y){
    src.w = dest.w = 32;
    src.h = dest.h = 32;
    src.x = src.y = 0;
    dest.x = x;
    dest.y = y;
}


MovementComponent::MovementComponent(){
    moveableTiles = 3;
}

MovementComponent::MovementComponent(int moves){
    moveableTiles = moves;
}

void MovementComponent::move(int xpos, int ypos, std::vector<std::array<int, 2> > taken){
    
    for (auto &m : moves){
        if (m.dest.x == xpos && m.dest.y == ypos){
            
            this->entity->getComponent<PositionComponent>().update(xpos, ypos);
            
        } else {
            
        }
        
    }
    
    
    
    
}

void MovementComponent::showValidMoves(std::vector<std::array<int,2>> taken){
   
    int xpos = this->entity->getComponent<PositionComponent>().x();
    int ypos = this->entity->getComponent<PositionComponent>().y();
    
    int endX = xpos + ((moveableTiles + 1) * 32); //the +1 compensate for the fact that sprite's locations are their top left corner
    int endY = ypos + ((moveableTiles + 1) * 32);
    
    for (int x = xpos - (moveableTiles * 32); x < endX; x = x + 32){
        
        for(int y = ypos - (moveableTiles * 32); y < endY; y = y + 32){
            
            bool empty = true;
            
            for (auto &t : taken){
                if (x == t[0] && y == t[1]){
                    empty = false;
                }
            }
            
            if(!(x == xpos && y == ypos) && empty){
                MoveMarker a = MoveMarker(x,y);
                moves.push_back(a);
            }
            
            
        }
        
    }
    
}

void MovementComponent::draw(){
    
    if (this->entity->isClicked()){
        
        SDL_Texture *tile = TextureManager::LoadTexture("assets/valid_move.png");
        for (auto &m : moves){
            std::cout << m.dest.x << ", " << m.dest.y << std::endl;
            TextureManager::Draw(tile, m.src, m.dest);
        }
    } else {
        moves.clear();
    }
}
