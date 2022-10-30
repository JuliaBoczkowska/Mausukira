#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "../Window.h"
#include "../scene/Scene.h"

struct SharedContext {
    Window& window;
    Scene activeScene;
};

#endif//SHAREDCONTEXT_H
