#ifndef RNDSPRITECOMPONENT_H
#define RNDSPRITECOMPONENT_H

#include "EnemyTextureGenerator.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "ecs/components/SpriteComponent.h"

class RndSpriteComponent : public SpriteComponent
{
public:
    RndSpriteComponent(EnemyTextureGenerator& mTextCreator);
    RndSpriteComponent(const RndSpriteComponent&);
    RndSpriteComponent(RndSpriteComponent&& c) noexcept;
    RndSpriteComponent& operator=(RndSpriteComponent&& other);

    void draw(sf::RenderWindow& window) override;
    void setPosition(const sf::Vector2f& position) override;
    void moveBy(const sf::Vector2f& mov) override;

private:
    EnemyTextureGenerator& mEnemyTextureCreator;
    std::vector<sf::Sprite> mSpritesParts;
};

#endif// RNDSPRITECOMPONENT_H
