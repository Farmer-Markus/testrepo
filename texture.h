#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

#include "textureDefines.h"


class Textures {
    private:
    std::unordered_map<std::string, SDL_Texture*> textures;

    protected:

    public:
    Textures();
    ~Textures();
    

    bool createTexture(const std::string textureId, SDL_Renderer* renderer);
    SDL_Texture* getTexture(const std::string& textureId);
};