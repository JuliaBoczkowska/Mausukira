#include "Map.h"
#include "Tile.h"
#include <json/json.h>
#include <fstream>
#include <iostream>

Map::Map(SharedContext* sharedCtx)
    : mSharedCtx(sharedCtx)
{
    mSharedCtx->textureManager->load("TILE", "resources/tiles/tileset.jpg");
    loadTiles();

    std::array<std::array<int, 32>, 32> procedurallyGeneratedMap = mTerrainGenerator.procedurallyGenerateMap();
    for (int x = 0; x <= MAP_SIZE.x - 1; ++x)
    {
        for (int y = 0; y <= MAP_SIZE.y - 1; ++y)
        {
            if (procedurallyGeneratedMap[x][y] == CellType::ROOM)
            {
                mTileMap.at(convertCoordsTo1D(x, y)) = std::move(
                    std::make_unique<Tile>(mTileModels.at(TileID::FLOOR).get()));
            }
            else if (procedurallyGeneratedMap[x][y] == CellType::HALL)
            {
                mTileMap.at(convertCoordsTo1D(x, y)) = std::move(
                    std::make_unique<Tile>(mTileModels.at(TileID::FLOOR).get()));
            }
            else
            {
                mTileMap.at(convertCoordsTo1D(x, y)) = std::move(
                    std::make_unique<Tile>(mTileModels.at(TileID::WALL).get()));
            }
        }
    }
}

void Map::loadTiles()
{
    Json::Value tiles;
    std::ifstream tileFile("resources/tiles/tiles.json", std::ifstream::binary);
    try
    {
        if (tileFile.fail())
        {
            throw std::runtime_error("ERR: Map::loadTiles - No tiles.json exists");

        }
        tileFile >> tiles;

        for (Json::Value::ArrayIndex index = 0; index != tiles.size(); index++)
        {
            bool isDeadly = tiles[index]["deadly"].asBool();
            unsigned int id = tiles[index]["id"].asUInt();

            /** Converting numerical ID to an enum type */
            TileID tileID = static_cast<TileID>(id);


            std::unique_ptr<TileModel> tileModel = std::make_unique<TileModel>(*mSharedCtx, isDeadly, tileID);
            mTileModels.insert({ tileID, std::move(tileModel) });
        }
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}

unsigned int Map::convertCoordsTo1D(const unsigned int& x, const unsigned int& y) const
{
    return (x * MAP_SIZE.x) + y;
}

Tile& Map::getTile(const unsigned int& x, const unsigned int& y)
{
    auto tile = mTileMap.at(convertCoordsTo1D(x, y)).get();
    return *tile;
}

void Map::update(const sf::Time& deltaTime)
{
    sf::FloatRect viewSpace = mSharedCtx->window->getViewSpace();
}

void Map::draw()
{
    sf::RenderWindow& window = mSharedCtx->window->mRenderWindow;
    sf::FloatRect viewSpace = mSharedCtx->window->getViewSpace();

    for (int x = 0; x <= MAP_SIZE.x - 1; ++x)
    {
        for (int y = 0; y <= MAP_SIZE.y - 1; ++y)
        {
            Tile& tile = getTile(x, y);
            sf::Sprite& sprite = tile.mTileModel->mSprite;
            sprite.setPosition(x * (TILE_SIZE), y * (TILE_SIZE));
            window.draw(sprite);
        }
    }
    mTerrainGenerator.draw(&window);
}
