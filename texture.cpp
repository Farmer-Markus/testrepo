#include <SDL2/SDL.h>
#include <string>

#include "texture.h"

std::unordered_map<std::string, SDL_Texture*> texture::textures;

bool texture::createTexture(const std::string& textureId, const std::string& texturePath, SDL_Renderer* renderer) {
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

    SDL_Texture* texture::getTexture(const std::string& textureId) {
        return textures[textureId];
    }