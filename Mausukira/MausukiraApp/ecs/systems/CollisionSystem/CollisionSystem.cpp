#include "CollisionSystem.h"
#include "ecs/components/ColliderComponent.h"
#include "ecs/components/HealthComponent.h"
#include "dungeon/map/MapUtils.h"

CollisionSystem::CollisionSystem(entt::registry& registry, MapContext& mapContext)
    : System(registry)
    , mMapContext(mapContext)
    , mCollisionKinematic(registry)
    , mCollisionStatic(registry, mapContext)
{
}


void CollisionSystem::update(const sf::Time& dt)
{
    mCollisionStatic.update(dt);
    mCollisionKinematic.update(dt);

//    std::vector<CollisionBox*> projectileCollisionBoxes;
//    projectileAndWall(projectileCollisionBoxes);
//    enemyAndProjectileCollision(projectileCollisionBoxes);
//    eraseProjectilesThatCollide();
}

//
//void CollisionSystem::enemyAndProjectileCollision(
//    std::vector<CollisionBox*>& projectileCollisionBoxes)
//{
//    mRegistry.view<ColliderComponent, TransformComponent, EntityStatistic, HealthComponent>().each(
//        [&](ColliderComponent& colliderComponent, TransformComponent& transformComponent,
//            EntityStatistic& entityStatistic, HealthComponent& healthComponent)
//        {
//            for (auto& projectile: projectileCollisionBoxes)
//            {
//                if (projectile->isColliding(colliderComponent.mCollisionBox))
//                {
//                    projectile->mIsColliding = true;
//                    healthComponent.damageHealth(5);
//                }
//            }
//        });
//}
//
//
//void CollisionSystem::eraseProjectilesThatCollide()
//{
//    mRegistry.view<Weapon>().each(
//        [&](Weapon& weapon)
//        {
//            auto it = weapon.mProjectiles.begin();
//            while (it != weapon.mProjectiles.end())
//            {
//                if ((*it)->CollisionBox.mIsColliding)
//                {
//                    weapon.mProjectiles.erase(it++);
//                }
//                else
//                {
//
//                    ++it;
//                }
//            }
//        });
//}
