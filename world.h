#pragma once

#include <unordered_map>
#include <utility>
#include <string>

//using coordinate = std::pair<int, int>; // x, y Koordinaten, coordinate.first = x, coordinate.secong = y

namespace std {//echt keine ahnung wie das hier funktioniert aber wirt schon richtig sein -_-
    template <>
    struct hash<std::pair<int, int>> {
        std::size_t operator()(const std::pair<int, int>& pair) const {
            auto hash1 = std::hash<int>{}(pair.first);
            auto hash2 = std::hash<int>{}(pair.second);
            return hash1 ^ (hash2 << 1); // Kombinieren der Hash-Werte
        }
    };
}

class world {
    private:
    static int genWorld(int x, int y);

    public:
    
    struct groundTile {
        std::string id;
    };

    struct buildingTile {
        std::string id = "";
        struct size {
            int w;
            int h;
        } size;
    };

    static groundTile getTile(int x, int y);
    static buildingTile getBuildingTile(int x, int y);

    /*static void genTestBuilding();*/
    static void saveBuilding(int x, int y, buildingTile tile);

    protected:
    static std::unordered_map<std::pair<int, int>, world::groundTile> tileMap; //für den compiler
    static std::unordered_map<std::pair<int, int>, world::buildingTile> buildingTileMap;
};