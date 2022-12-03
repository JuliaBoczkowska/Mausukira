#ifndef GUICOMPONENTS_H
#define GUICOMPONENTS_H

#include "Component.h"
#include <vector>

class GuiComponents : public sf::Drawable
{
public:
    GuiComponents() = default;

    void addComponent(std::shared_ptr<Component> component)
    {
        mComponents.emplace_back(std::move(component));
    }

    void handleEvent(sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<std::shared_ptr<Component>> mComponents;
};

#endif// GUICOMPONENTS_H
