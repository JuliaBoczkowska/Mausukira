target_sources(MausukiraApp PRIVATE
        Map.cpp
        room/Room.cpp
        ../DungeonGenerator.cpp
        room/RoomGenerator.cpp
        )

add_subdirectory(tile)