#include <iostream>

#include "main.h"
#include "game.h"
#include "building.h"

//Including SDL libraries
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_mixer.h>

//\param w window widh
//\param h window height
bool windowInit(int w, int h);
void destroyWindow(SDL_Window* window);
void createBuildingRegister();

SDL_Window* mainWindow;
SDL_Renderer* mainRenderer;


int main(int, char**){

    if(!windowInit(800,600)) {
        std::cerr << "Failed to initialize sdl renderer: " << SDL_GetError();
        return 0;
    }

    createBuildingRegister();
    
    game game;

    if(!game.startGame(mainWindow))
        std::cerr << "The game crashed \n";
    
    std::cout << "returning";
    
    destroyWindow(mainWindow);
    SDL_Quit();
    return 0;
}

bool windowInit(int w, int h) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return false;
    }
    
    mainWindow = SDL_CreateWindow("SDL2-Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_RESIZABLE);
    if(mainWindow == NULL){
        return false;
    }

    SDL_SetWindowMinimumSize(mainWindow, 400, 300);

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if(mainRenderer == NULL) {
        return false;
    }

    return true;
}

void destroyWindow(SDL_Window* window) {
    SDL_DestroyRenderer(SDL_GetRenderer(window));
    SDL_DestroyWindow(window);
}

void createBuildingRegister() {
    Buildings building;

    building.addBuildingToRegister("wooden-chest", 28, 28);
    building.addBuildingToRegister("iron-chest", 28, 28);
}