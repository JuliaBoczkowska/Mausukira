target_sources(MausukiraApp PRIVATE
        SystemQueue.cpp
        RenderingSystem/RenderingSystem.cpp
        CollisionSystem/CollisionSystem.cpp
        CollisionSystem/CollisionStatic.cpp
        CollisionSystem/CollisionKinematic.cpp
        PhysicsSystem/ProjectileShootSystem.cpp
        CameraSystem.cpp
        DebugSystem.cpp
        ScoreSystem.cpp
        MoveSystem/PlayerMoveSystem.cpp
        MoveSystem/MoveSystem.cpp
        CollisionSystem/SpatialHashing/SpatialHash.cpp
        DamageSystem/HealthSystem.cpp
        LevelChangeSystem.cpp
        AiSystem/EnemyFollowSystem.cpp
        )