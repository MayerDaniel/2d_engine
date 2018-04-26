#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Components.hpp"
#include <iostream>

class Game{
public:
    Game();
    ~Game();
    
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool running() {return isRunning; };
    
    static SDL_Renderer *renderer;
    
    //janky closure for event handler
    static std::vector<SDL_Event>& GetFrameEvents()
    {
        static std::vector<SDL_Event> frame_events;
        return frame_events;
    }
    
private:
    //event handler vars
    int mouseX;
    int mouseY;
    
    bool isRunning;
    int count = 0;
    SDL_Window *window;
};

#endif
