/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** DirectionalLight
*/

#pragma once
#include "ILight.hpp"

namespace Raytracer {
    class DirectionalLight : public ILight {
        public:
            DirectionalLight() = default;
            DirectionalLight(const Math::Vector3D& direction, double intensity,
                const Math::Vector3D& color = Math::Vector3D(1.0, 1.0, 1.0));
            ~DirectionalLight() = default;

            double getIntensity() const override;
            Math::Vector3D getColor() const override;
            Math::Vector3D getDirection() const;
            Math::Vector3D calculateColor(const Math::Vector3D& pixelColor, 
                const HitInfo& hitInfo, const Scene& scene) const override;

        private:
            Math::Vector3D _direction;
            double _intensity;
            Math::Vector3D _color;
    };
}
