#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

#include "textureDefines.h"


class texture {
    private:

    protected:

    public:
    static std::unordered_map<std::string, SDL_Texture*> textures;

    static bool createTexture(const std::string& textureId, const std::string& texturePath, SDL_Renderer* renderer);
    static SDL_Texture* getTexture(const std::string& textureId);
};