#include "game.h"
#include "world.h"
#include "texture.h"

#include <iostream>
//#include <string.h>
#include <cmath>

#ifdef ANDROID
#include <android/log.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

SDL_Rect rect;

bool game::startGame(SDL_Window* mainWindow) {
    rect.w = 32;
    rect.h = 32;

    SDL_Renderer* mainRenderer;
    mainRenderer = SDL_GetRenderer(mainWindow);
    SDL_SetRenderDrawBlendMode(mainRenderer, SDL_BLENDMODE_BLEND);

    /*SDL_Surface* surface;
#ifdef ANDROID
    surface = SDL_LoadBMP("dirt.bmp");
#else
    surface = SDL_LoadBMP("../dirt.bmp");
#endif
    texture texture;
    texture.dirt = SDL_CreateTextureFromSurface(mainRenderer, surface);
    //SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_FreeSurface(surface);

    if(texture.dirt == NULL)
        return false;
    
#ifdef ANDROID
    surface = SDL_LoadBMP("grass.bmp");
#else
    surface = SDL_LoadBMP("../grass.bmp");
#endif
    texture.grass = SDL_CreateTextureFromSurface(mainRenderer, surface);
    SDL_FreeSurface(surface);

    if(texture.grass == NULL)
        return false;*/

    texture::createTexture("GRASS_TEXTURE", GRASS_TEXTURE_FILE, mainRenderer);
    if(!texture::createTexture("DIRT_TEXTURE", DIRT_TEXTURE_FILE, mainRenderer))
        return false;
    texture::createTexture("WOOD_CHEST_TEXTURE", WOOD_CHEST_TEXTURE_FILE, mainRenderer);

    SDL_Texture* texture;

    key key;
    mouse mouse;
    ingameCoords coords;
    windowCoords winCoords;
    playerPos plrPos;
    defaultRec defRec;
    render render;
    world::groundTile tile;
    world::buildingTile buildingTile;
    
    gameRunning = true;
    world::genTestBuilding();

    while(gameRunning) {
        handleFps();
        #ifdef ANDROID
        __android_log_print(3, "org.libsdl.app", "fps: %i", fps);
        #else
        std::cout << fps << std::endl;
        #endif
        if(!inputHandling(key, plrPos, mouse))
            gameRunning = false;

        SDL_GetWindowSize(mainWindow, &window.w, &window.h);

        SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mainRenderer);
        SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 255);

        /*
        for (const auto& [key, tile] : world::tileMap) {
            coords.x = key.first;
            coords.y = key.second;

            winCoords = getWindowCoords(coords, plrPos);
            rect.x = winCoords.x;
            rect.y = winCoords.y;
            rect.w = defRec.w * zoomFactor; // Skalierung der Breite basierend auf dem Zoom-Faktor
            rect.h = defRec.h * zoomFacto    r; // Skalierung der Höhe basierend auf dem Zoom-Faktor

            SDL_RenderCopy(mainRenderer, texture, NULL, &rect);
        }
        */
        /*
        int test = 0;
        for(const auto& [key, tile] : world::tileMap) {
            test++;
        }
        __android_log_print(3, "org.libsdl.app", "cashed tiles: %i", test);
        */
        
        render.w = std::floor((window.w / (defRec.w * zoomFactor)) / 2) + 2; //+2 damit man die tiles nicht am rand verschwinden lässt
        render.h = std::floor((window.h / (defRec.h * zoomFactor)) / 2) + 2;
        
        for(int i = -render.w; i <= render.w; i++) {
            for(int f = -render.h; f <= render.h; f++) {
                coords.x = i + std::floor(plrPos.x);
                coords.y = f + std::floor(plrPos.y);
                rect.w = std::floor(defRec.w * zoomFactor);
                rect.h = std::floor(defRec.h * zoomFactor);

                tile = world::getTile(coords.x, coords.y);
                
                winCoords = getWindowCoords(coords, plrPos);
                rect.x = winCoords.x;
                rect.y = winCoords.y;
                rect.w = std::floor(defRec.w * zoomFactor); // Skalierung der Breite basierend auf dem Zoom-Faktor
                rect.h = std::floor(defRec.h * zoomFactor); // Skalierung der Höhe basierend auf dem Zoom-Faktor

                if(tile.id == 1)
                    texture = texture::getTexture("GRASS_TEXTURE");
                else
                    texture = texture::getTexture("DIRT_TEXTURE");

                SDL_RenderCopy(mainRenderer, texture, NULL, &rect);

                buildingTile = world::getBuildingTile(coords.x, coords.y);
                rect.x = std::floor(winCoords.x + ((defRec.w - buildingTile.size.w) * zoomFactor) / 2);
                rect.y = std::floor(winCoords.y + ((defRec.h - buildingTile.size.h) * zoomFactor) / 2);
                rect.w = std::floor(buildingTile.size.w * zoomFactor);
                rect.h = std::floor(buildingTile.size.h * zoomFactor);
                if(buildingTile.id == 1) {
                    texture = texture::getTexture("WOOD_CHEST_TEXTURE");
                    SDL_RenderCopy(mainRenderer, texture, NULL, &rect);
                }
                
                
            }
        }

        
        
        






       /* coords.x = 0;
        coords.y = 0;

        winCoords = getWindowCoords(coords, plrPos);
        rect.x = winCoords.x;
        rect.y = winCoords.y;
        rect.w = 64 * zoomFactor; // Skalierung der Breite basierend auf dem Zoom-Faktor
        rect.h = 64 * zoomFactor; // Skalierung der Höhe basierend auf dem Zoom-Faktor

        SDL_RenderCopy(mainRenderer, texture, NULL, &rect);*/
        
        rect.w = std::floor(defRec.w * zoomFactor);
        rect.h = std::floor(defRec.h * zoomFactor);
        winCoords.x = mouse.x;
        winCoords.y = mouse.y;
        coords = getIngameCoords(winCoords, plrPos);

        // Runde auf ganze Zahlen, um die Tile-Position zu bestimmen
        coords.x = std::floor(coords.x);
        coords.y = std::floor(coords.y);

        winCoords = getWindowCoords(coords, plrPos);

        rect.x = winCoords.x;
        rect.y = winCoords.y;
        rect.w = std::floor(defRec.w * zoomFactor);
        rect.h = std::floor(defRec.h * zoomFactor);

        SDL_RenderDrawRect(mainRenderer, &rect);

        SDL_RenderPresent(mainRenderer);
    }

    if(gameRunning)
        return false;

    return true;
}

