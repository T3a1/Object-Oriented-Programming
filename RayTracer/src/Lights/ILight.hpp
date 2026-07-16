/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** ILight interface
*/

#pragma once
#include "Vector3D.hpp"
#include "HitInfo.hpp"

namespace Raytracer {
    class Scene;
    
    class ILight {
        public:
            virtual ~ILight() = default;
            virtual double getIntensity() const = 0;
            virtual Math::Vector3D getColor() const = 0;
            virtual Math::Vector3D calculateColor(const Math::Vector3D& pixelColor, 
                const HitInfo& hitInfo, const Scene& scene) const = 0;
    };
}
