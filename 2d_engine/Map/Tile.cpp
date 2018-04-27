//
//  Tile.cpp
//  2d_engine
//
//  Created by Dan on 4/27/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#include "Tile.hpp"

Tile::Tile(int t)
{
    type = t;
    
    switch (type) {
        case 0:
            navigable = false;
            break;
            
        case 1:
            navigable = false;
            break;
            
        case 2:
            navigable = true;
            break;
            
        default:
            exit(1);
            break;
    }
}
