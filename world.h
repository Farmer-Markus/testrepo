#pragma once
#include "defines.h"

#include <unordered_map>
#include <utility>
#include <string>
#include <vector>

//using coordinate = std::pair<int, int>; // x, y Koordinaten, coordinate.first = x, coordinate.secong = y

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        std::size_t operator()(const std::pair<int, int>& pair) const {
            // Kombinieren der Hash-Werte mit einer besseren Methode
            return std::hash<int>{}(pair.first) ^ (std::hash<int>{}(pair.second) << 1);
        }
    };
}

class world {
    private:
    static int genWorld(int x, int y);

    public:
    struct chunk {
        //int size = 16;
        std::vector<std::vector<std::string>> tiles;
        chunk() : tiles(cSize, std::vector<std::string>(cSize, "empty")) {}    
    };
    
    struct groundTile {
        std::string id = "";
    };

    struct buildingTile {
        std::string id = "";
        struct size {
            int w;
            int h;
        } size;
    };

    static chunk getChunk(int chunkX, int chunkY); //testing
    static groundTile getTile(int chunkX, int chunkY, int x, int y);
    static buildingTile getBuildingTile(int x, int y);
    static bool checkForBuildingTile(int x, int y);
    static std::pair<int, int> getBuildingTileSize(int x, int y);

    /*static void genTestBuilding();*/
    static void saveBuilding(int x, int y, buildingTile tile);

    protected:
    //static std::unordered_map<std::pair<int, int>, world::groundTile> tileMap; //für den compiler
    static std::unordered_map<std::pair<int, int>, chunk> chunkWorld;
    static std::unordered_map<std::pair<int, int>, world::buildingTile> buildingTileMap;
};