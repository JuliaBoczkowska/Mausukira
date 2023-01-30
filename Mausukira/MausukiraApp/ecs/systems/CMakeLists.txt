target_sources(MausukiraSrc PRIVATE
        SystemQueue.cpp
        RenderingSystem/RenderingSystem.cpp
        CollisionSystem/CollisionSystem.cpp
        CollisionSystem/CollisionStatic.cpp
        CollisionSystem/CollisionKinematic.cpp
        CameraSystem.cpp
        DebugSystem.cpp
        ScoreSystem.cpp
        MoveSystem/PlayerMoveSystem.cpp
        MoveSystem/MoveSystem.cpp
        CollisionSystem/SpatialHashing/SpatialHash.cpp
        DamageSystem/HealthSystem.cpp
        LevelChangeSystem.cpp
        )

add_subdirectory(AiSystem/EnemySystems)
add_subdirectory(PhysicsSystem)