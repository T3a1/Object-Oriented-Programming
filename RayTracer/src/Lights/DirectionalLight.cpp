/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"
#include "Scene.hpp"
#include <cmath>

namespace Raytracer {

DirectionalLight::DirectionalLight(const Math::Vector3D& direction, double intensity,
    const Math::Vector3D& color) : _direction(direction), _intensity(intensity), _color(color)
{
    double len = _direction.length();
    if (len > 0) {
        _direction.x /= len;
        _direction.y /= len;
        _direction.z /= len;
    }
}

double DirectionalLight::getIntensity() const {
    return _intensity;
}

Math::Vector3D DirectionalLight::getColor() const {
    return _color;
}

Math::Vector3D DirectionalLight::getDirection() const {
    return _direction;
}

Math::Vector3D DirectionalLight::calculateColor(const Math::Vector3D& pixelColor, 
    const HitInfo& hitInfo, const Scene& scene) const
{
    double diff = std::max(0.0, hitInfo.normal.dot(_direction));
    Math::Vector3D shadowTransmission = scene.getShadowInfo(hitInfo.point, _direction).transmission;

    return Math::Vector3D(
        pixelColor.x * _color.x * _intensity * diff * shadowTransmission.x,
        pixelColor.y * _color.y * _intensity * diff * shadowTransmission.y,
        pixelColor.z * _color.z * _intensity * diff * shadowTransmission.z
    );
}

}
