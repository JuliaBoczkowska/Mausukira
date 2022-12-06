#include "RoomGenerator.h"
#include "scene/map/Tile/TileHelper.h"
#include "utils/RandomNumberGenerator.h"

RoomGenerator::RoomGenerator(std::array<std::array<int, 32>, 32>& map)
    : mMap(map)
{
}


RoomGrid RoomGenerator::getMultiDimGrid(int width, int height, int value)
{
    std::vector<int> row(height, value);
    std::vector<std::vector<int>> grid(width, row);
    return grid;
}

std::list<Room> RoomGenerator::allocateRooms()
{
    //    int count = 0;
    //    while (count != 5)
    //    {
    //        count++;
    while (true)
    {
        if (!placeRoomOnMap(generateRoom()))
        {
            break;
        }
    }
    return mRooms;
}

RoomGrid RoomGenerator::generateRoom()
{
    // TODO complete switch
    RoomTypes roomType = RECTANGLE;

    switch (roomType)
    {
        case RECTANGLE:
            return generateRoomRectangle();
            break;
            //        case CELLULAR_AUTOMATA:generateRoomCA();
            //            break;
            //        case CIRCLE:generateRoomCircle();
            //            break;
    }
}

std::vector<std::vector<int>> RoomGenerator::generateRoomRectangle()
{
    const auto& [width, height] = generateTwoNumbersInRange(3, 14);
    auto grid = getMultiDimGrid(width, height);

    return grid;
}

bool RoomGenerator::placeRoomOnMap(std::vector<std::vector<int>> roomOutline)
{
    /** Counter for debug purposes */
    roomCounter++;

    Room roomToBeAdded;
    int count = 0;
    int roomRow{0};
    int roomCol{0};

    do
    {
        /** After some number of attempts leave */
        if (count == 10000)
        {
            return false;
        }
        sf::Vector2i tileLocation = generateTwoNumbersInRange(1, 31);
        roomRow = roomOutline.size();
        roomCol = roomOutline.at(0).size();

        if (!tile_helper::isInBorders(
                sf::Vector2i{tileLocation.x + roomRow, tileLocation.y + roomCol}))
        {
            tileLocation.x = 31 - roomRow;
            tileLocation.y = 31 - roomCol;
        }

        auto worldLocation =
            tile_helper::tileToWorldCoordinate<float>(tileLocation.x, tileLocation.y);
        auto worldRoomDimension = tile_helper::tileToWorldCoordinate<float>(roomRow, roomCol);


        /** Center of the room */
        sf::Vector2f center = (worldLocation + (worldRoomDimension / 2.f));

        /** Additional two is added in order to obtain space between rooms and for outlines of
         * rooms*/
        roomToBeAdded = Room(tileLocation, sf::Vector2i{roomRow, roomCol}, roomOutline, center);
        ++count;
    }
    while (isRoomColliding(roomToBeAdded));

    mRooms.push_back(roomToBeAdded);

    //    int index = 0;

    for (int i = roomToBeAdded.mLocation.x;
         i < mMap.size() && (i < (roomToBeAdded.mLocation.x + roomRow)); ++i)
    {
        for (int j = roomToBeAdded.mLocation.y;
             j < mMap.size() && (j < (roomToBeAdded.mLocation.y + roomCol)); ++j)
        {
            // TODO Solution for circle and CA. For square only value "1" is sufficient
            // temp_row = index % roomRow;
            // temp_col = index / roomRow;

            mMap[i][j] = 1;
            // index++;
        }
    }
    return true;
}

bool RoomGenerator::isRoomColliding(Room& other)
{
    for (auto& room: mRooms)
    {
        if (room.collide(other))
        {
            return true;
        }
    }
    return false;
}