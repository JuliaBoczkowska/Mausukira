#include "Scene.h"
#include "../ecs/Entity.h"

Scene::Scene()
{
//    Entity entity = { mRegistry.create(), this };
//    entity.AddComponent<TransformComponent>();
}

Scene::~Scene()
{
}

void Scene::update(const sf::Time& deltaTime)
{
//    entt::entity entity = mRegistry.create();    /** entity is basically an id of std::uint32_t type */
//    mRegistry.emplace<TransformComponent>(entity, sf::Vector2f{ 0.f, 0.f });

//grouping and iterating
//    auto group = mRegistry.group<TransformComponent>(entt::get<SpriteComponent>);
//    for (auto entity: group)
//    {
//        auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
//    }
}

Entity Scene::createEntity()
{
    Entity entity = { mRegistry.create(), this };
//    entity.AddComponent<TransformComponent>();
    return entity;
}
