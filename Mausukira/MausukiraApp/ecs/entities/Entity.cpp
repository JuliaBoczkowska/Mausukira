#include "Entity.h"

Entity::Entity(entt::entity entity, entt::registry* registry)
    : mEntity(entity)
    , mRegistry(*registry)
{
}