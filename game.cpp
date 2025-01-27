#include "game.h"
#include "world.h"
#include "texture.h"
#include "building.h"

#include <iostream>
//#include <string.h>
#include <cmath>
#include <optional>

#ifdef ANDROID
#include <android/log.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>


/*int threadFunctionWrapper(void* data) {
    game* g = static_cast<game*>(data);  // Casten des übergebenen Zeigers auf game*
    return g->threadFunction(data);  // Aufruf der nicht-statischen Methode
}*/


SDL_FRect gndRect; //ground rectangle
SDL_FRect bldingRect; //building rectangle
SDL_FRect mrsRect; //mouse cursor rectangle

bool game::startGame(SDL_Window* mainWindow) {
    SDL_Renderer* mainRenderer;
    mainRenderer = SDL_GetRenderer(mainWindow);
    //SDL_SetRenderDrawBlendMode(mainRenderer, SDL_BLENDMODE_BLEND);

    Textures texture;
    
    texture.createTexture("grass-ground", mainRenderer);
    if(!texture.createTexture("dirt-ground", mainRenderer))
        return false;
    texture.createTexture("wooden-chest", mainRenderer);

    SDL_Texture* gndTexture;
    SDL_Texture* bldingTexture;
    Buildings building;

    key keys;
    mouse mouse;
    ingameCoords coords;
    windowCoords winCoords;
    ingameChunkCoords cCoords;
    //render renderSize; //render as far as the screen is
    world::groundTile tile;
    world::buildingTile buildingTile;
    SDL_Texture *textureTest;
    world::chunk chunk;
    


    /*SDL_Thread* thread1;
    game* g = this;
    thread1 = SDL_CreateThread(threadFunctionWrapper, "THREAD1", g);*/


    gndRect.w = defRec.w;
    gndRect.h = defRec.h;
    bool isBuilding = false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    //gndTexture = texture.getTexture("grass-ground"); //Performance Problem
    
    gameRunning = true;
    while(gameRunning) {
        handleFps();
        //SDL_Delay(1000);
        #ifdef ANDROID
        __android_log_print(3, "org.libsdl.app", "fps: %i", fps);
        #else
        std::cout << fps << std::endl;
        #endif
        if(!inputHandling(keys, mouse, building))
            gameRunning = false;

        SDL_GetWindowSize(mainWindow, &window.w, &window.h);

        SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mainRenderer);
        SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 255);
        SDL_SetRenderTarget(mainRenderer, textureTest);
        
        int visibleChunksX = std::ceil(window.w / (defRec.w * cSize * zoomFactor)) + 2; //um chunks nicht am rand auftauchen zu sehen
        int visibleChunksY = std::ceil(window.h / (defRec.h * cSize * zoomFactor)) + 2;
        //std::cout << visibleChunksX << " : " << visibleChunksY << std::endl;

        // Berechne die Start- und Endkoordinaten der sichtbaren Chunks//
        int startX = std::floor(plrPos.x / cSize) - visibleChunksX / 2;  //
        int endX = std::ceil(plrPos.x / cSize) + visibleChunksX / 2;       // by github copilot... thx :D
        int startY = std::floor(plrPos.y / cSize) - visibleChunksY / 2;  //
        int endY = std::ceil(plrPos.y / cSize) + visibleChunksY / 2;   //

        //Performance Vergleiche: beides = 85% | ohne texture = 71% | ohne chunk saving = 85% | ohne alles = 49%

        for (int chunkX = startX; chunkX <= endX; chunkX++) {
            for (int chunkY = startY; chunkY <= endY; chunkY++) {
                chunk = world::getChunk(chunkX, chunkY); //Performance Problem
                gndRect.w = std::floor(defRec.w * zoomFactor);
                gndRect.h = std::floor(defRec.h * zoomFactor);

                for (int cTileX = 0; cTileX < cSize; cTileX++) {
                    for (int cTileY = 0; cTileY < cSize; cTileY++) {
                        coords.x = (chunkX * cSize) + cTileX;
                        coords.y = (chunkY * cSize) + cTileY;

                        winCoords = getWindowCoords(coords, plrPos, gndRect);
                        gndRect.x = winCoords.x;
                        gndRect.y = winCoords.y;

                        gndTexture = texture.getTexture(chunk.tiles[cTileX][cTileY]); //Performance Problem
                        SDL_RenderCopyF(mainRenderer, gndTexture, NULL, &gndRect);
                    }
                }
            }
        }
                
                /*coords.x = i + std::floor(plrPos.x);
                coords.y = f + std::floor(plrPos.y);
                gndRect.w = std::floor(defRec.w * zoomFactor);
                gndRect.h = std::floor(defRec.h * zoomFactor);
                
                winCoords = getWindowCoords(coords, plrPos, gndRect);
                gndRect.x = winCoords.x;
                gndRect.y = winCoords.y;
                gndRect.w = defRec.w * zoomFactor + 1; // Skalierung der Breite basierend auf dem Zoom-Faktor. + 1, damit kacheln etwas überlappen und es keine sichtbaren fehler(streifen) zwischen den kacheln gibt
                gndRect.h = defRec.h * zoomFactor + 1;*/ // kann auch an den anfang der schleife gelegt werden um resourcen zu sparen

                /*
                isBuilding = world::checkForBuildingTile(coords.x, coords.y); //if buildingtile exists on this location, do
                if(isBuilding) {
                    bldingRect.x = winCoords.x + ((defRec.w - buildingTile.size.w) * zoomFactor) / 2;
                    bldingRect.y = winCoords.y + ((defRec.h - buildingTile.size.h) * zoomFactor) / 2;
                    bldingRect.w = buildingTile.size.w * zoomFactor;
                    bldingRect.h = buildingTile.size.h * zoomFactor;
                }

                if(isBuilding) {
                    buildingTile = world::getBuildingTile(coords.x, coords.y); //check for buildings
                    bldingTexture = textures.getTexture(buildingTile.id);
                }
                */

                //tile = world::getTile(coords.x, coords.y);
                /*gndTexture = textures.getTexture("grass-ground");
                SDL_RenderCopyF(mainRenderer, gndTexture, NULL, &gndRect);*/

                /*
                if(isBuilding)
                    SDL_RenderCopyF(mainRenderer, bldingTexture, NULL, &bldingRect);
                */

                //wait for thread and draw its results!
                /*
                SDL_SemPost(semaphore); // NOW DRAW THREAD!
                    if(thread.isBuilding) {
                        buildingTile = world::getBuildingTile(thread.coords.x, thread.coords.y); //check for buildings
                        bldingTexture = textures.getTexture(buildingTile.id);
                    }

                    tile = world::getTile(thread.coords.x, thread.coords.y);
                    gndTexture = textures.getTexture(tile.id);
                    SDL_RenderCopyF(mainRenderer, gndTexture, NULL, &thread.gndRect);
                    /*std::cout << thread.gndRect.x << "x" << thread.gndRect.y << std::endl;
                    std::cout << thread.gndRect.w << "x" << thread.gndRect.h << std::endl;
                    std::cout << "                                         " << std::endl;*/

                    /*
                    if(thread.isBuilding)
                        SDL_RenderCopyF(mainRenderer, bldingTexture, NULL, &thread.bldingRect);
                
                    //after that message the thread to continue calculating!!
                    //SDL_SemPost(semaphore);
                    */
                   /*
            }
        }
*/
        
        mrsRect.w = std::floor(defRec.w * zoomFactor);
        mrsRect.h = std::floor(defRec.h * zoomFactor);
        winCoords.x = mouse.x;
        winCoords.y = mouse.y;
        coords = getIngameCoords(winCoords, plrPos, mrsRect);

        coords.x = std::floor(coords.x);
        coords.y = std::floor(coords.y);

        winCoords = getWindowCoords(coords, plrPos, mrsRect);

        mrsRect.x = winCoords.x;
        mrsRect.y = winCoords.y;

        SDL_RenderDrawRectF(mainRenderer, &mrsRect);

        SDL_SetRenderTarget(mainRenderer, NULL);
        SDL_RenderCopyF(mainRenderer, textureTest, NULL, &gndRect);


        SDL_RenderPresent(mainRenderer);
    }

    if(gameRunning)
        return false;

    return true;
}

