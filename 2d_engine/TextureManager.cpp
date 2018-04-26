#include "TextureManager.hpp"

SDL_Texture * TextureManager::LoadTexture(const char *filePath)
{
    SDL_Surface *tempSurface = IMG_Load(filePath);
    if( tempSurface == NULL )
    {
        std::cout << "failed to load img" << std::endl;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
