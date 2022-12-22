target_sources(MausukiraApp PRIVATE
        ../ecs/Scene.cpp
        CollisionBox.cpp
        ../ecs/entities/enemy/EnemyParser.cpp
        ../ecs/entities/Player.cpp)

add_subdirectory(map)
add_subdirectory(algorithms)