#include "RoomGenerator.h"
#include "scene/map/Tile/TileHelper.h"
#include "utils/RandomNumberGenerator.h"

RoomGenerator::RoomGenerator(std::array<std::array<int, MAP_SIZE_X>, MAP_SIZE_Y>& map)
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
    auto roomType = RECTANGLE;
    auto chanceCircleRoom = 20.f;
    if (generateFloatNumberInRange(0.f, 1.f) * 100 < chanceCircleRoom)
    {
        roomType = CIRCLE;
    }

    switch (roomType)
    {
        case RECTANGLE: return generateRoomRectangle(); break;
        case CIRCLE: return generateRoomCircle(); break;
    }
}

#include <iostream>
std::vector<std::vector<int>> RoomGenerator::generateRoomCircle()
{
    int radius = generateIntNumberInRange(4, 7);

    auto squareGrid = getMultiDimGrid(2 * radius + 1, 2 * radius + 1, 0);
    int size = squareGrid.size();

    /** Coordinates inside the rectangle */
    int pointX, pointY;
    for (int rowIdx = 0; rowIdx < size; rowIdx++)
    {
        for (int colIdx = 0; colIdx < size; colIdx++)
        {
            /** Start from the left side point */
            pointX = rowIdx - radius;
            pointY = colIdx - radius;

            /** Check if its inside */
            if (pow(pointX, 2) + pow(pointY, 2) <= pow(radius, 2) + 1)
            {
                squareGrid[rowIdx][colIdx] = 1;
            }
        }
    }

    //    for (int y = 0; y < size; y++)
    //    {
    //        for (int x = 0; x < size; x++)
    //        {
    //            std::cout << squareGrid[x][y];
    //        }
    //        std::cout << std::endl;
    //    }
    return squareGrid;
}

std::vector<std::vector<int>> RoomGenerator::generateRoomRectangle()
{
    const auto& [width, height] = generateTwoIntNumbersInRange(5, 14);
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
        sf::Vector2i tileLocation = generateTwoIntNumbersInRange(1, MAP_SIZE_X);
        roomRow = roomOutline.size();
        roomCol = roomOutline.at(0).size();

        if (!tile_helper::isInBorders(
                sf::Vector2i{tileLocation.x + roomRow, tileLocation.y + roomCol}))
        {
            tileLocation.x = MAP_SIZE_X - 1 - roomRow;
            tileLocation.y = MAP_SIZE_Y - 1 - roomCol;
        }

        auto worldLocation =
            tile_helper::tileToWorldCoordinate<float>(tileLocation.x, tileLocation.y);
        auto worldRoomDimension = tile_helper::tileToWorldCoordinate<float>(roomRow, roomCol);


        /** Center of the room */
        sf::Vector2f center = (worldLocation + (worldRoomDimension / 2.f));

        /** Additional two is added in order to obtain space between rooms and for outlines of
         * rooms*/
        roomToBeAdded =
            Room(tileLocation, sf::Vector2i{roomRow - 1, roomCol - 1}, roomOutline, center);
        ++count;
    }
    while (isRoomColliding(roomToBeAdded));

    mRooms.push_back(roomToBeAdded);

    int index = 0;
    int temp_row = 0, temp_col = 0;

    for (int i = roomToBeAdded.mLocation.x;
         i < mMap.size() && (i < (roomToBeAdded.mLocation.x + roomRow)); ++i)
    {
        for (int j = roomToBeAdded.mLocation.y;
             j < mMap.size() && (j < (roomToBeAdded.mLocation.y + roomCol)); ++j)
        {
            if (temp_row == roomRow)
            {
                temp_row = 0;
                temp_col++;
            }
            if (temp_col == roomCol)
            {
                break;
            }
            if (roomToBeAdded.mGrid[temp_row][temp_col] == 0)
            {
                temp_row++;
                continue;
            }
            temp_row++;

            // mMap[temp_row][temp_col] = 1;
            mMap[i][j] = 1;
            //            index++;
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
