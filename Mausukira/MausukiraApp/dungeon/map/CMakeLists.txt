target_sources(MausukiraSrc PRIVATE
        Map.cpp
        room/Room.cpp
        ../DungeonGenerator.cpp
        room/RoomGenerator.cpp
        )

add_subdirectory(tile)