/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Raytracer {

Camera::Camera(const Math::Point3D &origin, const Math::Point3D &screen_origin,
    const Math::Vector3D &bottom_side, const Math::Vector3D &left_side)
    : _origin(origin), _screen(screen_origin, bottom_side, left_side)
{
}


Ray Camera::ray(double x, double y) const {
    Math::Point3D point = _screen.pointAt(x, y);
    Math::Vector3D direction = Math::Vector3D(point.x - _origin.x,
        point.y - _origin.y, point.z - _origin.z);

    return Ray(_origin, direction);
}

}
