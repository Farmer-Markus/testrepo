#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <mutex>

#include "world.h"
#include "texture.h"
//#include "building.h"
class Buildings;


class game {
    public:
    struct playerPos {
        float x = 0;
        float y = 0;
    } plrPos;

    struct ingameChunkCoords {
        float x = 0;
        float y = 0;
    };
    
    struct ingameCoords {
        float x = 0;
        float y = 0;
    };

    struct windowCoords {
        int x = 0;
        int y = 0;
    };

    struct mouse {
        int x = 0;
        int y = 0;
    };

    bool gameRunning;
    int fps;

    bool startGame(SDL_Window* mainWindow);
    
    private:
        SDL_Window* mainWindow;
        Uint64 deltaTime = SDL_GetTicks64();
        SDL_Renderer* mainRenderer;
        float zoomFactor = 1.0f;
        bool isMultigesture = false;
        bool fingerUp = true;
        SDL_semaphore* semaphore = SDL_CreateSemaphore(0);
        

        struct thread {
            bool finished = false;
            bool isBuilding = false;
            SDL_FRect gndRect; //for ground
            SDL_FRect bldingRect; //for buildings
            ingameCoords coords;
        } thread;
        
        struct key {
            bool keyup = false;
            bool keydown = false;
            bool keyleft = false;
            bool keyright = false;
        };

        struct window {
            int w;
            int h;
        } window;

        struct defaultRec {
            int x = 0;
            int y = 0;
            int w = 32;
            int h = 32;
        } defRec;
        
        struct render {
            int w = 0;
            int h = 0;
        } renderSize;
        
        
        int handleFps();
        bool inputHandling(key& key, mouse& mouse, Buildings& building);
        protected:

    public:
    ingameChunkCoords getIngameChunkCoords(ingameCoords& coords);
    windowCoords getWindowCoords(ingameCoords& gameCoords, playerPos& plrPos, SDL_FRect& rect);
    ingameCoords getIngameCoords(windowCoords& winCoords, playerPos& plrPos, SDL_FRect& rect);
};

