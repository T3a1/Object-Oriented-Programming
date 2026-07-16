/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** ISceneBuilder
*/

#pragma once
#include "Scene.hpp"

namespace Raytracer {
    class ISceneBuilder {
        public:
            virtual ~ISceneBuilder() = default;

            virtual void buildCamera(Scene& scene) = 0;
            virtual void buildPrimitives(Scene& scene) = 0;
            virtual void buildLights(Scene& scene) = 0;
            virtual void buildGroups(Scene& scene) = 0;
    };
}
