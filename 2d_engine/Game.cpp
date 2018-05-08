//
//  game.cpp
//  2d_engine
//
//  Created by Dan on 4/23/18.
//  Copyright © 2018 Dan. All rights reserved.
//

#include "Game.hpp"


SDL_Renderer *Game::renderer = nullptr;

Manager manager;
auto &Player1(manager.addEntity());
auto &Player2(manager.addEntity());

Map map = Map(50, 50);



enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupOccupiers
};

SDL_Rect Game::camera = {0,0,25*32,25*32};

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
        
        
        //ecs implementation
        
        map.LoadMap();
        
        Player1.addComponent<PositionComponent>(32,32);
        Player1.addComponent<SpriteComponent>(49,43,"assets/robot_gun.png");
        Player1.addComponent<MovementComponent>(3);
        Player1.addGroup(groupPlayers);
        Player1.addGroup(groupOccupiers);
        
        Player2.addComponent<PositionComponent>(96,32);
        Player2.addComponent<SpriteComponent>(49,43,"assets/robot_gun.png");
        Player2.addComponent<MovementComponent>(5);
        Player2.addGroup(groupPlayers);
        Player2.addGroup(groupOccupiers);
        
    } else {
        isRunning = false;
    }
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& occupiers(manager.getGroup(groupOccupiers));

void Game::handleEvents()
{
    
    for (auto &event : Game::GetFrameEvents()){
        
        switch(event.type){
            case SDL_QUIT:
                isRunning = false;
                break;
                
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x + camera.x;
                mouseY = event.motion.y + camera.y;
                
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT){
                    
                    std::vector<std::array<int,2>>takenTiles = getTakenTiles();

                    for (auto &p : players){
                        
                        std::cout << map.getTile((mouseX - (mouseX % 32)), (mouseY - (mouseY % 32))).getType() << std::endl;
                        
                        if (p->getComponent<PositionComponent>().x() == (mouseX - (mouseX % 32)) && p->getComponent<PositionComponent>().y() == (mouseY - (mouseY % 32)) )
                        {
                            p->setClick(!p->isClicked());
                            p->getComponent<MovementComponent>().showValidMoves(takenTiles);
                            
                        } else if (p->isClicked()){
                            
                            p->getComponent<MovementComponent>().move(mouseX - (mouseX % 32), mouseY - (mouseY % 32));
                            p->setClick(false);
                            
                        }
                        
                    }
                    
                    

                    
                }
            
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        camera.x -= 32;
                        break;
                    case SDLK_RIGHT:
                        camera.x += 32;
                        break;
                    case SDLK_UP:
                        camera.y -= 32;
                        break;
                    case SDLK_DOWN:
                        camera.y += 32;
                        break;
                    default:
                        break;
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
    
    if(camera.x < 0){
        camera.x = 0;
    }
    if (camera.y < 0){
        camera.y = 0;
    }
    if (camera.x > camera.w){
        camera.x = camera.w;
    }
    if (camera.y > camera.h){
        camera.y = camera.h;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    
    for (auto &t : tiles){
        t->draw();
    }
    for (auto &p : players){
        p->draw();
    }
    for (auto &p : enemies){
        p->draw();
    }
    
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

std::vector<std::array<int,2>> Game::getTakenTiles()
{
    std::vector<std::array<int,2>> taken;
    
    std::vector<std::array<int,2>> unnavigable = map.getUnnavigable();
    
    for (auto &o : occupiers){
        int x = o->getComponent<PositionComponent>().x();
        int y = o->getComponent<PositionComponent>().y();
        taken.push_back({x,y});
    }
    
    taken.insert( taken.end(), unnavigable.begin(), unnavigable.end() );
    
    return taken;
}

void Game::addTile(int x, int y, int type)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(x,y,type);
    tile.addGroup(groupMap);
    map.addToGrid(x, y, &tile);
}

void Game::addMoveMarker(int x, int y){
    auto &tile(manager.addEntity());
    tile.addComponent<PositionComponent>(x,y);
}





