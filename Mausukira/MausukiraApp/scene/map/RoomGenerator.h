#ifndef ROOMGENERATOR_H
#define ROOMGENERATOR_H
#include "Room.h"
#include <array>
#include <list>

using RoomGrid = std::vector<std::vector<int>>;

class RoomGenerator
{
public:
    RoomGenerator(std::array<std::array<int, 32>, 32>& map)
        : map(map){};
    
    enum RoomTypes
    {
        CELLULAR_AUTOMATA = 0,
        RECTANGLE,
        CIRCLE
    };

    /**
     * @brief Randomly allocate some number of rooms on the map
     */
    std::list<Room> allocateRooms();

private:
    bool isRoomColliding(Room& temp);
    RoomGrid getMultiDimGrid(int width, int height, int value = 1);
    RoomGrid generateRoom();
    std::vector<std::vector<int>> generateRoomRectangle();
    void generateRoomCA();
    void generateRoomCircle();
    bool placeRoomOnMap(std::vector<std::vector<int>> roomOutline);

private:
    int roomCounter{0};
    std::array<std::array<int, 32>, 32>& map;
    std::list<Room> mRooms;
};


#endif// ROOMGENERATOR_H