/*oid game::renderChunk(int chunkX, int chunkY, SDL_Renderer* &renderer, ingameCoords &coords, windowCoords winCoords) {
    world::chunk chunk;
    Textures texture;
    SDL_Texture* gndTexture;
    chunk = world::getChunk(chunkX,chunkY);
    gndRect.w = std::floor(defRec.w * zoomFactor);
    gndRect.h = std::floor(defRec.h * zoomFactor);
    for(int i = 0; i < 16; i++) {
        for(int f = 0; f < 16; f++) {
            coords.x = i + std::floor(plrPos.x);
            coords.y = f + std::floor(plrPos.y);

            winCoords = getWindowCoords(coords, plrPos, gndRect);
            gndRect.x = 200;
            gndRect.y = 200;
            gndRect.w = 80; // Skalierung der Breite basierend auf dem Zoom-Faktor. + 1, damit kacheln etwas überlappen und es keine sichtbaren fehler(streifen) zwischen den kacheln gibt
            gndRect.h = 80;

            gndTexture = texture.getTexture("grass-ground"); //chunk.tiles[i][f]
            SDL_RenderCopyF(renderer, gndTexture, NULL, &gndRect);
        }
    }
}*/

game::ingameChunkCoords game::getIngameChunkCoords(ingameCoords& coords) {
    ingameChunkCoords cCoords;
    cCoords.x = static_cast<int>(coords.x / cSize);
    cCoords.y = static_cast<int>(coords.y / cSize);
    return cCoords;
}

