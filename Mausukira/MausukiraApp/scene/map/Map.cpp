#include "Map.h"
#include "Tile.h"
#include "TileHelper.h"
#include <bitset>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <json/json.h>

Map::Map(SharedContext& sharedCtx, MapContext& mapContext)
    : mSharedCtx(sharedCtx)
    , mMapContext(mapContext)
    , mDungeonGenerator(mMapContext)
{
    loadTiles();
    mDungeonGenerator.procedurallyGenerateMap();
    tileMap();
}

void Map::tileMap()
{
    for (int x = 0; x < MAP_SIZE_X; ++x)
    {
        for (int y = 0; y < MAP_SIZE_Y; ++y)
        {
            sf::Vector2i currentTile{x, y};
            auto currentTileType = mMapContext.mMap[currentTile.x][currentTile.y];

            if (!currentTileType == NONE)
            {
                isNotWallTile(currentTile, currentTileType);
            }
            else
            {
                isWallTile(currentTile);
            }
        }
    }
}
void Map::isNotWallTile(const sf::Vector2i& currentTile, const int& currentTileType)
{
    setTile(currentTile.x, currentTile.y, chooseTile(currentTileType));
}
void Map::isWallTile(const sf::Vector2i& currentTile)
{

    auto TOP_TILE = isValidForCalculations(currentTile + tile_helper::neighbouringFourTiles[0]);
    auto LEFT_TILE = isValidForCalculations(currentTile + tile_helper::neighbouringFourTiles[1]);
    auto RIGHT_TILE = isValidForCalculations(currentTile + tile_helper::neighbouringFourTiles[2]);
    auto BOTTOM_TILE = isValidForCalculations(currentTile + tile_helper::neighbouringFourTiles[3]);

    // Corners are only relevant when its primary neighbours have a true value
    auto TOP_LEFT_TILE = (TOP_TILE && LEFT_TILE)
                             ? isValidForCalculations(currentTile + tile_helper::cornerTiles[0])
                             : 0;
    auto TOP_RIGHT_TILE = (TOP_TILE && RIGHT_TILE)
                              ? isValidForCalculations(currentTile + tile_helper::cornerTiles[1])
                              : 0;
    auto BOTTOM_LEFT_TILE = (BOTTOM_TILE && LEFT_TILE)
                                ? isValidForCalculations(currentTile + tile_helper::cornerTiles[2])
                                : 0;
    auto BOTTOM_RIGHT_TILE = (BOTTOM_TILE && RIGHT_TILE)
                                 ? isValidForCalculations(currentTile + tile_helper::cornerTiles[3])
                                 : 0;

    auto wallValue = TOP_LEFT_TILE * 1 + TOP_TILE * 2 + TOP_RIGHT_TILE * 4 + LEFT_TILE * 8 +
                     RIGHT_TILE * 16 + BOTTOM_LEFT_TILE * 32 + BOTTOM_TILE * 64 +
                     BOTTOM_RIGHT_TILE * 128;

    setWallTile(currentTile, wallValue);
}

void Map::setWallTile(const sf::Vector2i& currentTile, int wallValue)
{
    if (mWallTiles.contains(wallValue))
    {
        setTile(currentTile.x, currentTile.y, mWallTiles.at(wallValue));
    }
    else
    {
        setTile(currentTile.x, currentTile.y, "WALL_2_4");
    }
}

bool Map::isValidForCalculations(const sf::Vector2i& tile)
{
    if (!tile_helper::isInBorders(tile))
    {
        return true;
    }
    return (mMapContext.mMap[tile.x][tile.y] == NONE) ? true : false;
}

std::string Map::chooseTile(const int& tileType)
{
    switch (tileType)
    {
        case ROOM:
        case HALL: return "FLOOR"; break;
        default: return "FLOOR";
    }
}

void Map::setTile(int x, int y, const std::string& id)
{
    mMapContext.mTileMap.at(convertCoordsTo1D(x, y)) =
        std::move(std::make_unique<Tile>(mTileModels.at(id).get(), x, y));
}

void Map::loadTiles()
{
    mSharedCtx.textureManager.load("TILES", "resources/tiles/tileset.png");
    Json::Value tiles;
    std::ifstream tileFile("resources/tiles/tiles.json", std::ifstream::binary);
    try
    {
        if (tileFile.fail())
        {
            throw std::runtime_error("ERR: Map::loadTiles - No tiles.json exists");
        }
        tileFile >> tiles;
        auto tileID = 0;
        for (Json::Value::ArrayIndex index = 0; index != tiles.size(); index++)
        {
            std::string name = tiles[index]["name"].asString();
            bool isDeadly = tiles[index]["deadly"].asBool();

            auto tileModel =
                std::make_unique<TileModel>(mSharedCtx.textureManager, isDeadly, name, tileID);
            mTileModels.insert({name, std::move(tileModel)});
            ++tileID;
        }
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}

unsigned int Map::convertCoordsTo1D(const unsigned int& x, const unsigned int& y) const
{
    return (x * MAP_SIZE_X) + y;
}

Tile& Map::getTile(const unsigned int& x, const unsigned int& y)
{
    auto tile = mMapContext.mTileMap.at(convertCoordsTo1D(x, y)).get();
    return *tile;
}

void Map::update(const sf::Time& deltaTime)
{
}

void Map::draw(sf::RenderWindow& window)
{
    drawTiles(window);
    mDungeonGenerator.drawDebugLines(window);
}

void Map::drawTiles(sf::RenderWindow& window)
{
    for (int x = 0; x < MAP_SIZE_X; ++x)
    {
        for (int y = 0; y < MAP_SIZE_Y; ++y)
        {
            Tile& tile = getTile(x, y);
            tile.draw(window);
        }
    }
}
