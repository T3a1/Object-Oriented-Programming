/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Utils
*/

#pragma once

    #include <iostream>
    #include <map>
    #include <functional>

namespace Arc
{
    /**
     * @enum LibraryType
     * @brief Classification of dynamic libraries in the Arcade system.
     */
    enum class LibraryType
    {
        Game,       /**< A game implementation library */
        Renderer    /**< A graphics renderer implementation library */
    };

    /**
     * @struct Item
     * @brief Represents a renderable object in the display.
     */
    struct Item
    {
        std::pair<float, float> position;
        std::pair<float, float> size;
        int rotation;
        std::pair<float, float> textureSize;
        bool isHovered;
        int drawOrder;
        std::string texturePath;
        std::string text;
        std::function<void()> buttonAction;
    };
}
