#pragma once

#include <string>
#include <optional>

#include "texture.h"
#include "world.h"
#include "game.h"

static std::unordered_map<std::string, world::buildingTile> buildingTileRegister;



class Buildings : protected world {
    private:    

    protected:

    public:
    //something like wooden-chest
    void newBuilding(std::string buildingId, game::ingameCoords coords);
    void addBuildingToRegister(std::string buildingId, int buildingWith, int buildingHeigh);
};