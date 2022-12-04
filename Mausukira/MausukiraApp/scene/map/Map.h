#ifndef MAP_H
#define MAP_H

#include "../../states_stack/SharedContext.h"
#include "DungeonGenerator.h"
#include "MapContext.h"
#include "SFML/System/Time.hpp"
#include "TileHelper.h"
#include <array>
#include <bitset>
#include <unordered_map>

struct Tile;
struct TileModel;

using TileModels = std::unordered_map<std::string, std::unique_ptr<TileModel>>;
using TileMap = std::array<std::unique_ptr<Tile>, 1024>;

class Map
{
public:
    Map(SharedContext& sharedCtx, MapContext& mapContext);
    ~Map() = default;

    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);

private:
    void loadTiles();
    void tileMap();
    void setTile(int x, int y, const std::string& id);
    Tile& getTile(const unsigned int& x, const unsigned int& y);
    unsigned int convertCoordsTo1D(const unsigned int& x, const unsigned int& y) const;
    std::string chooseWallTile(const std::bitset<8>& tileBitmask);
    std::string chooseTile(const int& tileType);
    void drawTiles(sf::RenderWindow& window);
    bool isValidForCalculations(const sf::Vector2i& tile);
    void isWallTile(const sf::Vector2i& currentTile);
    void isNotWallTile(const sf::Vector2i& currentTile, const int& currentTileType);
    void setWallTile(const sf::Vector2i& currentTile, int wallValue);

private:
    TileModels mTileModels;
    SharedContext& mSharedCtx;
    MapContext& mMapContext;
    DungeonGenerator mDungeonGenerator;

    std::unordered_map<uint8_t, std::string> mWallTiles{
        {255, "WALL_0_0"}, {0, "WALL_0_1"},   {80, "WALL_0_2"},  {8, "WALL_0_3"},
        {2, "WALL_0_4"},   {64, "WALL_0_5"},  {72, "WALL_0_6"},  {16, "WALL_0_7"},

        {18, "WALL_1_0"},  {24, "WALL_1_1"},  {66, "WALL_1_2"},  {218, "WALL_1_3"},
        {23, "WALL_1_4"},  {11, "WALL_1_5"},  {104, "WALL_1_6"}, {248, "WALL_1_7"},

        {208, "WALL_2_0"}, {214, "WALL_2_1"}, {107, "WALL_2_2"}, {127, "WALL_2_3"},
        {63, "WALL_2_4"},  {223, "WALL_2_5"}, {254, "WALL_2_6"}, {90, "WALL_2_7"},

        {22, "WALL_3_0"},  {210, "WALL_3_1"}, {31, "WALL_3_2"},  {251, "WALL_3_3"},
        {216, "WALL_3_4"}, {27, "WALL_3_5"},  {10, "WALL_3_6"},  {86, "WALL_3_7"},

        {120, "WALL_4_0"}, {250, "WALL_4_1"}, {106, "WALL_4_2"}, {75, "WALL_4_3"},
        {82, "WALL_4_4"},  {222, "WALL_4_5"}, {74, "WALL_4_6"},  {74, "WALL_4_7"},

        {88, "WALL_5_0"},  {26, "WALL_5_1"},  {30, "WALL_5_2"},  {126, "WALL_5_3"},
        {219, "WALL_5_4"}, {123, "WALL_5_5"}, {95, "WALL_5_6"}};
};

#endif// MAP_H
