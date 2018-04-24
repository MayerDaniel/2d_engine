#include "TextureManager.hpp"

SDL_Texture * TextureManager::LoadTexture(const char *filePath, SDL_Renderer *ren)
{
    SDL_Surface *tempSurface = IMG_Load(filePath);
    if( tempSurface == NULL )
    {
        std::cout << "failed to load img" << std::endl;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return tex;
}
