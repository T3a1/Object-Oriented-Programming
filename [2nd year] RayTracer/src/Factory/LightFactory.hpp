/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-27
** File description:
** LightFactory - Factory Pattern for creating lights
*/

#pragma once
#include "ILight.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <functional>

namespace Raytracer {
    class LightFactory {
        public:
            LightFactory() = default;
            ~LightFactory() = default;

            std::unique_ptr<ILight> createLight(const std::string& type) const;
            std::unique_ptr<ILight> createAmbientLight(double intensity, 
                const Math::Vector3D& color = Math::Vector3D(1.0, 1.0, 1.0)) const;
            std::unique_ptr<ILight> createDirectionalLight(const Math::Vector3D& direction, 
                double intensity, const Math::Vector3D& color = Math::Vector3D(1.0, 1.0, 1.0)) const;
            std::unique_ptr<ILight> createPointLight(const Math::Point3D& position, 
                double intensity, const Math::Vector3D& color = Math::Vector3D(1.0, 1.0, 1.0)) const;
            
            void registerLightCreator(
                const std::string& type, 
                std::function<std::unique_ptr<ILight>()> creator
            );
            std::vector<std::string> getAvailableLights() const;
            void clearCreators() {
                _creators.clear();
            }

        private:
            std::unordered_map<std::string, std::function<std::unique_ptr<ILight>()>> _creators = {
                {"ambient", []() { return std::make_unique<AmbientLight>(); }},
                {"directional", []() { return std::make_unique<DirectionalLight>(); }},
                {"point", []() { return std::make_unique<PointLight>(); }},
            };
    };
}