//
//  MovementComponent.hpp
//  2d_engine
//
//  Created by Dan on 4/30/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#ifndef MovementComponent_hpp
#define MovementComponent_hpp

#include "Components.hpp"

class MoveMarker
{
public:
    SDL_Rect src, dest;
    MoveMarker(int x, int y);
};

class MovementComponent : public Component{
private:
    SDL_Rect src, dest;
    int moveableTiles;
    std::vector<MoveMarker> moves;
    
public:
    
    MovementComponent();
    MovementComponent(int moves);
    
    void move(int xpos, int ypos, std::vector<std::array<int,2>> taken);
    
    void showValidMoves(std::vector<std::array<int,2>> taken);
    
    void draw() override;
};

#endif /* MovementComponent_hpp */
