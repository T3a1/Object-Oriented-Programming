/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** HardCodedSceneBuilder
*/

#pragma once
#include "ISceneBuilder.hpp"
#include "ShapeFactory.hpp"
#include "LightFactory.hpp"
#include <memory>

namespace Raytracer {
    class HardCodedSceneBuilder : public ISceneBuilder {
        public:
            HardCodedSceneBuilder(
                ShapeFactory& shapeFactory,
                LightFactory& lightFactory
            );

            void buildCamera(Scene& scene) override;
            void buildPrimitives(Scene& scene) override;
            void buildLights(Scene& scene) override;
            void buildGroups(Scene& scene) override;

        private:
            ShapeFactory& _shapeFactory;
            LightFactory& _lightFactory;
    };
}
