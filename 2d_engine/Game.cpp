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
auto &newPlayer(manager.addEntity());
auto &tile1(manager.addEntity());
auto &tile2(manager.addEntity());


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
        newPlayer.addComponent<MovementComponent>(3);
        
        tile1.addComponent<PositionComponent>(64,32);
        tile1.addComponent<SpriteComponent>("assets/strip.png");
        
        tile2.addComponent<PositionComponent>(32,64);
        tile2.addComponent<SpriteComponent>("assets/strip.png");
        
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
                    
                    std::vector<std::array<int,2>> takenTiles;
                    
                    takenTiles.push_back({tile1.getComponent<PositionComponent>().x(), tile1.getComponent<PositionComponent>().y()});
                    takenTiles.push_back({tile2.getComponent<PositionComponent>().x(), tile2.getComponent<PositionComponent>().y()}); //refactor
                    
                    if (newPlayer.getComponent<PositionComponent>().x() == (mouseX - (mouseX % 32)) && newPlayer.getComponent<PositionComponent>().y() == (mouseY - (mouseY % 32)) )
                    {
                        newPlayer.setClick(!newPlayer.isClicked());
                        newPlayer.getComponent<MovementComponent>().showValidMoves(takenTiles);
                    
                    } else if (newPlayer.isClicked()){
                        
                        newPlayer.getComponent<MovementComponent>().move(mouseX - (mouseX % 32), mouseY - (mouseY % 32), takenTiles);
                        newPlayer.setClick(false);
                        
                    }
                    
                    

                    
                }
                
                
            delfault:
                break;
        }
        
    }
    
    Game::GetFrameEvents().clear();
    
    
}

void Game::update()
{
    manager.update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}


