/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** AmbientLight
*/

#pragma once
#include "ILight.hpp"

namespace Raytracer {
    class AmbientLight : public ILight {
        public:
            AmbientLight() = default;
            AmbientLight(double intensity, const Math::Vector3D& color = Math::Vector3D(1.0, 1.0, 1.0));
            ~AmbientLight() = default;

            double getIntensity() const override;
            Math::Vector3D getColor() const override;
            Math::Vector3D calculateColor(const Math::Vector3D& pixelColor,
                [[maybe_unused]] const HitInfo& hitInfo, [[maybe_unused]] const Scene& scene) const override;

        private:
            double _intensity;
            Math::Vector3D _color;
    };
}
