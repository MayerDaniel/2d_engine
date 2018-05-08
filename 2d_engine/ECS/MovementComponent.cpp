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

void MovementComponent::move(int xpos, int ypos){
    
    for (auto &m : moves){
        if (m.dest.x == xpos && m.dest.y == ypos){
            
            this->entity->getComponent<PositionComponent>().update(xpos, ypos);
            
        } else {
            
        }
        
    }
    
    
    
    
}

void MovementComponent::showValidMoves(std::vector<std::array<int,2>> takenOrVisited){  //refactor this shiz
   
    int xpos = this->entity->getComponent<PositionComponent>().x();
    int ypos = this->entity->getComponent<PositionComponent>().y();
    
    std::queue<std::array<int, 3>> queue;
    queue.push({xpos + 32, ypos, moveableTiles});
    queue.push({xpos - 32, ypos, moveableTiles});
    queue.push({xpos, ypos + 32, moveableTiles});
    queue.push({xpos, ypos - 32, moveableTiles});
    
    
    while (!queue.empty()){
        
        auto &currTile(queue.front());
        int x = currTile[0];
        int y = currTile[1];
        int movesLeft = currTile[2];
        
        bool valid = true;
        for (auto &t : takenOrVisited){
            if(x == t[0] && y == t[1]){
                valid = false;
            }
        }
        
        if (movesLeft > 0 && valid){
            
            MoveMarker m = MoveMarker(x, y);
            moves.push_back(m);
            takenOrVisited.push_back({x,y});
            
            queue.push({x + 32, y, movesLeft - 1});
            queue.push({x - 32, y, movesLeft - 1});
            queue.push({x, y + 32, movesLeft - 1});
            queue.push({x, y - 32, movesLeft - 1});
            
        }
        
        queue.pop();
        
    }
    
}

void MovementComponent::draw(){
    
    if (this->entity->isClicked()){
        
        SDL_Texture *tile = TextureManager::LoadTexture("assets/valid_move.png");
        for (auto &m : moves){
            SDL_Rect copy = m.dest;
            copy.x = m.dest.x - Game::camera.x;
            copy.y = m.dest.y - Game::camera.y;
            TextureManager::Draw(tile, m.src, copy);
        }
    } else {
        moves.clear();
    }
}

void MovementComponent::update(){
    
}