//fixed "ingame" pos!
game::mouse game::getFixedMouseCoords(mouse mouseCoords) {
    mouse fixedMouse;
    return fixedMouse;
}

game::windowCoords game::getWindowCoords(ingameCoords& gameCoords, playerPos& plrPos) {
    windowCoords winCoords;
    // Berechnung der neuen Position basierend auf dem Zoom-Faktor
    winCoords.x = (gameCoords.x - plrPos.x) * static_cast<float>(rect.w) + window.w / 2;
    winCoords.y = (gameCoords.y - plrPos.y) * static_cast<float>(rect.h) + window.h / 2;
    return winCoords;
}

game::ingameCoords game::getIngameCoords(windowCoords& winCoords, playerPos& plrPos) {
    ingameCoords coords;
    // Berechnung der neuen Ingame-Koordinaten basierend auf dem Zoom-Faktor
    coords.x = ((winCoords.x - window.w / 2) / static_cast<float>(rect.w)) + plrPos.x;
    coords.y = ((winCoords.y - window.h / 2) / static_cast<float>(rect.h)) + plrPos.y;
    return coords;
}

int game::handleFps() {
    int frameDelay = (1000 / 60) - (SDL_GetTicks64() - deltaTime);
    if(frameDelay > 0)
        SDL_Delay(frameDelay);
    fps = 1000 / (SDL_GetTicks64() - deltaTime);
    deltaTime = SDL_GetTicks64();
    return fps;
}

