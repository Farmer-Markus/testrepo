#include <SDL2/SDL.h>
#include <string>

#include "texture.h"



Textures::Textures() {
    std::unordered_map<std::string, SDL_Texture*> textures;
}

Textures::~Textures() {
    textures.clear();
}

bool Textures::createTexture(const std::string textureId, SDL_Renderer* renderer) {
        std::string texturePath;
        texturePath = TEXTURE_PATH + textureId + ".bmp";
        SDL_Surface* surface;
        SDL_Texture * texture;
        surface = SDL_LoadBMP(texturePath.c_str());
        if (!surface) {
            return false;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(!texture) {
            return false;
        }
        textures[textureId] = texture; // Textur speichern
        return true;
    }

SDL_Texture* Textures::getTexture(const std::string& textureId) {
        return textures[textureId];
    }