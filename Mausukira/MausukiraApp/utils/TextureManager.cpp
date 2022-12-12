#include "TextureManager.h"
#include <exception>
#include <iostream>

void TextureManager::load(const std::string& name, const std::string& path)
{
    /** Checking if the textures was double loaded */
    if (textures.find(name) == textures.cend())
    {
        std::unique_ptr<sf::Texture> texture(new sf::Texture());
        try
        {
            /** sf::Texture::loadFromFile() returns a Boolean value that is true in case of success,
             * and false in case of failure */
            if (!texture->loadFromFile(path))
            {
                throw std::runtime_error("ERR: TextureManager::load - Failed to load a texture");
            }
            const auto inserted = textures.insert(std::make_pair(name, std::move(texture)));

            if (inserted.second == false)
            {
                throw std::logic_error("ERR: TextureManager::insert - Failed to insert");
            }
        }
        catch (std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (std::logic_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

const sf::Texture& TextureManager::get(const std::string& name)
{
    const auto foundTexture = textures.find(name);
    try
    {
        if (foundTexture == textures.cend())
        {
            throw std::runtime_error("ERR: TextureManager::get - Cannot find a texture");
        }
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }

    return *foundTexture->second;
}

void TextureManager::load(const std::string& name, std::unique_ptr<sf::Texture> texture)
{
    /** Checking if the textures was double loaded */
    if (textures.find(name) == textures.cend())
    {
        try
        {
            const auto inserted = textures.insert(std::make_pair(name, std::move(texture)));
            if (inserted.second == false)
            {
                throw std::logic_error("ERR: TextureManager::insert - Failed to insert");
            }
        }
        catch (std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (std::logic_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}