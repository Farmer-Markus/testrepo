#include <unordered_map>
#include <iostream>

#include "world.h"

std::unordered_map<std::pair<int, int>, world::groundTile> world::tileMap; //zum speicher reservieren
std::unordered_map<std::pair<int, int>, world::buildingTile> world::buildingTileMap;

world::groundTile world::getTile(int x, int y) {
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
        tileMap[{x, y}] = {tile.id};
        
        return tile;
    }
}

/*void world::genTestBuilding() {
    buildingTile tile;
    tile.id = 1;
    tile.size.h = 28;
    tile.size.w = 28;
    
    buildingTileMap[{0, 0}] = {tile};
}*/

void world::saveBuilding(int x, int y, buildingTile tile) {
    buildingTileMap[{x, y}] = {tile};
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