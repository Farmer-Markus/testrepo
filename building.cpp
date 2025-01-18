#include "building.h"
#include "game.h"
#include "world.h"

#include <iostream>

//std::unordered_map<std::string, world::buildingTile> buildingTileRegister;


void Buildings::newBuilding(std::string buildingId, game::ingameCoords coords) {
    world::buildingTile tile;
    
    auto buildingRegister = buildingTileRegister.find(buildingId);
    if(buildingRegister != buildingTileRegister.end()) {
        tile = buildingRegister->second;
        //std::cout << "DEBUG:" << coords.x << std::endl;

        world::saveBuilding(std::floor(coords.x), std::floor(coords.y), tile);

    } else
        return;
}

void Buildings::addBuildingToRegister(std::string buildingId, int buildingWith, int buildingHeigh) {
    world::buildingTile tile;
    tile.id = buildingId;
    tile.size.w = buildingWith;
    tile.size.h = buildingHeigh;

    buildingTileRegister[buildingId] = tile;
}