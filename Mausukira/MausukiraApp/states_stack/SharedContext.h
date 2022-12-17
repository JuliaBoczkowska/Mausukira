#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "../Window.h"
#include "../scene/Scene.h"
#include "../utils/TextureManager.h"

struct SharedContext
{
    SharedContext(Window& window, TextureManager& textureManager)
        : window(window)
        , textureManager(textureManager)
    {
    }

    Window& window;
    TextureManager& textureManager;
    sf::Sprite background;
};

#endif// SHAREDCONTEXT_H
