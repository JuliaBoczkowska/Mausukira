#include "GuiComponents.h"

void GuiComponents::handleEvent(sf::Event& event)
{
    for (auto& component: mComponents)
    {
        component->handleEvent(event);
    }
}

void GuiComponents::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& component: mComponents)
    {
        component->draw(target, states);
    }
}