bool game::inputHandling(key& key, playerPos& plrPos, mouse& mouse) {
    SDL_Event inputEvent;
#ifdef ANDROID
    SDL_TouchID touchDevice = SDL_GetTouchDevice(1);
#endif
    while(SDL_PollEvent(&inputEvent)) {
        switch(inputEvent.type) {
            case SDL_QUIT:
                return false;
                break;

            case SDL_WINDOWEVENT:
                if(inputEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    //updateScreen = true;
                break;

#ifdef ANDROID
            case SDL_MULTIGESTURE:
                isMultigesture = true;
                if( fabs( inputEvent.mgesture.dDist ) > 0.001 ) {
                    if( inputEvent.mgesture.dDist > 0 ) {
                        zoomFactor += zoomFactor / 25.0f;

                    } else {
                        zoomFactor -= zoomFactor / 25.0f;

                    }
                    
                    if (zoomFactor < 0.5) zoomFactor = 0.5;
                    if (zoomFactor > 10) zoomFactor = 10;
                    //__android_log_print(3, "SDL", "Maus: %f", coords.x);
                }
                break;

            case SDL_FINGERDOWN:

                break;

            case SDL_FINGERUP:
                isMultigesture = false;
                fingerUp = true;
                break;

            case SDL_FINGERMOTION:
                if (isMultigesture || SDL_GetNumTouchFingers(touchDevice) > 1 || inputEvent.tfinger.fingerId != 0)
                    break;

                if(!fingerUp) {
                    plrPos.x -= ((inputEvent.tfinger.x * window.w) - mouse.x) / (32 * (zoomFactor));
                    plrPos.y -= ((inputEvent.tfinger.y * window.h) - mouse.y) / (32 * (zoomFactor));
                }

                //__android_log_print(3, "org.libsdl.app", "plrPos: %f", plrPos.x);

                mouse.x = inputEvent.tfinger.x * window.w;
                mouse.y = inputEvent.tfinger.y * window.h;
                fingerUp = false;
                break;

#else
            case SDL_KEYDOWN:
                switch(inputEvent.key.keysym.sym) {
                    case SDLK_LEFT:
                        key.keyleft = true;
                        break;

                    case SDLK_RIGHT:
                        key.keyright = true;
                        break;

                    case SDLK_UP:
                        key.keyup = true;
                        break;

                    case SDLK_DOWN:
                        key.keydown = true;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch(inputEvent.key.keysym.sym) {
                    case SDLK_LEFT:
                        key.keyleft = false;
                        break;

                    case SDLK_RIGHT:
                        key.keyright = false;
                        break;

                    case SDLK_UP:
                        key.keyup = false;
                        break;

                    case SDLK_DOWN:
                        key.keydown = false;
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                mouse.x = inputEvent.motion.x;
                mouse.y = inputEvent.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(inputEvent.button.button == SDL_BUTTON_LEFT) {
                    std::cout << "MouseLeftButtonDown" << std::endl;
                    world::buildingTile blding;
                    ingameCoords coords;
                    windowCoords winCoords;
                    blding.id = 1;
                    blding.size.w = 28;
                    blding.size.h = 28;
                    winCoords.x = mouse.x;
                    winCoords.y = mouse.y;
                    coords = getIngameCoords(winCoords, plrPos);
                    world::createBuilding(std::floor(coords.x), std::floor(coords.y), blding);
                } else if(inputEvent.button.button == SDL_BUTTON_RIGHT) {
                    std::cout << "MouseRightButtonDown" << std::endl;
                } else if(inputEvent.button.button == SDL_BUTTON_MIDDLE) {
                    std::cout << "MouseMiddleButtonDown" << std::endl;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if(inputEvent.button.button == SDL_BUTTON_LEFT) {
                    std::cout << "MouseLeftButtonUp" << std::endl;
                } else if(inputEvent.button.button == SDL_BUTTON_RIGHT) {
                    std::cout << "MouseRightButtonUp" << std::endl;
                } else if(inputEvent.button.button == SDL_BUTTON_MIDDLE) {
                    std::cout << "MouseMiddleButtonUp" << std::endl;
                }
                break;

            case SDL_MOUSEWHEEL:
                int y = inputEvent.wheel.y;
                if(inputEvent.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
                    y = -y; // entweder 1 oder -1

                zoomFactor += y * (zoomFactor / 10.0f);
                // Begrenzen Sie den Zoom-Faktor auf einen sinnvollen Bereich
                if (zoomFactor < 0.5) zoomFactor = 0.5;
                if (zoomFactor > 6) zoomFactor = 6;

                //std::cout << zoomFactor << " : " << rect.w << " " << rect.h << std::endl;
                break;
#endif
        }
    }

    if(key.keydown) {
        plrPos.y += 0.05;
    }

    if(key.keyup) {
        plrPos.y -= 0.05;
    }

    if(key.keyleft) {
        plrPos.x -= 0.05;
    }

    if(key.keyright) {
        plrPos.x += 0.05;
    }

    return true;
}