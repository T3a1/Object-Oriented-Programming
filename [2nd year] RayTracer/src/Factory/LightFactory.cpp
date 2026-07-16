/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-27
** File description:
** LightFactory implementation
*/

#include "LightFactory.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include <iostream>
#include <unordered_map>
#include <functional>

namespace Raytracer {

    std::unique_ptr<ILight> LightFactory::createLight(const std::string& type) const
    {
        static const std::unordered_map<std::string, std::function<std::unique_ptr<ILight>()>> creators = {
            {"ambient", []() { return std::make_unique<AmbientLight>(); }},
            {"directional", []() { return std::make_unique<DirectionalLight>(); }},
            {"point", []() { return std::make_unique<PointLight>(); }},
        };
        const auto it = creators.find(type);
        if (it != creators.end())
            return it->second();

        std::cerr << "Error: Unknown light type '" << type << "'" << std::endl;
        return nullptr;
    }

    std::unique_ptr<ILight> LightFactory::createAmbientLight(double intensity,
        const Math::Vector3D& color) const {
        return std::make_unique<AmbientLight>(intensity, color);
    }

    std::unique_ptr<ILight> LightFactory::createDirectionalLight(const Math::Vector3D& direction, 
        double intensity, const Math::Vector3D& color) const {
        return std::make_unique<DirectionalLight>(direction, intensity, color);
    }

    std::unique_ptr<ILight> LightFactory::createPointLight(const Math::Point3D& position, 
        double intensity, const Math::Vector3D& color) const {
        return std::make_unique<PointLight>(position, intensity, color);
    }



    void LightFactory::registerLightCreator(
        const std::string& type, 
        std::function<std::unique_ptr<ILight>()> creator
    ) {
        _creators[type] = creator;
    }

    std::vector<std::string> LightFactory::getAvailableLights() const {
        std::vector<std::string> result;
        for (const auto& pair : _creators) {
            result.push_back(pair.first);
        }
        return result;
    }
}
