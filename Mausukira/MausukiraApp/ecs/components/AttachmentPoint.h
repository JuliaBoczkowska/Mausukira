#ifndef ATTACHMENTPOINT_H
#define ATTACHMENTPOINT_H

#include "entt/entt.hpp"
#include "SFML/System/Vector2.hpp"

struct AttachmentPoint
{
    entt::entity parent{ entt::null };
    sf::Vector2f offsetFromParent;
};

struct Relationship
{
    std::size_t children{};
    entt::entity first_child{ entt::null };
    entt::entity prev{ entt::null };
    entt::entity next{ entt::null };
    entt::entity parent{ entt::null };
    sf::Vector2f offsetFromParent;
};
#endif //ATTACHMENTPOINT_H
