//
//  Map.hpp
//  2d_engine
//
//  Created by Dan on 4/24/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include "Game.hpp"
#include "TextureManager.hpp"

class Map
{
public:
    Map();
    ~Map();
    
    void LoadMap(int arr[20][25]);
    void DrawMap();
    
private:
    
    SDL_Rect src, dest;
    
    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;
    
    int map[20][25];
    
};

#endif /* Map_hpp */
