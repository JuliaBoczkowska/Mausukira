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
        SpatialHashing/SpatialHash.cpp
        )