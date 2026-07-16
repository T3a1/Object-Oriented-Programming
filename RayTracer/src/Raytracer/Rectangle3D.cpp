/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"

namespace Raytracer {

Rectangle3D::Rectangle3D() {
    _origin = Math::Point3D();
    _bottom_side = Math::Vector3D();
    _left_side = Math::Vector3D();
}

Rectangle3D::Rectangle3D(const Math::Point3D &origin, const Math::Vector3D &bottom_side, const Math::Vector3D &left_side)
    : _origin(origin), _bottom_side(bottom_side), _left_side(left_side)
{
}

Math::Point3D Rectangle3D::pointAt(double x, double y) const {
    return _origin + _bottom_side * x + _left_side * y;
}

}
