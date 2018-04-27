//
//  Tile.hpp
//  2d_engine
//
//  Created by Dan on 4/27/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <SDL2/SDL.h>

class Tile
{
private:
    bool navigable;
    int type;
    
public:
    Tile(int type);
    ~Tile();
    bool isNavigable(){ return navigable; }
    int getType(){ return type; }
    
    
};

#endif /* Tile_hpp */
