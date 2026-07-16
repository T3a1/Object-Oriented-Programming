/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Ray
*/

#include "Ray.hpp"

namespace Raytracer {

Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
    : _origin(origin), _direction(direction)
{
}

}
