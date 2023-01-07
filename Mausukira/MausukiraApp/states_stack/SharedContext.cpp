#include "SharedContext.h"
#include "Window.h"
#include "utils/TextureManager.h"

SharedContext::SharedContext(Window& window, TextureManager& textureManager)
    : window(window)
    , textureManager(textureManager)
{
}
