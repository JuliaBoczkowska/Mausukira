#ifndef MAP_H
#define MAP_H

#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"
#include "TerrainGenerator.h"
#include "../../states_stack/SharedContext.h"
#include <unordered_map>
#include <array>

struct Tile;
enum TileID;
struct TileModel;

using TileModels = std::unordered_map<TileID, std::unique_ptr<TileModel>>;
using TileMap = std::array<std::unique_ptr<Tile>, 1024>;

class Map
{
public:
    Map(SharedContext* sharedCtx);

    ~Map() = default;

    void update(const sf::Time& deltaTime);

    void draw();

    Tile& getTile(const unsigned int& x, const unsigned int& y);

    unsigned int convertCoordsTo1D(const unsigned int& x, const unsigned int& y) const;

private:
    void loadTiles();

private:
    const sf::Vector2u MAP_SIZE = { 32, 32 };    ///< Map size
    TileModels mTileModels;
    TileMap mTileMap;
    SharedContext* mSharedCtx;
    TerrainGenerator mTerrainGenerator;
};

#endif //MAP_H
