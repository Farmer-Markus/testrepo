#pragma once

#ifdef ANDROID
#define TEXTURE_PATH ""
#else
#define TEXTURE_PATH "../data/textures"
#endif
#define GRASS_TEXTURE_FILE TEXTURE_PATH"/grass.bmp"
#define DIRT_TEXTURE_FILE TEXTURE_PATH"/dirt.bmp"
#define WOOD_CHEST_TEXTURE_FILE TEXTURE_PATH"/wooden-chest.bmp"