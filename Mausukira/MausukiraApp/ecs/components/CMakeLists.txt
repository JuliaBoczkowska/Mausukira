target_sources(MausukiraApp PRIVATE
        SpriteComponent.cpp
        TransformComponent.cpp
        ColliderComponent.cpp
        HealthComponent.cpp
        ScoreComponent.cpp
        )

add_subdirectory(enemy)
add_subdirectory(weapon)