game::windowCoords game::getWindowCoords(ingameCoords& gameCoords, playerPos& plrPos, SDL_FRect& rect) {
    windowCoords winCoords;
    // Berechnung der neuen Position basierend auf dem Zoom-Faktor
    winCoords.x = (gameCoords.x - plrPos.x) * static_cast<float>(rect.w) + window.w / 2;
    winCoords.y = (gameCoords.y - plrPos.y) * static_cast<float>(rect.h) + window.h / 2;
    return winCoords;
}

game::ingameCoords game::getIngameCoords(windowCoords& winCoords, playerPos& plrPos, SDL_FRect& rect) {
    ingameCoords coords;
    // Berechnung der neuen Ingame-Koordinaten basierend auf dem Zoom-Faktor
    coords.x = ((winCoords.x - window.w / 2) / static_cast<float>(rect.w)) + plrPos.x;
    coords.y = ((winCoords.y - window.h / 2) / static_cast<float>(rect.h)) + plrPos.y;
    return coords;
}

int game::handleFps() {
    Uint64 currentTicks = SDL_GetTicks64();
    int frameTime = currentTicks - deltaTime;
    int frameDelay = (1000 / 60) - frameTime;
    if(frameDelay > 0)
        SDL_Delay(frameDelay);
    if(SDL_GetTicks64() - deltaTime > 0)
        fps = 1000 / (SDL_GetTicks64() - deltaTime);
    
    deltaTime = currentTicks;
    return fps;
}

bool game::inputHandling(key& key, mouse& mouse, Buildings& building) {
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

            case SDL_FINGERDOWN:
                windowCoords winCoords = {mouse.x, mouse.y};
                ingameCoords coords = getIngameCoords(winCoords, plrPos, bldingRect);
                building.newBuilding("wooden-chest", coords);
                break;

            case SDL_FINGERUP:
                isMultigesture = false;
                fingerUp = true;
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
                    
                    windowCoords winCoords = {mouse.x, mouse.y};
                    ingameCoords coords = getIngameCoords(winCoords, plrPos, mrsRect);
                    building.newBuilding("wooden-chest", coords);
                    
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