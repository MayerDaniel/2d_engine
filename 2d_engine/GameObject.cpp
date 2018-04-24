#include "GameObject.hpp"

GameObject::GameObject(const char *textureSheet, SDL_Renderer *ren)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(textureSheet, ren);
    SDL_RenderCopy(renderer, objTexture, NULL, NULL);
    std::cout << "here" << std::endl;
}

void GameObject::Update()
{
    xpos = 0;
    ypos = 0;

    srcRect.h = 16;
    srcRect.w = 16;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h *2;
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
