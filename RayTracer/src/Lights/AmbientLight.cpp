/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** AmbientLight
*/

#include "AmbientLight.hpp"

namespace Raytracer {

AmbientLight::AmbientLight(double intensity, const Math::Vector3D& color)
    : _intensity(intensity), _color(color)
{
}

double AmbientLight::getIntensity() const {
    return _intensity;
}

Math::Vector3D AmbientLight::getColor() const {
    return _color;
}

Math::Vector3D AmbientLight::calculateColor(const Math::Vector3D& pixelColor, 
    [[maybe_unused]] const HitInfo& hitInfo, [[maybe_unused]] const Scene& scene) const
{
    return Math::Vector3D(
        pixelColor.x * _color.x * _intensity,
        pixelColor.y * _color.y * _intensity,
        pixelColor.z * _color.z * _intensity
    );
}

}
