#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "world.h"


class game {
    public:
    struct playerPos {
        float x = 0;
        float y = 0;
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
        
        struct key {
            bool keyup = false;
            bool keydown = false;
            bool keyleft = false;
            bool keyright = false;
        };
        
        /*int world[3][3] = {
            {},
            {},
            {},
        };*/

        struct window {
            int w;
            int h;
        } window;

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

        struct defaultRec {
            int x = 0;
            int y = 0;
            int w = 32;
            int h = 32;
        };
        
        struct render {
            int w;
            int h;
        };

        int handleFps();
        bool inputHandling(key& key, playerPos& plrPos, mouse& mouse);
        windowCoords getWindowCoords(ingameCoords& gameCoords, playerPos& plrPos);
        ingameCoords getIngameCoords(windowCoords& winCoords, playerPos& plrPos);
        mouse getFixedMouseCoords(mouse mouseCoords);
    protected:
};
/*
rect.w = std::floor(defRec.w * zoomFactor); // Skalierung der Breite basierend auf dem Zoom-Faktor
rect.h = std::floor(defRec.h * zoomFactor);
*/