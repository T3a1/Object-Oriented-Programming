/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** SceneDirector
*/

#pragma once
#include "ISceneBuilder.hpp"

namespace Raytracer {
    class SceneDirector {
        public:
            SceneDirector(ISceneBuilder& builder) : _builder(builder) {}

            Scene constructFullScene() {
                Scene scene;
                _builder.buildCamera(scene);
                _builder.buildPrimitives(scene);
                _builder.buildGroups(scene);
                _builder.buildLights(scene);
                scene.buildBVH();
                return scene;
            }

            Scene constructSubScene() {
                Scene scene;
                _builder.buildPrimitives(scene);
                _builder.buildGroups(scene);
                _builder.buildLights(scene);
                return scene;
            }

            void constructAndRenderPreview(Scene& scene) {
                _builder.buildCamera(scene);
                _builder.buildPrimitives(scene);
                _builder.buildGroups(scene);
                _builder.buildLights(scene);
                scene.renderScenePreview(scene.getWidth(), scene.getHeight(), scene.getBackgroundColor());
            }

            void constructAndRenderFullScene(Scene& scene, int antialiasing = 1) {
                _builder.buildCamera(scene);
                _builder.buildPrimitives(scene);
                _builder.buildGroups(scene);
                _builder.buildLights(scene);
                scene.renderScene(scene.getWidth(), scene.getHeight(), scene.getBackgroundColor(), antialiasing);
            }

        private:
            ISceneBuilder& _builder;
    };
}
