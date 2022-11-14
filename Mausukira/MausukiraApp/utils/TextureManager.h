#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <map>
#include <memory>
#include "SFML/Graphics/Texture.hpp"
#include <string>

class TextureManager
{
public:

    /**
     * \brief Loads new textures to a map. If the texture was already present in the map the function returns.
     * \param name Alias for an texture, this will be the key to the map
     * \param path File path of the texture
     */
    void load(const std::string& name, const std::string& path);

    /**
     * \brief Function that finds and returns  a texture in the map by pre-registered name.
     * \param name Alias for an texture, which is then used as the key to the map.
     * \return A reference to a texture.
     */
    const sf::Texture& get(const std::string& name);

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textures; ///< Map storing all textures loaded during the game.
};

#endif