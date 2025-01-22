#include <unordered_map>
#include <iostream>

#include "world.h"

//std::unordered_map<std::pair<int, int>, world::groundTile> world::tileMap; //zum speicher reservieren
std::unordered_map<std::pair<int, int>, world::chunk> world::chunkWorld;
std::unordered_map<std::pair<int, int>, world::buildingTile> world::buildingTileMap;

world::groundTile world::getTile(int chunkX, int chunkY, int x, int y) {
    
}

world::chunk world::getChunk(int chunkX, int chunkY) {
    chunk chunk;
    std::pair<int, int> coordinates = {chunkX, chunkY};
    auto it = chunkWorld.find(coordinates);
    if(it != chunkWorld.end()) {
        chunk = it->second;
        return chunk;
    } else {
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {
                if(std::rand() % 2 == 1) {
                    chunk.tiles[y][x] = "grass-ground";
                } else {
                    chunk.tiles[y][x] = "dirt-ground";
                }
            }
        }
        chunkWorld[{chunkX, chunkY}] = chunk;
        return chunk;
    }
}

/*
std::pair<int, int> coordinates = {x, y};
    auto it = tileMap.find(coordinates);
    groundTile tile;

    if (it != tileMap.end()) {
        // Wenn das Tile gefunden wurde
        tile = it->second;  // Das Tile befindet sich im `second` des Paares
        return tile;
    } else {
        if(std::rand() % 2 == 1) {
            tile.id = "grass-ground";
        } else {
            tile.id = "dirt-ground";
        }
        tileMap[{x, y}] = tile;
        
        return tile;
    }
*/


void world::saveBuilding(int x, int y, buildingTile tile) {
    buildingTileMap[{x, y}] = {tile};
}

bool world::checkForBuildingTile(int x, int y) {
    std::pair<int, int> coordinates = {x, y};
    auto it = buildingTileMap.find(coordinates);

    if (it != buildingTileMap.end())
        return true;

    return false;
}

std::pair<int, int> world::getBuildingTileSize(int x, int y) {
    std::pair<int, int> coordinates = {x, y};
    auto it = buildingTileMap.find(coordinates);
    buildingTile tile;
    int w;
    int h;

    if (it != buildingTileMap.end()) {
        tile = it->second;
        w = tile.size.w;
        h = tile.size.h;
    } else {
        w = 0;
        h = 0;
    }
    
    return {w, h};
}

world::buildingTile world::getBuildingTile(int x, int y) {
    std::pair<int, int> coordinates = {x, y};
    auto it = buildingTileMap.find(coordinates);
    buildingTile tile;

    if (it != buildingTileMap.end()) {
        tile = it->second;
        return tile;
    } else {
        return tile;
    }

}

int world::genWorld(int x, int y) {
    return 1;
}