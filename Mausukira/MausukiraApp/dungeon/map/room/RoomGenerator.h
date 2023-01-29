#ifndef ROOMGENERATOR_H
#define ROOMGENERATOR_H

#include "Room.h"
#include "dungeon/map/Constants.h"
#include <array>
#include <list>

class RoomGenerator
{
public:
    RoomGenerator();

    enum RoomTypes
    {
        RECTANGLE = 1,
        CIRCLE = 2
    };

    /**
     * @brief Randomly allocate some number of rooms on the map
     */
    std::list<Room> allocateRooms(std::array<std::array<int, MAP_SIZE_X>, MAP_SIZE_Y>& map);

private:
    bool isRoomColliding(Room& temp);

    Room::RoomGrid getMultiDimGrid(int width, int height, int value = 1);

    Room::RoomGrid generateRoom();

    std::vector<std::vector<int>> generateRoomRectangle();

    std::vector<std::vector<int>> generateRoomCircle();

    bool placeRoomOnMap(std::vector<std::vector<int>> roomOutline);

private:
    int roomCounter{0};
    std::array<std::array<int, MAP_SIZE_X>, MAP_SIZE_Y>* mMap;
    std::list<Room> mRooms;
};


#endif// ROOMGENERATOR_H
