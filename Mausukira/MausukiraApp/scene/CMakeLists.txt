target_sources(MausukiraApp PRIVATE
        Scene.cpp
        CollisionBox.cpp
        EnemyParser.cpp)

add_subdirectory(map)
add_subdirectory(algorithms)