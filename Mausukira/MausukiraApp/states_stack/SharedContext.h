#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "SFML/Graphics/Sprite.hpp"

class Window;

class TextureManager;

struct SharedContext
{
    SharedContext(Window& window, TextureManager& textureManager);

    Window& window;
    TextureManager& textureManager;
    sf::Sprite background;
};

#endif// SHAREDCONTEXT_H
