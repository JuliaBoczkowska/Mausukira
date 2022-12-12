target_sources(MausukiraApp PRIVATE
        SpriteComponent.cpp
        TransformComponent.cpp
        ColliderComponent.cpp
        HealthComponent.cpp
        EntityComponent.h
        )

add_subdirectory(enemy)