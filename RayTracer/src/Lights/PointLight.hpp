/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** PointLight
*/

#pragma once
#include "ILight.hpp"
#include "Point3D.hpp"

namespace Raytracer {
    class PointLight : public ILight {
        public:
            PointLight() = default;
            PointLight(const Math::Point3D& position, double intensity,
                const Math::Vector3D& color = Math::Vector3D(1.0, 1.0, 1.0));
            ~PointLight() = default;

            double getIntensity() const override;
            Math::Vector3D getColor() const override;
            Math::Point3D getPosition() const;
            Math::Vector3D calculateColor(const Math::Vector3D& pixelColor, 
                const HitInfo& hitInfo, const Scene& scene) const override;

        private:
            Math::Point3D _position;
            double _intensity;
            Math::Vector3D _color;
    };
}
