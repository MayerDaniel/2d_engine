#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "TextureManager.hpp"
#include "Components.hpp"
#include "Map.hpp"
#include "ECS.hpp"
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
    
    std::vector<std::array<int,2>> getTakenTiles();
    
    static void addTile(int x, int y, int wall1, int wall2);
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
