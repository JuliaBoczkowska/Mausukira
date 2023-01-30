target_sources(MausukiraSrc PRIVATE
        ../ecs/Scene.cpp
        CollisionBox.cpp
        ../ecs/entities/enemy/EnemyParser.cpp
        ../ecs/entities/Player.cpp
        Debug.cpp)

add_subdirectory(map)
add_subdirectory(algorithms)