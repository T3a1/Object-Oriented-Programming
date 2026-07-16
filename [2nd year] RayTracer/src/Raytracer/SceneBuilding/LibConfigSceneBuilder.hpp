/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** LibConfigSceneBuilder
*/

#pragma once
#include "ISceneBuilder.hpp"
#include "ShapeFactory.hpp"
#include "LightFactory.hpp"
#include "GroupShape.hpp"
#include <libconfig.h++>
#include <string>
#include <memory>

namespace Raytracer {
    class LibConfigSceneBuilder : public ISceneBuilder {
        public:

            LibConfigSceneBuilder(
                const std::string& configFilePath,
                Raytracer::ShapeFactory& shapeFactory,
                Raytracer::LightFactory& lightFactory
            );

            void buildCamera(Scene& scene) override;
            void buildPrimitives(Scene& scene) override;
            void buildLights(Scene& scene) override;
            void buildGroups(Scene& scene) override;

        private:
            libconfig::Config _cfg;
            ShapeFactory& _shapeFactory;
            LightFactory& _lightFactory;

            void loadSphere(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);
            void loadPlane(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);
            void loadCylinder(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);
            void loadCone(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);
            void loadLimitedCylinder(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);
            void loadLimitedCone(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);
            void loadTriangle(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);
            void loadTorus(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);
            void buildPrimitivesWithContainer(libconfig::Setting& primitives, std::shared_ptr<GroupShape> group, Scene& scene);
            void loadGroupShapes(libconfig::Setting& prim, Scene& scene);
            void loadObj(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene);

            void loadAmbientLight(Scene& scene);
            void loadDirectionalLights(Scene& scene);
            void loadPointLights(Scene& scene);
    };
}