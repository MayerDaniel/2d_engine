//
//  game.cpp
//  2d_engine
//
//  Created by Dan on 4/23/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#include "Game.hpp"

Map *map;

SDL_Renderer *Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsytems initialized..." << std::endl;
        
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            std::cout << "Window created!" << std::endl;
        }
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            std::cout << "Renderer created!" << std::endl;
        }
        
        isRunning = true;
        
        map = new Map();
        
        //ecs implementation
        
        newPlayer.addComponent<PositionComponent>(32,32);
        newPlayer.addComponent<SpriteComponent>("assets/strip.png");
        
    } else {
        isRunning = false;
    }
}

void Game::handleEvents()
{
    
    for (auto &event : Game::GetFrameEvents()){
        
        switch(event.type){
            case SDL_QUIT:
                isRunning = false;
                break;
                
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT){
                    newPlayer.getComponent<PositionComponent>().update(mouseX - (mouseX % 32), mouseY - (mouseY % 32));
                }
                
                
            delfault:
                break;
        }
        
    }
    
    Game::GetFrameEvents().clear();
    
    
}

void Game::update()
{
    count++;
    manager.update();
    newPlayer.update();
    

}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    newPlayer.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}


