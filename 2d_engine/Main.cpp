#include "Game.hpp"

Game *game = nullptr;

int main(int argc, const char * argv[]) {
    
    const int FPS = 60;
    const float frame_delay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;
    
    game = new Game();
    
    game -> init("Flash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, false);
    
    while(game -> running()){
        
        frameStart = SDL_GetTicks();
        
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0)
        {
            Game::GetFrameEvents().push_back(event);
        }
        game -> handleEvents();
        game -> update();
        game -> render();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (frame_delay > frameTime){
            SDL_Delay(frame_delay - frameTime);
        }
    }
    
    game -> clean();
    
    return 0;
}
