/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** PointLight
*/

#include "PointLight.hpp"
#include "Scene.hpp"
#include <cmath>

namespace Raytracer {

PointLight::PointLight(const Math::Point3D& position, double intensity,
    const Math::Vector3D& color)
    : _position(position), _intensity(intensity), _color(color)
{
}

double PointLight::getIntensity() const {
    return _intensity;
}

Math::Vector3D PointLight::getColor() const {
    return _color;
}

Math::Point3D PointLight::getPosition() const {
    return _position;
}

Math::Vector3D PointLight::calculateColor(const Math::Vector3D& pixelColor, 
    const HitInfo& hitInfo, const Scene& scene) const
{
    Math::Vector3D to_light(
        _position.x - hitInfo.point.x,
        _position.y - hitInfo.point.y,
        _position.z - hitInfo.point.z
    );

    double distance_to_light = std::sqrt(to_light.x * to_light.x
        + to_light.y * to_light.y + to_light.z * to_light.z);
    if (distance_to_light < 1e-6)
        return Math::Vector3D(0, 0, 0);

    Math::Vector3D light_dir(
        to_light.x / distance_to_light,
        to_light.y / distance_to_light,
        to_light.z / distance_to_light
    );
    double attenuation = 1.0 / (distance_to_light * distance_to_light);
    double diff = std::max(0.0, hitInfo.normal.dot(light_dir));
    Math::Vector3D shadowTransmission = scene.getShadowInfo(hitInfo.point, light_dir, distance_to_light).transmission;

    return Math::Vector3D(
        pixelColor.x * _color.x * _intensity * diff * attenuation * shadowTransmission.x,
        pixelColor.y * _color.y * _intensity * diff * attenuation * shadowTransmission.y,
        pixelColor.z * _color.z * _intensity * diff * attenuation * shadowTransmission.z
    );
}

}
